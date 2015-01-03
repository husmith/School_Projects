## This file is an outline for Project 5 (Web Crawler) in CIS 211, Winter 2014

#  -- Hannah Smith --

from sys import argv, exit, stderr
from urllib.request import urlopen
from urllib.parse import urlparse, urlunparse, urljoin
from html.parser import HTMLParser



class Collector(HTMLParser):
    def __init__(self, url):
        'initializes parser, the url, and a list'
        HTMLParser.__init__(self)
        self.url = url
        self.links = []

    def handle_starttag(self, tag, attrs):
        'collect hyperlink URLs in their absolute format'
        if tag =='a':
            for attr in attrs:
                if attr[0] =='href':
                    # construct absolute URL
                    absolute = urljoin(self.url, attr[1])
                    if absolute[:4] =='http':
                        # collect HTTP URLs
                        self.links.append(absolute)
    def getLinks(self):
        'returns hyperlinks URLs in their absolute format'
        return self.links
    pass


def crawl(site, graph, dist):
    print("crawling", site, file=stderr)
    graph[site] = set()
    s = urlunparse(('http',site,'',None, None, None))
    try:
        response = urlopen(s)
    except Exception as e:
        print(e)
        return None
    content = response.read().decode()
    collect = Collector(s)
    collect.feed(content)
    for link in collect.getLinks():
        if link not in graph:
            link = urlparse(link)
            desc = link.netloc
            graph[site].add(desc)
            if dist > 1:
                if desc not in graph:
                    crawl(desc,graph,dist-1)
    return graph
    

def print_graph(g):
    "Print a graph using one node per line"
    print("{")
    for x in g:
        print("  ",x,":",g[x],",")
    print("}")
    
## Comamnd Line API

if __name__ == "__main__":
    if len(argv) < 2:
        print("Usage:  python3 crawler.py url dist")
        exit(2)
        
    parts = urlparse(argv[1])
    dist = int(argv[2])
    
    if parts.scheme not in ['', 'http', 'https']:
        print("URL must use http or https")
        exit(1)
    site = parts.path if parts.netloc == '' else parts.netloc
    
    g = crawl(site, {}, dist)  
    print_graph(g)

