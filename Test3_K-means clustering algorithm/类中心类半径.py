import math
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Circle
from numpy.random.tests import data

MIN_DISTANCE = 0.00001

# 获取文件
print('请输入类数(2次)')
i = str(input())
filename1 = 'C:/Users/Administrator/Desktop/机挖/聚类'
filename2 = '类.csv'
filename3 = 'C:/Users/Administrator/Desktop/机挖/聚类中心'
filename4 = '.csv'
path1 = filename1 + i + filename2
path2 = filename3 + i + filename4
# ==========================================
data = np.loadtxt(path1, delimiter=',')
data1 = np.loadtxt(path2, delimiter=',')

# ==========================================
count = -1
count1 = -1
colour = ["ro", "bo", "co", "yo", "go"]
length = int((input()))
# 圆心坐标
r = [0, 0, 0, 0, 0]
a = []
b = []
for j in range(0, length * 2):
    if data1[j, 0] == 0:
        count1 += 1
        continue
    a.append(data1[j, 0])
    b.append(data1[j, 1])
    plt.plot(a, b, 'mD')

# 聚类点坐标
for i in range(0, 20 + length):
    if data[i, 0] == 0:
        count += 1
        continue
    # 聚类坐标
    x = data[i, 0]
    y = data[i, 1]
    plt.plot(x, y, colour[count])  # 打点
    p2 = np.array([x, y])
    # 计算最大半径
    p1 = np.array([a[count], b[count]])
    p3 = p2 - p1
    temp = math.hypot(p3[0], p3[1])
    if temp > r[count]:
        r[count] = float(temp)

# 画圆
for i in range(length):
    theta = np.arange(0, 2 * np.pi, 0.01)
    o = a[i] + r[i] * np.cos(theta)
    p = b[i] + r[i] * np.sin(theta)
    plt.plot(o, p, 'black')

plt.show()
