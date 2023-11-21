from collections import OrderedDict

class LRUCache:
    def __init__(self, capacity):
        self.capacity = capacity
        self.cache = OrderedDict()
        self.hits = 0
        self.misses = 0

    def refer(self, page):
        if page in self.cache:
            # If page is already present in cache, move it to the end (most recently used)
            self.cache.move_to_end(page)
            self.hits += 1
        else:
            # If page is not present in cache
            self.misses += 1
            if len(self.cache) >= self.capacity:
                # If the cache is full, remove the least recently used item (first item)
                self.cache.popitem(last=False)
            # Add the new page to the end (most recently used)
            self.cache[page] = True

    def display_stats(self):
        total_requests = self.hits + self.misses
        hit_percentage = (self.hits / total_requests) * 100 if total_requests > 0 else 0
        miss_percentage = (self.misses / total_requests) * 100 if total_requests > 0 else 0
        
        print("Page Table:")
        print("Page No.   Status")
        for page, status in self.cache.items():
            print(f"{page:^9}   {'In Memory' if status else 'Not in Memory'}")
        
        print("\nStatistics:")
        print(f"Total Requests: {total_requests}")
        print(f"Total Hits: {self.hits}  ({hit_percentage:.2f}%)")
        print(f"Total Misses: {self.misses}  ({miss_percentage:.2f}%)")

# Example usage:
if __name__ == "__main__":
    cache_capacity = 3  # Change the cache capacity as needed
    pages = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2]  # Example page reference string

    cache = LRUCache(cache_capacity)

    for page in pages:
        cache.refer(page)

    cache.display_stats()
