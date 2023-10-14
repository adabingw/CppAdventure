use std::{
    fs,
    thread,
    time::Duration,
    io::prelude::*,
    net::{TcpListener, TcpStream},
};
use server::ThreadPool;

fn main() {
    let listener = TcpListener::bind("127.0.0.1:7878").unwrap();
    let pool = ThreadPool::new(4);

    for stream in listener.incoming().take(2) {
        let stream = stream.unwrap();

        // closures can capture values from the scope in which they’re defined
        pool.execute(|| {
            handle_connection(stream);
        });
    }

    println!("shutting down...");
}

fn handle_connection(mut stream: TcpStream) {
    // read up to 1024 bytes
    let mut buffer = [0; 1024];
    stream.read(&mut buffer).unwrap();

    let GET = b"GET / HTTP/1.1\r\n";
    let SLEEP = b"GET /sleep HTTP/1.1\r\n";
    
    let (status_line, filename) = if buffer.starts_with(GET) {
        ("HTTP/1.1 200 OK", "index.html")
    } else if buffer.starts_with(SLEEP) {
        thread::sleep(Duration::from_secs(5));
        ("HTTP/1.1 200 OK", "index.html")
    } else {
        ("HTTP/1.1 404 NOT FOUND", "404.html")
    };

    let contents = fs::read_to_string(filename).unwrap();
    let length = contents.len();
    let response = format!("{status_line}\r\nContent-Length: {length}\r\n\r\n{contents}");

    stream.write_all(response.as_bytes()).unwrap();
    stream.flush().unwrap();
}
