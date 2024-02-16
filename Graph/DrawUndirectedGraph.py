import matplotlib.pyplot as plt
import networkx as nx

# 获取用户输入的顶点数、边数和每条边的信息
num_vertices = int(input("Enter number of vertices: "))
num_edges = int(input("Enter number of edges: "))

edges = []
for i in range(num_edges):
    edge = list(map(int, input(f"Enter edge {i+1} (format: vertex1 vertex2 weight): ").split()))
    edges.append((edge[0], edge[1], {'weight': edge[2]}))

# 创建图形
G = nx.Graph()

# 添加所有的顶点
G.add_nodes_from(range(1, num_vertices + 1))

# 添加边
G.add_edges_from(edges)

# 绘制图形,默认为用直线连接
pos = nx.spring_layout(G)#nx.spring_layout(G)是一种布局
nx.draw(G, pos, with_labels=True)

labels = nx.get_edge_attributes(G, 'weight')
# 绘制边的权重
nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)

# 绘制边，将边显示为曲线
#for edge in G.edges():
#   nx.draw_networkx_edges(G, pos, edgelist=[edge], connectionstyle=f"arc3,rad=0.3", arrows=True)

# 显示节点标签
nx.draw_networkx_labels(G, pos)

plt.show()