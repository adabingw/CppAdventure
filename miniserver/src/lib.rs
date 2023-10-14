use std::{
    sync::{mpsc, Arc, Mutex}, 
    thread
};

// mpsc stands for: multiple producers, single consumer
// in other words, multiple sending ends but only one receiving end

pub struct ThreadPool {
    workers: Vec<Worker>,
    /**
     * use Option to be able to take() and move sender out of ThreadPool
     */
    sender: Option<mpsc::Sender<Job>>
}

/**
 * we use Box because we only care that the job implements the traits
 * for the purpose of dynamic dispatching
 * other uses of box:
 * 1. for recursive types (or types whose size can't be known at runtime)
 * 2. for when u have large amounts of data and want to ensure they're not deep copied
 * 
 * dyn is used for trait objects when we want any closure function
 * 
 * The way a closure captures and handles values from the environment affects which 
 * traits the closure implements, and traits are how functions and structs can specify 
 * what kinds of closures they can use. Closures will automatically implement one, two, 
 * or all three of these Fn traits, in an additive fashion, 
 * depending on how the closure’s body handles the values:
 * 
 * 1. FnOnce applies to closures that can be called once. All closures implement at least this trait, 
 * because all closures can be called. A closure that moves captured values out of its body will 
 * only implement FnOnce and none of the other Fn traits, because it can only be called once.
 * 
 * 2. FnMut applies to closures that don’t move captured values out of their body, but that might 
 * mutate the captured values. These closures can be called more than once.
 * 
 * 3. Fn applies to closures that don’t move captured values out of their body and that don’t 
 * mutate captured values, as well as closures that capture nothing from their environment. 
 * These closures can be called more than once without mutating their environment, which is important 
 * in cases such as calling a closure multiple times concurrently.
 */

type Job = Box<dyn FnOnce() + Send + 'static>;

impl ThreadPool {
    pub fn new(size: usize) -> ThreadPool {
        assert!(size > 0);

        // sender: Sender<Box<dyn FnOnce() + Send>>
        // receiver: Receiver<Box<dyn FnOnce() + Send>>
        let (sender, receiver) = mpsc::channel();

        // mutex allows only one thread to access some data at any given time.
        // use Arc for multiple ownership of the Mutex, because we want to move it into threads
        let receiver = Arc::new(Mutex::new(receiver));

        let mut workers: Vec<Worker> = Vec::with_capacity(size);

        for id in 0..size {
            // cloning it increases the reference count
            workers.push(Worker::new(id, Arc::clone(&receiver)));
        }

        ThreadPool { workers, sender: Some(sender) }
    }

    pub fn execute<F>(&self, f: F) where F: FnOnce() + Send + 'static {
        let job = Box::new(f);

        // send function takes ownership
        // sends closure to worker
        self.sender.as_ref().unwrap().send(job).unwrap();
    }

}

impl Drop for ThreadPool {
    fn drop(&mut self) {

        // Takes the value out of the option, leaving a None in its place.
        drop(self.sender.take());

        for worker in &mut self.workers {
            println!("shutting down worker {}", worker.id);
            
            // will wait for its thread to finish

            // join takes ownership
            // we only have mutable reference of worker instances, so don't have ownership over thread
            // we need to move the thread out of the Worker instance that owns thread so join can consume the thread. 
            // if Worker holds an Option<thread::JoinHandle<()>> instead, 
            // we can call the take method on the Option to move the value out of the Some variant and 
            // leave a None variant in its place. In other words, a Worker that is running will 
            // have a Some variant in thread, and when we want to clean up a Worker, 
            // we’ll replace Some with None so the Worker doesn’t have a thread to run.

            if let Some(thread) = worker.thread.take() {
                thread.join().unwrap()
            }
        }
    }
}

struct Worker {
    id: usize, 
    thread: Option<thread::JoinHandle<()>>
}

impl Worker {
    fn new(id: usize, receiver: Arc<Mutex<mpsc::Receiver<Job>>>) -> Worker {

        // we wanna move ownership of stuff into the thread
        let thread = thread::spawn(move || loop {

            // To access the data inside the mutex, we use the lock method to acquire the lock. 
            // this call will block the current thread so it can’t do any work until it’s our turn to have the lock.
            // fails if thread with the lock panics, so we use unwrap

            // recv is what we receive from the sender, unwrap just in case
            let message = receiver.lock().unwrap().recv();
            match message {
                Ok(job) => {
                    println!("worker {id} got a job; executing.");
                    job();
                }

                Err(_) => {
                    println!("worker {id} disconnected; shutting down.");
                    break;
                }
            }            
        });

        Worker { id, thread: Some(thread) }
    }
}
