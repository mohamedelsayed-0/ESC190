import heapq
import matplotlib.pyplot as plt
import numpy as np

# Grid Cell Types
EMPTY = 0
WALL = 1
WEIGHTED = 2
START = 3
GOAL = 4
VISITED = 5
PATH = 6

# Movement: Up, Down, Left, Right
DIRECTIONS = [(0, 1), (0, -1), (1, 0), (-1, 0)]

class Grid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = np.zeros((height, width), dtype=int)
        self.costs = np.ones((height, width), dtype=float)
        self.start = None
        self.goal = None

    def set_wall(self, x, y):
        self.cells[y][x] = WALL
        self.costs[y][x] = float('inf')

    def set_weighted(self, x, y, cost=5.0):
        self.cells[y][x] = WEIGHTED
        self.costs[y][x] = cost

    def set_start(self, x, y):
        self.start = (x, y)
        self.cells[y][x] = START

    def set_goal(self, x, y):
        self.goal = (x, y)
        self.cells[y][x] = GOAL

    def is_in_bounds(self, x, y):
        return 0 <= x < self.width and 0 <= y < self.height

    def is_passable(self, x, y):
        return self.cells[y][x] != WALL

    def get_cost(self, x, y):
        return self.costs[y][x]

    def get_neighbors(self, x, y):
        neighbors = []
        for dx, dy in DIRECTIONS:
            nx, ny = x + dx, y + dy
            if self.is_in_bounds(nx, ny) and self.is_passable(nx, ny):
                neighbors.append((nx, ny))
        return neighbors

def heuristic(a, b):
    # Manhattan distance for 4-directional movement
    return abs(a[0] - b[0]) + abs(a[1] - b[1])

def reconstruct_path(came_from, current):
    path = []
    while current in came_from:
        path.append(current)
        current = came_from[current]
    return path[::-1]

def dijkstra(grid):
    start = grid.start
    goal = grid.goal
    
    pq = [(0, start)]
    came_from = {}
    cost_so_far = {start: 0}
    visited_nodes = []

    while pq:
        current_cost, current = heapq.heappop(pq)

        if current == goal:
            break

        if current != start:
            visited_nodes.append(current)

        for next_node in grid.get_neighbors(*current):
            new_cost = cost_so_far[current] + grid.get_cost(*next_node)
            if next_node not in cost_so_far or new_cost < cost_so_far[next_node]:
                cost_so_far[next_node] = new_cost
                came_from[next_node] = current
                heapq.heappush(pq, (new_cost, next_node))

    path = reconstruct_path(came_from, goal)
    return path, visited_nodes, cost_so_far.get(goal, float('inf'))

def a_star(grid):
    start = grid.start
    goal = grid.goal
    
    pq = [(0, start)]
    came_from = {}
    cost_so_far = {start: 0}
    visited_nodes = []

    while pq:
        _, current = heapq.heappop(pq)

        if current == goal:
            break

        if current != start:
            visited_nodes.append(current)

        for next_node in grid.get_neighbors(*current):
            new_cost = cost_so_far[current] + grid.get_cost(*next_node)
            if next_node not in cost_so_far or new_cost < cost_so_far[next_node]:
                cost_so_far[next_node] = new_cost
                priority = new_cost + heuristic(next_node, goal)
                came_from[next_node] = current
                heapq.heappush(pq, (priority, next_node))

    path = reconstruct_path(came_from, goal)
    return path, visited_nodes, cost_so_far.get(goal, float('inf'))

def visualize(grid, d_path, d_visited, d_cost, a_path, a_visited, a_cost):
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 7))
    
    def draw_grid(ax, title, path, visited, cost):
        # Create a display copy of the grid
        display = np.copy(grid.cells)
        
        # Mark visited nodes
        for x, y in visited:
            if display[y][x] == EMPTY:
                display[y][x] = VISITED
            elif display[y][x] == WEIGHTED:
                # Keep weighted color hint but mark as visited if desired
                # For clarity, let's just mark empty cells as visited
                pass
        
        # Mark path
        for x, y in path:
            if display[y][x] not in [START, GOAL]:
                display[y][x] = PATH

        # Color map
        # 0: Empty (White), 1: Wall (Black), 2: Weighted (Brown/Gray), 
        # 3: Start (Green), 4: Goal (Red), 5: Visited (Light Blue), 6: Path (Yellow)
        colors = ['white', 'black', '#8B4513', 'green', 'red', '#ADD8E6', 'orange']
        cmap = plt.matplotlib.colors.ListedColormap(colors)
        bounds = [0, 1, 2, 3, 4, 5, 6, 7]
        norm = plt.matplotlib.colors.BoundaryNorm(bounds, cmap.N)

        ax.imshow(display, cmap=cmap, norm=norm)
        ax.set_title(f"{title}\nNodes Explored: {len(visited)}\nPath Cost: {cost:.1f}\nPath Length: {len(path)}")
        ax.set_xticks(np.arange(-.5, grid.width, 1), minor=True)
        ax.set_yticks(np.arange(-.5, grid.height, 1), minor=True)
        ax.grid(which='minor', color='gray', linestyle='-', linewidth=0.5)
        ax.tick_params(which='both', bottom=False, left=False, labelbottom=False, labelleft=False)

    draw_grid(ax1, "Dijkstra's Algorithm", d_path, d_visited, d_cost)
    draw_grid(ax2, "A* Search", a_path, a_visited, a_cost)

    # Legend
    from matplotlib.patches import Patch
    legend_elements = [
        Patch(facecolor='white', edgecolor='gray', label='Empty Cell (Cost: 1)'),
        Patch(facecolor='black', label='Wall'),
        Patch(facecolor='#8B4513', label='Weighted Terrain (Cost: 5)'),
        Patch(facecolor='green', label='Start'),
        Patch(facecolor='red', label='Goal'),
        Patch(facecolor='#ADD8E6', label='Explored Node'),
        Patch(facecolor='orange', label='Shortest Path')
    ]
    fig.legend(handles=legend_elements, loc='lower center', ncol=4, bbox_to_anchor=(0.5, -0.05))
    
    plt.tight_layout()
    plt.subplots_adjust(bottom=0.15)
    plt.savefig('/Users/mohamedelsayed/Desktop/Y1S2/ESC190/Assignments/Agentic_Studio/comparison.png')

def create_example_grid():
    width, height = 30, 20
    grid = Grid(width, height)
    
    grid.set_start(2, 2)
    grid.set_goal(27, 17)
    
    # Vertical wall with a gap
    for y in range(0, 15):
        grid.set_wall(10, y)
    
    # Another vertical wall with a gap at the top
    for y in range(5, 20):
        grid.set_wall(20, y)
        
    # Weighted region in the middle
    for x in range(11, 19):
        for y in range(8, 12):
            grid.set_weighted(x, y, cost=10.0)

    # Some random obstacles
    grid.set_wall(5, 5)
    grid.set_wall(5, 6)
    grid.set_wall(6, 5)

    return grid

if __name__ == "__main__":
    grid = create_example_grid()
    
    print("Running Dijkstra's Algorithm...")
    d_path, d_visited, d_cost = dijkstra(grid)
    print(f"Dijkstra: Found path of cost {d_cost} with {len(d_visited)} nodes explored.")
    
    print("\nRunning A* Search...")
    a_path, a_visited, a_cost = a_star(grid)
    print(f"A*: Found path of cost {a_cost} with {len(a_visited)} nodes explored.")
    
    visualize(grid, d_path, d_visited, d_cost, a_path, a_visited, a_cost)
