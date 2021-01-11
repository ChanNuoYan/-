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
