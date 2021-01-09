## 实验二    《数据统计和可视化》

**实验项目：**
基于实验一中清洗后的数据练习统计和视化操作，100个同学（样本），每个同学有11门课程的成绩（11维的向量）；那么构成了一个100x11的数据矩阵。以你擅长的语言C/C++/Java/Python/Matlab，编程计算。
### 1.题目要求：
**1. 请以课程1成绩为x轴，体能成绩为y轴，画出散点图。**

**2. 以5分为间隔，画出课程1的成绩直方图。**


**3. 对每门成绩进行z-score归一化，得到归一化的数据矩阵。**


**4. 计算出100x100的相关矩阵，并可视化出混淆矩阵。（为避免歧义，这里“协相关矩阵”进一步细化更正为100x100的相关矩阵，100为学生样本数目，视实际情况而定）**

**5. 根据相关矩阵，找到距离每个样本最近的三个样本，得到100x3的矩阵（每一行为对应三个样本的ID）输出到txt文件中，以\t,\n间隔。**

### 2.相关公式
**均值公式：**

![均值公式](https://img-blog.csdnimg.cn/20201205164837659.jpg#pic_center)

**协方差公式：**

![协方差公式](https://img-blog.csdnimg.cn/20201205164858214.jpg#pic_center)

**z-score规范化：**

![z-score规范化](https://img-blog.csdnimg.cn/2020120516490490.jpg#pic_center)

**相关性：**

![相关性](https://img-blog.csdnimg.cn/20201205164911317.jpg#pic_center)
### 3.语言
**语言：Python、Markdown**
### 4.主要函数解释
**【分数转换】**

```
turnscore(data)
```


因为原数据中存在**Constitution**列是**Object**类型数据，需要转换成**Float数值类型数据**，对于每个评级 **[bad,general,good,excellent]** ，利用**np.random.randint(min,max,1)** 对分数进行转换。

**【去掉NAN数据】**

```
for j in data[i].values:#排除掉nan数据
            if math.isnan(j) :
                  break
 ```
 因为对于原文件有补缺失的操作，所以如果存在NAN可以直接直接排除掉。


 **【均值、方差、Z-Score归一化】**

 函数对于数学公式进行复现


 **【相关矩阵】**

 相关矩阵：**i行j列数据**表示原来**第i行和第j行的相关系数**
 首先分别得到**协方差矩阵**和**方差列表**
 再通过**协方差和方差**的计算得到**相关系数**
 ```
 table(data)
 ```


**【最接近的三个样本】**

将得到的相关矩阵中每行对绝对值abs进行排序
得到的前三个值就是最接近的样本
从而得到最接近的三个样本构成的矩阵
  ```
  sort(array)
  其中：
  list1.append(sorted(array[i],reverse = True))
  ```

### 5.结果show
问题1:      
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109102655394.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)
问题2：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109102725195.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)
问题3：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109102848375.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)
问题4：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109102917167.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)
问题5：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109103047501.jpg)
### 6.总结
利用matplotlib画图工具的同时熟悉画图的过程，在对数据处理的同时，因为经历了第一个过程，所以知道C10列绝对是空列，所以在读取操作数据的同时避开了**NAN**数据，并且对于**Constitution**列的转换为数值类型的处理，采用的是随机范围数，因为如果采用单一值替代的方法，数值是停留在几条直线上的。

计算相关矩阵的时候，对于行列操作需要清晰，虽然调用库函数更加简单，但是在体验这个过程的时候，也能根据公式以及过程去捋清代码思路。

