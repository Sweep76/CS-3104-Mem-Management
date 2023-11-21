from collections import OrderedDict

class LRUCache:
    def __init__(self, capacity):
        self.capacity = capacity
        self.cache = OrderedDict()
        self.hits = 0
        self.misses = 0

    def refer(self, page):
        if page in self.cache:
            self.cache.move_to_end(page)
            self.hits += 1
        else:
            self.misses += 1
            if len(self.cache) >= self.capacity:
                self.cache.popitem(last=False)
            self.cache[page] = True

    def display_table(self):
        print("Incoming\tPages in Memory")
        for page in incomingStream:
            self.refer(page)
            print(page, end="\t\t")
            for p in self.cache:
                print(p, end="\t")
            print()

    def display_stats(self):
        total_requests = self.hits + self.misses
        hit_percentage = (self.hits / total_requests) * 100 if total_requests > 0 else 0
        miss_percentage = (self.misses / total_requests) * 100 if total_requests > 0 else 0
            
        print("\nPage Faults:", self.misses)
        print("Hits:", self.hits)
        print("Hit Percentage:", f"{hit_percentage:.2f}%")
        print("Miss Percentage:", f"{miss_percentage:.2f}%")

# Driver code
incomingStream = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1]
cache_capacity = 3

cache = LRUCache(cache_capacity)
cache.display_table()
cache.display_stats()
