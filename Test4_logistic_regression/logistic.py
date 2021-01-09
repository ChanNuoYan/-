#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time    : 2021/1/8 11:29
# @Author  : Adam
# @Site    : 
# @File    : Log.py
# @Software: PyCharm
import numpy as np
import matplotlib.pyplot as plt
from sympy import *
import csv


def sigmoid(x):
    # sigmoid函数
    return 1 / (1 + exp(-x))


def average(y, hx, number):
    # average计算均值
    # type_y获得y中唯一的标签值
    type_y = np.unique(y)
    # type_number获得y中标签的种类数目
    type_number = len(type_y)
    # 初始化列表
    sum_list = [0 for i in range(type_number)]
    count_list = [1 for i in range(type_number)]
    for i in range(number):
        for j in range(type_number):
            if y[i] == type_y[j]:
                sum_list[j] += hx[i]
                count_list[j] += 1
    final_average = 0
    for i in range(type_number):
        sum_list[i] = sum_list[i] / count_list[i]
        final_average += sum_list[i]
    # 获得均值
    final_average = final_average / type_number
    return final_average


def paint_sigmoid():
    # 绘图sigmoid函数
    # 预设随机x值，并根据x值获得y值
    x = np.linspace(-6, 6, 1000)
    y = []
    for i in x:
        y.append(sigmoid(i))
    ax = plt.gca()
    # 将右边 边沿线颜色设置为空 其实就相当于抹掉这条边
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')
    ax.xaxis.set_ticks_position('bottom')
    ax.yaxis.set_ticks_position('left')
    # 设置中心的为（0，0）的坐标轴
    # 指定 data 设置的bottom(也就是指定的x轴)绑定到y轴的0这个点上
    ax.spines['bottom'].set_position(('data', 0))
    ax.spines['left'].set_position(('data', 0))
    plt.plot(x, y)
    plt.show()


def update_gradient(number, theta, y, x, dimension):
    # 更新梯度函数
    # 根据数据维度新建梯度矩阵
    gradient = np.zeros(dimension)
    hx_y = []
    # 数学公式的实现
    # 更新h[x]-y[i]
    for i in range(number):
        hx_y.append((np.dot(x[i], theta)) - y[i])
    # 更新(h[x]-y)x[j]
    for i in range(dimension):
        for j in range(number):
            gradient[i] += hx_y[j] * x[j, i]
    return gradient


def handle_csv(filepath):
    # 读取训练文件
    with open(filepath, encoding='utf-8') as f:
        data = np.loadtxt(f, delimiter=",")
    final_data = data[:, 0:data.shape[1] - 1]
    final_target = data[:, data.shape[1] - 1]
    return final_data, final_target, data.shape[1], data.shape[0]


def handle_test(filepath):
    # 读取测试文件
    with open(filepath, encoding='utf-8') as f:
        data = np.loadtxt(f, delimiter=",")
    print(data.shape[0])
    print(data.ndim)
    print(data)
    print(data[0])
    exit()
    return data, len(data)


def get_test(filepath):
    test = []
    count_row = 0
    with open(filepath, 'r') as f:
        reader = csv.reader(f)
        for row in reader:
            count_row += 1
            temp = []
            for i in row:
                temp.append(float(i))
            test.append(temp)
    return test, count_row


if __name__ == '__main__':
    # 画sigmoid图
    paint_sigmoid()
    # 读取训练文件和测试文件
    filepath = 'E:/桌面/聚类2类.csv'
    test_path = 'E:/桌面/a.CSV'
    data, y, dimension, number = handle_csv(filepath)
    t, num = get_test(test_path)
    t = np.array(t)
    add = np.ones(num)
    test = np.c_[add, t]
    temp_theta = np.ones(dimension)
    add = np.ones(number)
    x = np.c_[add, data]
    theta = temp_theta.T
    res = np.zeros(dimension)
    # 设置学习率为alpha
    alpha = 0.001
    # 记录迭代次数
    time = 0
    # 迭代θ的过程
    while (res != theta).all():
        time += 1
        res = theta
        gradient = update_gradient(number, theta, y, x, dimension) / number
        new_theta = theta - alpha * gradient
        count = 0
        theta = new_theta
    hx = []
    yi = []
    # 计算每一行数据对应的预测值hx和用sigmoid测试
    for i in range(number):
        hx.append(np.dot(x[i, :], theta.T))
        yi.append(sigmoid(hx[i]))
    # 得到平均值,将数据拟合x=0轴为分界
    final_average = average(y, hx, number)
    for i in range(number):
        # 将hx到x=0附近
        hx[i] = hx[i] - final_average
        print("点数值: ", x[i, [1, dimension - 1]], "\n", "hx: ", hx[i], "\n", "yi: ", yi[i], "\n", "y_real: ", y[i])
    print("学习率α: ", alpha, "it costs time: ", time)
    for xa in test:
        actually = np.dot(theta, xa)
        hx_test = np.dot(xa, theta.T)
        y_test = sigmoid(hx_test)
        hx_test = hx_test - final_average
        print("点数值: ", xa, "\n", "hx: ", hx_test, "\n", "yi: ", y_test)
    # 判断所属类型
    if hx_test > 0:
        ("y_guess:", 1)
    else:
        ("y_guess:", 0)
    # 不同类别的点用不同颜色画
    color = ['red', 'blue']
    # 绘制测试数据点
    for i in range(number):
        plt.scatter(hx[i], yi[i], c=color[int(y[i])])
    # 绘制待分类点
    plt.scatter(hx_test, y_test, c='black')
    # 将点排序后进行连接
    hx.sort()
    yi.sort()
    # 连线
    plt.plot(hx, yi, linewidth=1)
    # 划分中线
    plt.axvline(x=0, ls='-', c='yellow')
    # 展示
    plt.show()
