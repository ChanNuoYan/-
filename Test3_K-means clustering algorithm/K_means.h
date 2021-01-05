#pragma once
#include"time.h"
class ClusterMethod
{
private:
	double **Sample;//输入
	double **Centers;//储存聚类中心
	double **Distances;//距离矩阵
	int SampleNum;//样本数
	int ClusterNum;//聚类数
	int FeatureNum;//每个样本特征数
	int *ClusterResult;//聚类结果
	int MaxIterationTimes;//最大迭代次数

public:
	void GetClusterd(vector<std::vector<std::vector<double> > >&v, double** feateres, int ClusterNum, int SampleNum, int FeatureNum);//外部接口

private:
	void Initialize(double** feateres, int ClusterNum, int SampleNum, int FeatureNum);//类初始化
	void k_means(vector<vector<vector<double> > >&v);//算法入口
	void k_means_Initialize();//聚类中心初始化
	void k_means_Calculate(vector<vector<vector<double> > >&v);//聚类计算

};


//v 保存分类结果 v[i][j][k]表示第i类第j个数据第k个特征（从0开始）
//feateres 输入数据 feateres[i][j]表示第i个数据第j个特征（i，j从0开始）
//ClusterNum 分类数
//SampleNum 数据数量
//FeatureNum 数据特征数

void ClusterMethod::GetClusterd(vector<std::vector<std::vector<double> > >&v, double** feateres, int ClusterNum, int SampleNum, int FeatureNum)
{
	Initialize(feateres, ClusterNum, SampleNum, FeatureNum);//初始化类内数据

	k_means(v);//k算法
}


//类内数据初始化
void ClusterMethod::Initialize(double** feateres, int ClusterNumz, int SampleNumz, int FeatureNumz)
{	//类内数据赋值
	Sample = feateres;
	FeatureNum = FeatureNumz;
	SampleNum = SampleNumz;
	ClusterNum = ClusterNumz;
	MaxIterationTimes = 50;//最大迭代次数

	Centers = new double*[ClusterNum];//定义聚类中心二维数组

	for (int i = 0; i < ClusterNum; ++i)//横坐标表示第x个聚类中心
	{
		Centers[i] = new double[FeatureNum];//纵坐标表示聚类中心特征值
	}

	Distances = new double*[SampleNum];//定义距离二位数组
	for (int i = 0; i < SampleNum; ++i)//横坐标表示第x个数据
	{
		Distances[i] = new double[ClusterNum];//纵坐标表示该行数据与某一类中心的距离
	}

	ClusterResult = new int[SampleNum];//定义聚类结果，数值表示类别
}


//算法入口
void ClusterMethod::k_means(vector<vector<vector<double> > >&v)
{
	k_means_Initialize();//初始化

	k_means_Calculate(v);//聚类计算
}


//初始化聚类中心
void ClusterMethod::k_means_Initialize()//以原数据类中的前n个作为初始化的中心【n取决于要聚的类数目】
{
	for (int i = 0; i < ClusterNum; ++i)
	{
		//Centers[i] = Sample[i];

		for (int k = 0; k < FeatureNum; ++k)
		{
			Centers[i][k] = Sample[i][k];
		}
	}
}

//聚类过程
void ClusterMethod::k_means_Calculate(vector<vector<vector<double>>>&v)
{
	double J = DBL_MAX;//目标函数

	int time = MaxIterationTimes;//迭代次数

	while (time)

	{
		double now_J = 0;//上次更新距离中心后的目标函数
		--time;//迭代次数减1

		//距离初始化
		for (int i = 0; i < SampleNum; ++i)
		{
			for (int j = 0; j < ClusterNum; ++j)//距离行列置0
			{
				Distances[i][j] = 0;

			}
		}
		//计算欧式距离
		for (int i = 0; i < SampleNum; ++i)
		{
			for (int j = 0; j < ClusterNum; ++j)//第i行数据与第j个聚类中心的距离
			{
				for (int k = 0; k < FeatureNum; ++k)
				{
					Distances[i][j] += abs(pow(Sample[i][k], 2) - pow(Centers[j][k], 2));//第k个特征之间的距离
						//	cout << "欧氏距离:"<<Distances[i][j] << endl;
				}
				now_J += Distances[i][j];//now_J决断函数，用于衡量聚类的变化情况，相邻的两次变化不大于0.01我们把他们看作已收敛
			}
		}

		if (J - now_J < 0.01)//目标函数不再变化结束循环
		{
			break;
		}
		J = now_J;//将now_J赋值给J

		//a存放临时分类结果
		vector<vector<vector<double> > > a(ClusterNum);
		for (int i = 0; i < SampleNum; ++i)//对每一行
		{

			double min = DBL_MAX;
			for (int j = 0; j < ClusterNum; ++j)//对每一列
			{
				if (Distances[i][j] < min)
				{
					min = Distances[i][j];
					ClusterResult[i] = j;//获得该行数据与距离最小的聚类中心的ID
				}
			}

			vector<double> vec(FeatureNum);
			for (int k = 0; k < FeatureNum; ++k)//获得该行的数据
			{
				vec[k] = Sample[i][k];
			}
			a[ClusterResult[i]].push_back(vec);//将该行的数据置入其所属类列之下
			//	v[ClusterResult[i]].push_back(vec);这里不能这样给v输入数据，因为v没有初始化大小
		}
		v = a;

		//计算新的聚类中心

		for (int j = 0; j < ClusterNum; ++j)//聚类中心初始化
		{
			for (int k = 0; k < FeatureNum; ++k)
			{
				Centers[j][k] = 0;
			}
		}


		for (int j = 0; j < ClusterNum; ++j)//计算新的聚类中心
		{
			for (int k = 0; k < FeatureNum; ++k)
			{
				for (int s = 0; s < v[j].size(); ++s)
				{
					Centers[j][k] += v[j][s][k];//求和聚类第j类第k个特征的总和
				}
				if (v[j].size() != 0)
				{
					Centers[j][k] /= v[j].size();//均值
				}
			}
		}
	}
	double SSE=0;
	for (int i = 0; i < SampleNum; ++i) {
		SSE += Distances[i][ClusterResult[i]] *Distances[i][ClusterResult[i]];
	}
	cout << "SSE:" << SSE << endl;
	//输出聚类中心
	
	for (int j = 0; j < ClusterNum; ++j)
	{
		cout << "聚类中心" <<j+1<<":"<< endl;
		for (int k = 0; k < FeatureNum; ++k)
		{
			cout <<Centers[j][k] <<" ";
		}
		cout << endl;
	}
	
}
