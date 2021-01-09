## 实验四《逻辑回归二分类》

**实验题目**： 
学习sigmoid函数和逻辑回归算法。将实验三.2中的样例数据用聚类的结果打标签{0，1}，并用逻辑回归模型拟合。


### 1.题目要求：

**1. 学习并画出sigmoid函数**

**2. 设计梯度下降算法，实现逻辑回归模型的学习过程。**

**3. 根据给定数据（实验三.2），用梯度下降算法进行数据拟合，并用学习好的模型对(2,6)分类。**

### 2.相关公式：

**sigmoid**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109105338821.png)

**参数θ：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109104925784.png)

**损失函数：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109105017445.png)

**对损失函数求偏导数：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109105052603.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

**梯度公式：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109105123420.png)

### 3.语言

**语言：Python、Markdown**

### 4.主要函数解释

**sigmoid函数**

对sigmoid数学函数进行函数实现

```
sigmoid(x)
```

**绘sigmoid函数图像**

随机获得从-6~6之间5000个点，作为x值

根据x值代入sigmoid函数获得y值

```
paint_sigmoid()
```

**更新梯度gradient**

首先损失函数偏导数公式中【(h[x]-y)】部分

再乘以各个特征值下的数据，并按特征值求和

返回值为g即gradient

```
update_gradient(number, theta, y, x, dimension)
```

**读取训练文件**

调用numpy.loadtxt函数对csv数据文件进行读取

```
handle_csv(filepath)
```

**读取测试文件**

此处有两个函数，具体为什么写了两个，是因为在测试的过程中发现了np.loadtxt函数对于只有一行的csv文件是不能正确读取，

即如果该csv有3列，但是读取后生成的数组数据中，它是作为3行存在的

故正常使用的读取测试文件为以下函数

```
get_test(filepath)
```

**迭代θ过程**

    # 迭代θ的过程
    while (res != theta).all():
        time += 1
        res = theta
        gradient = update_gradient(number, theta, y, x, dimension) / number
        new_theta = theta - alpha * gradient
        count = 0
        theta = new_theta

### 5.show
问题1：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109101245619.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70#pic_center)

问题3：

训练点集分布情况【数值表示】：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109101245534.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109101245446.jpg#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109101245403.jpg#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109101245271.jpg#pic_center)

测试点集分布情况【数值表示】：

α=0.01：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109101245228.jpg#pic_center)

α=0.001：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109101245227.jpg#pic_center)

测试点集和训练点集分布情况【图像表示】：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109101245614.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70#pic_center)

### 5.总结
实验难点在于对逻辑回归公式中梯度下降的理解，但只要抓住了公式的要点，明白了每一步迭代的过程是为了找到最优解，原理理解参考了【winrar_setup.rar】先生的博客https://blog.csdn.net/weixin_39445556/article/details/83661219
，以及【吴恩达】先生的机器学习课程【梯度下降】、【多元梯度下降】。
