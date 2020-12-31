import numpy as np
from matplotlib import pyplot as plt


def turnscore(data):  # 将Object类型数据转换为数值数据
    """
    :param data: 原数据表
    :return: return none
    """
    for i in data.columns:
        if i == "Constitution":
            for j in range(106):
                if data[i][j] == "bad":
                    temp = np.random.randint(0, 60, 1)
                    data[i][j] = temp[0]
                elif data[i][j] == "general":
                    temp = np.random.randint(60, 80, 1)
                    data[i][j] = temp[0]
                elif data[i][j] == "good":
                    temp = np.random.randint(80, 90, 1)
                    data[i][j] = temp[0]
                elif data[i][j] == "excellent":
                    temp = np.random.randint(90, 101, 1)
                    data[i][j] = temp[0]


def ques1(data):  # 绘图表示C1和Constitution
    """
    :param data: 原数据表
    :return: return none
    """
    x = data["C1"]
    y = data["Constitution"]
    plt.title("Matplotlib demo")
    plt.xlabel("score of C1")
    plt.ylabel("score of Constitution")
    plt.scatter(x, y, c='#00CED1', alpha=0.4)
    plt.show()
