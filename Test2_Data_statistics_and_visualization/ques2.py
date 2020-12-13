from matplotlib import pyplot as plt
def ques2(data):#绘图
    plt.hist(x=data.C1,bins=20,color='steelblue',edgecolor = 'black',range=(0,100))
    plt.xlabel("C1")
    plt.ylabel("Score")
    plt.title("Score Histogram Of C1")
    plt.show()