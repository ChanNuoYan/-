import csv

import matplotlib.pyplot as plt

with open('E:/桌面/4/SSE.csv')as f:
    f_csv = csv.reader(f)
    x=[]
    y=[]
    for row in f_csv:
        x.append(row[0])
        y.append(row[1])
    plt.plot(x, y, color='g', linewidth=2.0, linestyle='-')
    plt.show()