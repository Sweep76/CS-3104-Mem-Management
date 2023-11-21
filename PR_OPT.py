class OptimalCache:
    def __init__(self, capacity):
        self.capacity = capacity
        self.cache = []
        self.hits = 0
        self.misses = 0

    def refer(self, page, remaining_stream):
        if page in self.cache:
            self.hits += 1
        else:
            self.misses += 1
            if len(self.cache) >= self.capacity:
                index = -1
                farthest = 0
                for i, c in enumerate(self.cache):
                    if c not in remaining_stream:
                        index = i
                        break
                    else:
                        farthest = max(farthest, remaining_stream.index(c))
                        if farthest == remaining_stream.index(c):
                            index = i
                if index != -1:
                    self.cache[index] = page
            else:
                self.cache.append(page)

    def display_table(self, remaining_stream):
        print("Incoming\tPages in Memory")
        for i, page in enumerate(incomingStream):
            remaining_stream = incomingStream[i + 1:]
            self.refer(page, remaining_stream)
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

cache = OptimalCache(cache_capacity)
cache.display_table(incomingStream)
cache.display_stats()
