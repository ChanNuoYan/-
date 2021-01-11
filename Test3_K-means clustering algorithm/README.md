## 实验三  《k-means聚类算法》
【部分题目图片不能正常显示请在文档中下载观察】

**小组信息**

组员信息：钟昊柱（有组但单干）

组员分工：钟昊柱

指导老师：彭伟龙


**实验项目：**
实验K-Means聚类方法，并实现可视化
### 1.题目要求：

**用C++实现k-means聚类算法**

**1. 对实验二中的z-score归一化的成绩数据进行测试，观察聚类为2类，3类，4类，5类的结果，观察得出什么结论？**

**2. 由老师给出测试数据，进行测试，并画出可视化出散点图，类中心，类半径，并分析聚为几类合适。**

样例数据(x,y)数据对：

x | y
---|---
3.45 | 7.08
1.76 | 7.24
4.29 | 9.55
3.35 | 6.65
3.17 | 6.41
3.68 | 5.99
2.11 | 4.08
2.58 | 7.10
3.45 | 7.88
6.17 | 5.40
4.20 | 6.46
5.87 | 3.87
5.47 | 2.21
5.97 | 3.62
6.24 | 3.06
6.89 | 2.41
5.38 | 2.32
5.13 | 2.73
7.26 | 4.19
6.32 | 3.62

### 2.相关公式
**均值公式：**

![均值公式](https://img-blog.csdnimg.cn/20201205164837659.jpg#pic_center)

**协方差公式：**

![协方差公式](https://img-blog.csdnimg.cn/20201205164858214.jpg#pic_center)

**z-score规范化：**

![z-score规范化](https://img-blog.csdnimg.cn/2020120516490490.jpg#pic_center)

**手肘法：**

![手肘法](https://img-blog.csdnimg.cn/20210105174915942.jpg)

**欧式距离：**

![欧式距离](https://img-blog.csdnimg.cn/20210105175753684.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

**K_Means原理**

K-Means的算法流程下所示，这里对周志华教授《机器学习》一书中的插图用文字描述：

            1.首先确定K值（即你想把数据聚为几类，K值是K-Means算法中唯一的参数）；

            2.从原始数据集中随机选择K个点作为初始均值点（步骤1和2为准备工作）；

            3.依次从原始数据集中取出数据，每取出一个数据就和K个均值点分别计算距离（默认计算点间的欧氏距离），
	    和谁更近就归为这个均值点所在的簇；

            4.当步骤3结束后，分别计算各簇当前的均值点（即求该簇中所有点的平均值）；

            5.比较当前的均值点和上一步得到的均值点是否相同，如果相同，则K-Means算法结束，
	    否则，将当前的均值点替换掉之前的均值点，然后重复步骤3。

**手肘法原理**

       手肘法的核心思想是：随着聚类数k的增大，样本划分会更加精细，每个簇的聚合程度会逐渐提高，那么误差平方和SSE自然会逐渐变小。
       并且，当k小于真实聚类数时，由于k的增大会大幅增加每个簇的聚合程度，故SSE的下降幅度会很大，而当k到达真实聚类数时，
       再增加k所得到的聚合程度回报会迅速变小，所以SSE的下降幅度会骤减，然后随着k值的继续增大而趋于平缓，也就是说SSE和k的关系图是一个手肘的形状，
       而这个肘部对应的k值就是数据的真实聚类数。当然，这也是该方法被称为手肘法的原因。
       
### 3.语言
**语言：C++、Python、Markdown**

### 4.主要函数解释
**【K_Means】**

```
void ClusterMethod::k_means_Calculate(vector<vector<vector<double>>>&v)
```
设置最大迭代次数**time=50**

距离计算利用欧式距离公式
**loop** {

对每一个**Sample**计算其到聚类中心的距离**Distance**

取最近的作为其聚类结果

计算每一个**Sample**到其聚类中心的距离之和

与前一次的距离之和进行比较
{
            若距离变化<0.01
            
            则说明数据收敛
            
            不再进行迭代
                                    }
计算新的聚类中心

}

**【手肘法计算】**

```
for (int i = 0; i < SampleNum; ++i) {
            SSE += Distances[i][ClusterResult[i]] *Distances[i][ClusterResult[i]];//
}
```

**【readCSV过程】**

```
double** read()
```

```
while (getline(inFile, line))//getline(inFile, line)表示按行读取CSV文件中的数据
{
	int columns = 0;
	string field;
	istringstream sin(line); //将整行字符串line读入到字符串流sin中;
	while (sin) {
		getline(sin, field, ','); //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
		if (columns != 0 && rows != 0) {
			b[rows - 1][columns - 1] = atof(field.c_str());
		}
		columns++;
	}
	rows++;
}

```

因为原数据导出时是带有行号和列名的形式，所以在这里对第0行和对第0列采取不操作的处理方式

### 5.show

a.K_means to test2

对于第二题中归一化数据的处理：

聚类二类数据情况部分截图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109142718438.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

聚类三类数据情况部分截图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109142823968.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

聚类四类数据情况部分截图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109142911867.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

聚类五类数据情况部分截图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021010914295754.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

手肘图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021010914035362.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

【最佳K值为10】

b.K_means to data from teacher

对于彭老师在本题中给出的数据的处理：

待分类数据情况：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109143638410.png)

聚类二类数据情况截图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109144033320.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109143126936.png)

聚类三类数据情况截图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109144108887.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109143234387.png)

聚类四类数据情况截图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109144127390.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109143349297.png)

聚类五类数据情况截图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109144144747.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109143502906.png)

手肘图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109143543450.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

【最佳K值为3】

### 6.总结
本次实验对K_Means聚类算法进行了C++复现，并采用了简单的手肘法进行对K的选择，K_Means中是对聚类中心的不断更新到最后分类结果变化不大渐渐收敛的时候，生成最终的聚类结果。

并且根据SSE的表述，存在一个突然变化巨大的点作为最佳的K值，K_Means是在聚类中不断收敛的。

本次实验用C++实现的难点在于多维数组的调用赋值方面，考虑到可能存在读取并不了解的文件情况的时候，所以采用了指针对数据进行读取。

Question1：而观察聚类2、3、4、5类的结果时，容易得到聚类的结果簇越多，越可能出现簇内元素比例失衡情况，而对于106x11的归一化矩阵，根据SSE图可知，其肘部在聚类10类时出现。

Question2：观察聚类2、3、4、5类的结果时，根据SSE图可知，其肘部在聚类3类时出现，因为其样本数目比较少，所以聚类目的结果也不能超过一定的范围。本题中最佳聚类数目选择3。
