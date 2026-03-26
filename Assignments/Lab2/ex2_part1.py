"""
Part 1, Python Implementation
Does not use heap properties, so insert is O(1) but pop is O(n).
It stores values in a plain Python list.
"""

class MaxHeap:
    def __init__(self):
        self.heap = []   # just using a list

    def insert(self, key):
        self.heap.append(key)

    def pop(self):
        if len(self.heap) == 0:
            return None

        max_index = 0
        for i in range(1, len(self.heap)):
            if self.heap[i] > self.heap[max_index]:
                max_index = i

        max_value = self.heap[max_index]
        self.heap.pop(max_index)
        return max_value
        

if __name__ == "__main__":
    max_heap = MaxHeap()
    
    max_heap.insert(27)
    max_heap.insert(89)
    max_heap.insert(-29)
    max_heap.insert(13)
    max_heap.insert(83)
    max_heap.insert(-48)
    max_heap.insert(-9)
    max_heap.insert(-50)
    max_heap.insert(2)
    max_heap.insert(26)

    for _ in range(11):
        print(max_heap.pop())