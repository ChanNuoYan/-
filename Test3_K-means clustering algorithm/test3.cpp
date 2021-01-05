// test3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include"readcsv.h"
#include"K_means.h"
using namespace std;
int main()
{
	vector<std::vector<std::vector<double> > >v;
	ClusterMethod a;
	double** data = read();
	int clusternum;
	int judge=1;
	while (judge) {
		//cout << "请输入聚类数量:" << endl;
		//cin >> clusternum;
		for (int clusternum = 2; clusternum < 6; ++clusternum) {
			a.GetClusterd(v, data, clusternum, 20, 2);
		}

		judge = 0;
		/*
		for (int i = 0; i < v.size(); ++i)
		{
			cout << "第" << i + 1 << "类" << endl;
			cout << "该类总共" << v[i].size() << "个元素" << endl;
			for (int j = 0; j < v[i].size(); ++j)
			{
				for (int k = 0; k < v[i][j].size(); ++k)
				{
					cout << v[i][j][k] << " ";
				}
				cout << endl;
			}
		}
		
		cout << "Continue?" << "y" << " or " << "n" << endl;
		string j;
		cin >> j;
		if (j == "y") {
			continue;
		}
		else if (j == "n") {
		judge = 0;
		}
			*/
	}

}
