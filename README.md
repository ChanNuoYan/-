# Data_Mining
## PS：子文件夹中也包含了各自实验的README文件
## 实验一《多源数据集成、清洗和统计》

**小组信息**

组员信息：钟昊柱（有组但单干）

组员分工：钟昊柱

指导老师：彭伟龙


**实验题目**： 广州大学某班有同学100人，现要从两个数据源汇总学生数据。第一个数据源在数据库中，第二个数据源在txt文件中，两个数据源课程存在缺失、冗余和不一致性，请用C/C++/Java程序实现对两个数据源的一致性合并以及每个学生样本的数值量化。

**数据不一致性**：两个数据源中的数据单位、种类、数据类型存在不一致。

| 相异数据/数据源|Txt|  Csv|
|:----:|:----:|:----:|
|**性别**|male/female|boy/girl|
|**身高**  |m为单位  |cm为单位  |
|**id**|从1开始的纯数字|以202为前缀的纯数字|

**数据冗余性**：同一个数据源可能储存了相同的学生数据，存在冲突

**数据缺失**：某个数据源中可能存在某个学生的某一项信息缺失的情况

### 1.题目要求：

**1. 学生中家乡在Beijing的所有课程的平均成绩。**

**2. 学生中家乡在广州，课程1在80分以上，且课程9在9分以上的男同学的数量。(备注：该处做了修正，课程10数据为空，更改为课程9)**

**3. 比较广州和上海两地女生的平均体能测试成绩，哪个地区的更强些？**

**4. 学习成绩和体能测试成绩，两者的相关性是多少？（九门课的成绩分别与体能成绩计算相关性）**
### 2.相关公式：
**均值公式：**

![均值公式](https://img-blog.csdnimg.cn/20201205164837659.jpg#pic_center)

**协方差公式：**

![协方差公式](https://img-blog.csdnimg.cn/20201205164858214.jpg#pic_center)

**z-score规范化：**

![z-score规范化](https://img-blog.csdnimg.cn/2020120516490490.jpg#pic_center)

**相关性：**

![相关性](https://img-blog.csdnimg.cn/20201205164911317.jpg#pic_center)

### 3.语言
**语言：C++、Markdown**
### 4.主要函数解释
**LD算法**
因为示例中存在着名字相差不大，可以辨别是同一个人的数据，所以用LD算法来判断名字，若偏差在一定范围之内，认定为同一个人，然后便于对**数据冗余**进行操作处理
LD算法原理：
算法目的：计算出两字符序列的编辑距离，同时也能求出两序列的匹配序列

假设：
比对的俩序列为：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109101909513.png)

则两序列的长度分别为len(A) = n，Len(B)=m；
LD(A,B)：字符串A和字符串B的编辑距离，即将字符串A转换为字符串B所用的最少字符操作数。
LD(A,B)=0表示两个字符串完全一样。
LD(i,j)=LD(a1a2……ai,b1b2……bj)，其中0≤i≤N，0≤j≤M

算法步骤：

初始化算法分数矩阵H，使行i表示字符ai，列j表示字符bj；

计算矩阵中每一项的LD(i, j)：

若ai = bj，则LD(i, j) = LD(i-1, j-1) 取左上角的值

若ai ≠ bj，则LD(i, j) = Min( LD(i-1, j-1), LD(i-1, j), LD(i, j-1) ) +1

回溯，从矩阵右下角开始：

若ai=bj，则回溯到左上角单元格；

若ai≠bj，回溯到左上角、上边、左边中值最小的单元格，若有相同最小值的单元格，优先级按照左上角、上边、左边的顺序。

根据回溯路径，写出匹配字符串：

若回溯到左上角单元格，将ai添加到匹配字串A‘，将bj添加到匹配字串B’；

若回溯到上边单元格，将ai添加到匹配字串A’，将_添加到匹配字串B’；

若回溯到左边单元格，将_添加到匹配字串A’，将bj添加到匹配字串B’。

矩阵右下角的值即为俩序列的编辑距离，回溯结果为全部匹配序列。

示例：

**A=GGATCGA，B=GAATTCAGTTA**

评分矩阵：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109102059262.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

回溯：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109102135508.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

结果：
LD(A,B) = 5;

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109102244248.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)
```
int minDistance2(string s1, string s2)//LD算法
```
**模仿字典**
冗余数据中存在非空但不相等的数据，利用vector存储两张表中该列的数据，再用模仿字典统计出现最多次数的数据，作为最后使用的数据。
```
string countve(vector<string>&vec) //作为字典，统计vector中某元素出现的次数，返回次数最多的元素
```
**双表联动去冗余**

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109101350688.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

因为对一个表进行处理的话，手上的数据是有限的，所以在对一表进行处理的同时对另外一个表进行对比。
冗余部分
如果遇到有相同特征但数据不同的条目，从中进行字典统计，从中选择出现次数更多的数据的条目，并且记录下冗余部分的索引号，在索引号统计完毕后，从低索引号开始往高索引号进行移动，若遇到了新的要去冗余的部分，则此之后的数据条目往前的偏移量+1.

```
void comparedata(string(*table)[16], string(*table2)[16],int length,int len) //去冗余
```
**当存在缺失值**
当一个表存在缺失值的时候，对另一个表的相似条目进行对比，若数据非空则用非空一方的数据进行填充，数据为空则不处理。
```
void whenlackmes(string *table1, string *table2)
```
**处理新表，用均值填充**
当我们得到一张新的表的时候，我们因为也存在一些两张表都没有的数据，所以合并的新表中部分数据也将为空。对这部分数据进行均值填充。
```
void handle(string(*excel)[16],int length)
```
**Z_Score**
该部分进行Z-score归一化处理，计算出其方差与均值后进行归一化，并返回归一化的结果。
```
//Z-Score
double z_score(vector<double>&gzsum) {
	double sum = 0;
	double avg = average(gzsum, gzsum.size());
	double var = variance(gzsum, gzsum.size());
	for (int i = 0; i < gzsum.size(); i++) {
		sum = sum+(gzsum[i] - avg) / var;
	}
	return sum / gzsum.size();
}
```
**UTF8ToGB**
原题目中的Constitution列是存在中文数据的，预先调试的时候发现读取是会根据源文件的编码类型UTF8而出现问题，所以用这一步将原本是UTF8编码的数据转换为GB。
```
char* UTF8ToGB(const char* utf8)
```

### 5.show

a.原数据源情况：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109134940161.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109135123529.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

**观察数据源数据分布情况从而拟定处理方案
Ⅰ存在冗余数据
Ⅱ存在缺失数据**

b.题目完成情况：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109135419908.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

c.处理后的新表情况：

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021010913572545.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

### 6.总结
**数据预处理：**去数据冗余、处理数据缺失、处理数据的不一致性，比较关键的点在于**【数据不一致性】的区分和同步、【数据冗余】的判断、【数据缺失】的完善方法选择**
对两个数据源的数据进行整合清洗，对数据预处理有了进一步的认识，同时知道了数据预处理的步骤：数据清洗、数据集成、数据变换和数据规约。
本次实验主要涉及数据清洗，如针对数据数值上的各种异常情况，根据数值异常情况的不同，对数据清理具体包括移除异常值、替换缺失值、将干扰数据进行平滑处理以及纠正不一致数据。在进行数据清洗等预处理操作的之前，首先对数据模型进行一定的观察，分辨数据的表达方式的异同点，再进行读取操作的选择、统一类型的选择等。

## 实验二    《数据统计和可视化》

**小组信息**

组员信息：钟昊柱（有组但单干）

组员分工：钟昊柱

指导老师：彭伟龙

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
**问题1:以课程1成绩为x轴，体能成绩为y轴，画出散点图**



![q1](https://img-blog.csdnimg.cn/20210109102655394.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)



**问题2：以5分为间隔，画出课程1的成绩直方图**



![q2](https://img-blog.csdnimg.cn/20210109102725195.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

**问题3：对每门成绩进行z-score归一化，得到归一化的数据矩阵**



![q3](https://img-blog.csdnimg.cn/20210109102848375.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

**问题4：计算出100x100的相关矩阵，并可视化出混淆矩阵**



![q4](https://img-blog.csdnimg.cn/20210109102917167.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

**问题5：根据相关矩阵，找到距离每个样本最近的三个样本，得到100x3的矩阵**



![q5](https://img-blog.csdnimg.cn/20210109103047501.jpg)

### 6.总结
利用matplotlib画图工具的同时熟悉画图的过程，在对数据处理的同时，因为经历了第一个过程，所以知道C10列绝对是空列，所以在读取操作数据的同时避开了**NAN**数据，并且对于**Constitution**列的转换为数值类型的处理，采用的是随机范围数，因为如果采用单一值替代的方法，数值是停留在几条直线上的。

计算相关矩阵的时候，对于行列操作需要清晰，虽然调用库函数更加简单，但是在体验这个过程的时候，也能根据公式以及过程去捋清代码思路。

## 实验三  《k-means聚类算法》
【部分题目图片不能正常显示请在文档中下载观察】

**小组信息**

组员信息：钟昊柱（有组但单干）

组员分工：
钟昊柱【K_means代码实现】
朱天昊【可视化类图、手肘法】

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

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210111173210181.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109143126936.png)

聚类三类数据情况截图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021011117332854.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109143234387.png)

聚类四类数据情况截图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210111173347229.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210109143349297.png)

聚类五类数据情况截图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210111173406248.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzYxODA1,size_16,color_FFFFFF,t_70)

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

## 实验四《逻辑回归二分类》
【部分图片可能在下方无法正常显示，请下载观察】

**小组信息**

组员信息：钟昊柱（有组但单干）

组员分工：钟昊柱

指导老师：彭伟龙


**实验题目**： 
学习sigmoid函数和逻辑回归算法。将实验三.2中的样例数据用聚类的结果打标签{0，1}，并用逻辑回归模型拟合。


### 1.题目要求：

**1. 学习并画出sigmoid函数**

**2. 设计梯度下降算法，实现逻辑回归模型的学习过程。**

**3. 根据给定数据（实验三.2），用梯度下降算法进行数据拟合，并用学习好的模型对(2,6)分类。**
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

即如果该csv只有一行但其有3列，但是读取后生成的数组数据中，它是作为3行存在的

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

### 6.总结
实验难点在于对逻辑回归公式中梯度下降的理解，但只要抓住了公式的要点，明白了每一步迭代的过程是为了找到最优解，原理理解参考了【winrar_setup.rar】先生的博客https://blog.csdn.net/weixin_39445556/article/details/83661219
，以及【吴恩达】先生的机器学习课程【梯度下降】、【多元梯度下降】。其实整个过程就是完善h(x)=求和[θixi]),当i=0时,xi=1，即θ0x0作为常数项存在。
