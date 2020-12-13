import numpy as np
from matplotlib import pyplot as plt
import math
def table(data):
    newtable = np.zeros((106, 106), dtype=float)
    list0 = []
    mean = []
    var=[]
    for i in range(106):
        templist = []
        tempsum = 0
        for j in data:
            templist.append(data[j][i])
        for k in templist:#求每一行的总和
            if math.isnan(k):
                continue
            tempsum += k
        tempsum = tempsum / 11#求每行的均值
        mean.append(tempsum)#均值放入mean
        list0.append(templist)#把每一行的值放入list0
        difference=0#差值
        for j in range(11):#对每一列
            if math.isnan(list0[i][j]):
                continue
            difference+=(list0[i][j]-mean[i])**2#每列（每个值-平均值）**2
        var.append((difference/11))#除以11得到方差
    for i in range(106):#对x行
        for j in range(106):#对y列
            EXY = 0
            for k in range(11):#对数值内部的k列
                judge = 0
                if math.isnan(list0[i][k]):
                    judge += 1
                    continue
                EXY += list0[i][k] * list0[j][k]#求得鸡和
            EXY = EXY / 11#求得EXY
            COV = EXY - (mean[i]) * (mean[j])#求得COV
            newtable[i][j] = COV
    for i in range(106):
        for j in range(106):
            newtable[i][j]=newtable[i][j]/((var[i]*var[j])**(1/2))
    return newtable
def paint(correlation_matrix):
    plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
    plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号
    fig = plt.figure()  # 调用figure创建一个绘图对象
    ax = fig.add_subplot(111)
    cax = ax.matshow(correlation_matrix, vmin=-1, vmax=1)  # 绘制热力图，从-1到1
    fig.colorbar(cax)  # 将matshow生成热力图设置为颜色渐变条
    ax.set_title("相关矩阵")
    ax.set_xlabel("ID")
    ax.set_ylabel("ID")
    plt.savefig('C:/Users/羊小猪/PycharmProjects/testpython')
    plt.show()
def ques4(data):
    a=table(data)
    paint(a)
    return a
