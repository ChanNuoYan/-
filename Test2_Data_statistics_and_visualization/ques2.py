#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time    : 2020/11/18 10:43
# @Author  : Adam
# @Site    : 
# @File    : Log.py
# @Software: PyCharm
from matplotlib import pyplot as plt


def ques2(data):  # 绘图
    """
    :param data: 原数据表
    :return: return none
    """
    plt.hist(x=data.C1, bins=20, color='steelblue', edgecolor='black', range=(0, 100))
    plt.xlabel("C1")
    plt.ylabel("Score")
    plt.title("Score Histogram Of C1")
    plt.show()
