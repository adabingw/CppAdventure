import os
import random
import re
import sys

DAMPING = 0.85
SAMPLES = 10000


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python pagerank.py corpus")
    corpus = crawl(sys.argv[1])
    # print(corpus)
    # print(corpus.keys())
    ranks = sample_pagerank(corpus, DAMPING, SAMPLES)
    print(f"PageRank Results from Sampling (n = {SAMPLES})")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")
    ranks = iterate_pagerank(corpus, DAMPING)
    print(f"PageRank Results from Iteration")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")


def crawl(directory):
    """
    Parse a directory of HTML pages and check for links to other pages.
    Return a dictionary where each key is a page, and values are
    a list of all other pages in the corpus that are linked to by the page.
    """
    pages = dict()

    # Extract all links from HTML files
    for filename in os.listdir(directory):
        if not filename.endswith(".html"):
            continue
        with open(os.path.join(directory, filename)) as f:
            contents = f.read()
            links = re.findall(r"<a\s+(?:[^>]*?)href=\"([^\"]*)\"", contents)
            pages[filename] = set(links) - {filename}

    # Only include links to other pages in the corpus
    for filename in pages:
        pages[filename] = set(
            link for link in pages[filename]
            if link in pages
        )

    return pages


def transition_model(corpus, page, damping_factor):
    """
    Return a probability distribution over which page to visit next,
    given a current page.

    With probability `damping_factor`, choose a link at random
    linked to by `page`. With probability `1 - damping_factor`, choose
    a link at random chosen from all pages in the corpus.
    """
    probability = {}
        
    if len(corpus[page]) < 1: 
        # no links, choose randomly
        for key in corpus.keys(): 
            probability[key] = 1 / len(corpus.keys())
    else: 
        # probability = (1 - damp) / num_pages + damp / num_links
        random_factor = (1 - damping_factor) / len(corpus.keys())
        not_random_factor = damping_factor / len(corpus[page])

        for key in corpus.keys():
            if key not in corpus[page]:
                # if page doesn't point to said page
                probability[key] = random_factor
            else:
                probability[key] = not_random_factor + random_factor
                
    return probability


def sample_pagerank(corpus, damping_factor, n):
    """
    Return PageRank values for each page by sampling `n` pages
    according to transition model, starting with a page at random.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """

    samples = corpus.copy()
    
    # clear dictionary
    for i in samples:
        samples[i] = 0
    page = None

    for j in range(n):
        if page:
            # use transition
            transition = transition_model(corpus, page, damping_factor)
            list_of_transition = list(transition.keys())
            transition_w = [transition[i] for i in transition]
            # random.choices(sequence, weights=None, cum_weights=None, k=1)
            rand = random.choices(list_of_transition, transition_w, k = 1)
            page = rand[0]
        else:
            # sample dun exist, random
            page = random.choice(list(corpus.keys()))

        # count each sample
        samples[page] += 1

    # turn sample count to percentage
    for sample in samples:
        samples[sample] /= n

    return samples



def iterate_pagerank(corpus, damping_factor):
    """
    Return PageRank values for each page by iteratively updating
    PageRank values until convergence.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    num_pages = len(corpus)
    old = {}
    new = {}

    # rank: 1 / num_pages for each page
    for page in corpus:
        old[page] = 1 / num_pages

    # repeat until converges
    while True:
        for page in corpus:
            temp = 0
            for link in corpus:
                # if links to our page
                if page in corpus[link]:
                    # print(corpus[link])
                    # temp = temp + old_rank / links_in_corpus[link]
                    temp += (old[link] / len(corpus[link]))
                # if no links, equal distribution
                if len(corpus[link]) == 0:
                    # temp = temp + old_rank / num_pages
                    temp += (old[link]) / num_pages
            temp *= damping_factor
            temp += (1 - damping_factor) / num_pages

            new[page] = temp

        difference = max([abs(new[x] - old[x]) for x in old])
        if difference < 0.001:
            break
        else:
            old = new.copy()

    return old


if __name__ == "__main__":
    main()
