import matplotlib.pyplot as plt
import networkx as nx

# 获取用户输入的顶点数、边数和每条边的信息
num_vertices = int(input("Enter number of vertices: "))
num_edges = int(input("Enter number of edges: "))

edges = []
for i in range(num_edges):
    edge = list(map(int, input(f"Enter edge {i+1} (format: start_vertex end_vertex): ").split()))
    edges.append(edge)

# 创建有向图
G = nx.DiGraph()#如果两点之间可以有多条边，就用MultiGraph

# 添加所有的顶点
G.add_nodes_from(range(1, num_vertices + 1))

# 添加边
G.add_edges_from(edges)

# 使用 spring_layout 排列节点位置
pos = nx.spring_layout(G)

# 绘制图形
nx.draw(G, pos,with_labels=True, arrows=True)
plt.show()