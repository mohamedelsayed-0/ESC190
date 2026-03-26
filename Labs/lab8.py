import random

graph = {
    0: [1, 2],
    1: [2],
    2: [0, 3],
    3: [0]
}

n = len(graph)

steps = 10000

current = 0
visits = [0] * n

for _ in range(steps):
    visits[current] += 1
    current = random.choice(graph[current])

fractions = [v / steps for v in visits]

print("Visit counts:", visits)
print("Visit fractions:")
for i in range(n):
    print(f"Vertex {i}: {fractions[i]:.4f}")