# This code initializes a MemoryManager with an initial list of memory blocks. 
# It then iterates through a list of processes, attempting to allocate each process using the First Fit algorithm. 
# It prints the process size, allocation status, and the updated memory state after each allocation attempt.

# You can adjust the processes list to test different process sizes 
# and see how the memory manager allocates them based on the available memory blocks.


class MemoryManager:
    def __init__(self, memory_blocks):
        self.memory_blocks = memory_blocks

    def best_fit(self, process_size):
        suitable_blocks = [i for i, block in enumerate(self.memory_blocks) if block >= process_size]
        if not suitable_blocks:
            print(f"No suitable block found for {process_size}KB process.")
            return False
        best_fit_index = min(suitable_blocks, key=lambda x: self.memory_blocks[x])
        allocated_size = self.memory_blocks[best_fit_index]
        self.memory_blocks[best_fit_index] -= process_size
        print(f"Allocated {process_size}KB in block {best_fit_index}. Remaining space: {allocated_size - process_size}KB")
        print(f"Updated memory state: {self.memory_blocks}\n")
        return True

# Example usage:
memory_blocks = [100, 50, 200, 80] # memory allocation blocks available
memory_manager = MemoryManager(memory_blocks)

processes = [120, 30, 60, 90] # processes to be inserted 

for process in processes:
    print(f"Process size: {process}KB")
    memory_manager.best_fit(process)
