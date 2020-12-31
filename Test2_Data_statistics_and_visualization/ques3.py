import math


def mean(list1, num):  # 计算列表的均值
    """
    :param list1: 列特征
    :param num: 列数
    :return: 均值
    """
    mean = 0
    for i in list1:
        mean += i
    mean = mean / num
    return mean


def std(list1, mean, num):  # 计算列的方差
    """
    :param list1: 列特征
    :param mean: 列均值
    :param num: 列数
    :return: 方差
    """
    temp = 0
    for i in list1:
        temp = temp + ((i - mean) ** 2)
    std = (temp / num) ** (1 / 2)
    return std


def z_score(list1, mean, std):  # Z_SCORE归一化
    """
    :param list1: 列特征
    :param mean: 列均值
    :param std: 列方差
    :return: return none
    """
    for i in range(106):
        temp = (list1[i] - mean) / std
        list1[i] = temp


def ques3(data):
    """
    :param data: 原数据表
    :return: 处理后的新数据表
    """
    newdata = data.copy()
    newdata.drop(newdata.tail(3).index, inplace=True)  # 从尾部去掉n行
    for i in newdata.columns:
        judge = 0
        for j in newdata[i].values:  # 排除掉nan数据
            if math.isnan(j):
                judge += 1
                break
        if judge == 1:
            continue
        tempmean = mean(newdata[i].values, 106)
        tempstd = std(newdata[i].values, tempmean, 106)
        z_score(newdata[i].values, tempmean, tempstd)
    return newdata
