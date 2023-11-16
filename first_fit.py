# This code initializes a MemoryManager with an initial list of memory blocks. 
# It iterates through a list of processes, attempting to allocate each process using the Next Fit algorithm. 
# It prints the process size, allocation status, and the updated memory state after each allocation attempt, 
# considering the next available block from the previous allocation. 
# Adjust the processes list to test different process sizes.


class MemoryManager:
    def __init__(self, memory_blocks):
        self.memory_blocks = memory_blocks

    def first_fit(self, process_size):
        for i, block in enumerate(self.memory_blocks):
            if block >= process_size:
                allocated_size = block
                self.memory_blocks[i] -= process_size
                print(f"Allocated {process_size}KB in block {i}. Remaining space: {allocated_size - process_size}KB")
                print(f"Updated memory state: {self.memory_blocks}\n")
                return True
        print(f"No suitable block found for {process_size}KB process.")
        return False

# Example usage:
memory_blocks = [100, 50, 200, 80] # memory allocation blocks available
memory_manager = MemoryManager(memory_blocks)

processes = [120, 30, 60, 90] # processes to be inserted 

for process in processes:
    print(f"Process size: {process}KB")
    memory_manager.first_fit(process)
