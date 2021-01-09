#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time    : 2020/11/18 10:24
# @Author  : Adam
# @Site    : 
# @File    : Log.py
# @Software: PyCharm
import pandas as pd
import ques5
import ques4
import ques3
import ques2
import ques1
if __name__ == '__main__':
    data=pd.read_csv("D://test.csv", usecols = [5,6,7,8,9,10,11,12,13,14,15])
    ques1.turnscore(data)
    data[["C2","C7","C8","C9","Constitution"]]=data[["C2","C7","C8","C9","Constitution"]].astype(float)
    ques1.ques1(data)
    ques2.ques2(data)
    newdata=ques3.ques3(data)
    newtable=ques4.ques4(newdata)
    ques5.ques5(newtable)


