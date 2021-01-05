#pragma once
#include <iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;
double** read() {
	double** b;
	b = new double*[106];
	for(int i=0;i<106;i++) {
		b[i] = new double[11];
	}
	ifstream inFile("E://test.csv", ios::in);
	int rows = 0;
	string line;
	string field;
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
	inFile.close();
	cout << "共读取了：" << rows << "行" << endl;
	cout << "读取数据完成" << endl;
	return b;
}
