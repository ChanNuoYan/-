#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time    : 2020/12/24 18:22
# @Author  : Adam
# @Site    : 
# @File    : Log.py
# @Software: PyCharm
import csv

import matplotlib.pyplot as plt

with open('E:/桌面/4/聚类5类.csv')as f:
    f_csv = csv.reader(f)
    count = -1
    temp = 0
    colour = ['b', 'g', 'r', 'orange','purple']
    for row in f_csv:
        if(float(row[0])==0):
            count+=1
            continue
        plt.scatter(row[0], row[1], marker='*', s=8, c=colour[count])
    plt.show()
