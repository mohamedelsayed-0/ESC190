class CircularQueue:
    def __init__(self,capacity):
        self.data = [None]*capacity 
        self.begin = 0
        self.end = 0
        self.size = 0

    def enqueue(self, val):
        self.data[self.end]=val
        self.end = (self.end + 1) % len(self.data) #makes it a wrap n go back
        self.size+=1

    def dequeue (self):
        val = self.data[self.begin]
        self.data[self.begin] = None
        self.begin = (self.begin +1)% len(self.data)
        self.size-=1
        return val 
    
    def __repr__(self):
        items = []
        current = self.begin
        for _ in range(self.size):
            items.append(self.data[current])
            current = (current + 1) % len(self.data)
        return "CircularQueue(" + repr(items) + ")"
    
    def __lt__(self, other):
        i = self.begin
        j = other.begin
        for _ in range(min(self.size, other.size)):
            if self.data[i] != other.data[j]:
                return self.data[i] < other.data[j]
            i = (i + 1) % len(self.data)
            j = (j + 1) % len(other.data)

        return self.size < other.size
q = CircularQueue(5)
q.enqueue(10)
q.enqueue(12)
q.enqueue(7)
print("after 3 enq:", q, q.data, q.begin, q.end, q.size)

print("deq:", q.dequeue())
print("after deq:", q, q.data, q.begin, q.end, q.size)

q.enqueue(1)
q.enqueue(6)  
print("after wrap enq:", q, q.data, q.begin, q.end, q.size)
q.enqueue(99)
print("after enqueue 99:", q, q.data, q.begin, q.end, q.size)

q1 = CircularQueue(5)
q1.enqueue(1)
q1.enqueue(5)
q1.enqueue(5)

q2 = CircularQueue(5)
q2.enqueue(2)
q2.enqueue(1)
q2.enqueue(5)

q3 = CircularQueue(6)
q3.enqueue(2)
q3.enqueue(5)
q3.enqueue(10)
q3.enqueue(12)

q4 = CircularQueue(5)
q4.enqueue(11)
q4.enqueue(2)

print(q1 < q2)  # True (1 < 2)
queues = [q3, q1, q4, q2]
print(sorted(queues))
