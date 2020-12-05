#include<vector>
#include"string.h"
#include<iostream>
#include<fstream>
#include"io.h"
#include <windows.h>
#include<array>
#include"stdio.h"
#include<map>
#include<cmath>
#include<string>
#include<map>
using namespace std;
typedef map<string, int> UDT_MAP_INT_CSTRING;
#define FILE_BUFFER_LENGTH 30000
UDT_MAP_INT_CSTRING enumMap;
std::map<string, int> personnel;
template <class T> void ClearVector(vector<T>& v);
template <class T>
void ClearVector(vector<T>& v)//vector释放
{	vector<T>vtTemp;//临时变量
	vtTemp.swap(v);
	v.shrink_to_fit();
	v.~vector<T>();
}
string countve(vector<string>&vec) {//作为字典，统计vector中某元素出现的次数，返回次数最多的元素
	map<string, int>mapvec;
	for (int i = 0; i < vec.size(); i++) {
		map<string, int>::iterator iter = mapvec.find(vec[i]);
		if (iter != mapvec.end()) {
			mapvec.find(vec[i])->second = (mapvec.find(vec[i])->second) + 1;
		}
		else {
			mapvec[vec[i]] = 1;
		}
	}
	int ct = 0;
	string temp;
	map<string, int>::iterator iter;
	iter = mapvec.begin();
	int count=1;
	for (auto&iter : mapvec) {
		if ((iter.second )> ct) {
			ct = iter.second;
			temp = iter.first;
	}
	}
	return temp;
}
void givemeaning(string *a, string *target) {//循环赋值
	for (int i = 0; i < 16; i++) {
		target[i] = a[i];
	}
}
	int minDistance2(string s1, string s2)//LD算法
	{
		int m = s1.length();
		int n = s2.length();
		vector<vector<int>> dp(m + 1, vector<int>(n + 1));
		for (int i = 1; i <= m; i++)//<=说明遍历的次数是m-1+1次，即字符串的长度
		{
			dp[i][0] = i;
		}
		for (int j = 1; j <= n; j++)
		{
			dp[0][j] = j;
		}
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				//if (s1[i] == s2[j])//运行结果不对，因为第i个字符的索引为i-1
				if (s1[i - 1] == s2[j - 1])
				{
					dp[i][j] = dp[i - 1][j - 1];//第i行j列的步骤数等于第i-1行j-1列，因为字符相同不需什么操作，所以不用+1
				}
				else
				{
					dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + 1);//+1表示经过了一次操作
				}
			}
		}
		return dp[m][n];
		dp.~vector();
		ClearVector(dp);
	}
void changesn(string(*table)[16],int length) {//性别、号码、身高规范化
	for (int i = 1; i < length; i++) {
		if (table[i][3] == "girl") {
			table[i][3] = "female";
		}
		else if (table[i][3] == "boy") {
			table[i][3] = "male";
		}
		if ((table[i][0].size())<6) {
			table[i][0] = to_string(202000 + atoi(table[i][0].c_str()));
		}
		if (table[i][4] != "") {
			float compare = atof(table[i][4].c_str());
			if (compare > 100) {
				float temp;
				temp = atof(table[i][4].c_str()) / 100;
				table[i][4] = to_string(temp);
			}
		}
	}
}
double turnscore(string a) {//把pm成绩数学化
	if (a == "bad") {
		return 60;
	}
	else if (a == "general") {
		return 75;
	}
	else if (a == "good") {
		return 85;
	}
	else if (a == "excellent") {
		return 95;
	}
}
void compareline(string *table, vector<int>&num, string *table2) {//访问两个数组，填补空数据和识别异常数据
	for (int i = 0; i < 16; i++) {
		if (table[i] == table2[i]&&table[i]!="") {
			continue;
		}
		else if (table[i] == ""&&table2[i] != "") {
			table[i] = table2[i];
		}
		else if (table[i] != ""&&table2[i] == "") {
			table2[i] = table[i];
		}
		else if (table[i] != table2[i]) {
			num.push_back(i);
		}
	}
}
void findnumline(string *table1, string(*table2)[16], int length, vector<int>&num, int judge) {//以num或者name为权重，到另一张表找到类似的元素行
	for (int i = 1; i < length; i++) {
		if (table1[judge] == table2[i][judge]) {
			num.push_back(i);
		}
	}
}
void show(string(*table)[16], int length) {//展示数组
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < 16; j++) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
}
void comparedata(string(*table)[16], string(*table2)[16],int length,int len) {//去冗余
	vector<int>del;
	for (int i = 1; i < length; i++) {//从第一行开始
		for (int j = i+1; j < length&&j<i+2; j++) {//和偏移2以内的行进行比较
			vector<int>temp;
			vector<int>lin;
			if (table[i][0] == table[j][0]) {//当num相同的时候
				if (minDistance2(table[i][1], table[j][1]) < 3) {//是同一个人的时候
					compareline(table[i], temp, table[j]);//每行比较是不是有不同的信息，如果有把不同的信息所在的下标记录下来
					del.push_back(j);
					if (temp.size() == 0) {//数据没差别的时候
						break;
					}
					else {//数据有差别的时候
						findnumline(table[i], table2, len,lin, 0);//找到一样的号码所在的行
						for (int t = 0; t < temp.size(); t++) {//如果temp中还有元素的话
							vector<string>now;
							now.push_back(table[i][(temp[t])]);//根据temp中的列号把 i j还有table2的lin行中temp列元素放入now
							now.push_back(table[j][(temp[t])]);
							for (int cou = 0; cou < lin.size(); cou++) {
								now.push_back(table2[(lin[cou])][temp[t]]);
							}
							table[i][(temp[t])] = countve(now);
							table[j][(temp[t])] = table[i][(temp[t])];
							for (int cou = 0; cou < lin.size(); cou++) {
								table2[(lin[cou])][(temp[t])] = table[i][(temp[t])];
							}
							ClearVector(now);
						}
					}
					continue;
				}
				else {
					break;
				}
			}
			if (minDistance2(table[i][1], table[j][1]) < 3) {
				if (i>0&&table[i][0] == table[i - 1][0]) {
					table[i][0] = table[j][0];
				}
				compareline(table[i], temp, table[j]);
				del.push_back(j);
				if (temp.size() == 0) {//数据没差别的时候
					continue;
				}
				else {//数据有差别的时候
					findnumline(table[i], table2, len,lin, 1);
					for (int t = 0; t < temp.size(); t++) {
						vector<string>now;
						now.push_back(table[i][(temp[t])]);
						now.push_back(table[j][(temp[t])]);
						for (int cou = 0; cou < lin.size(); cou++) {
							now.push_back(table2[(lin[cou])][(temp[t])]);
						}
						table[i][temp[t]] = countve(now);
						for (int cou = 0; cou < lin.size(); cou++) {
							table2[(lin[cou])][(temp[t])] = table[i][(temp[t])];
						}
						now.~vector();
						ClearVector(now);
					}
					continue;
				}
			}
			lin.~vector();
			temp.~vector();
			ClearVector(lin);
			ClearVector(temp);
		}
	}
	for (int coun = 0; coun < del.size(); coun++) {
		cout << "del:" << del[coun] << endl;
	}

	sort(del.begin(), del.end());
	for (int count = 0; count < del.size(); count++) {
		if (count+1 == del.size()) {
			for (int judge = del[count]; judge < length-1; judge++) {
				for (int row = 0; row < 16; row++) {
					table[judge + 1 - count - 1][row] = table[judge + 1][row];
				}
			}
			break;
		}
		for (int judge = del[count]; judge < del[count + 1] ; judge++) {
			for (int row = 0; row < 16; row++) {
				table[judge + 1 - count - 1][row] = table[judge + 1][row];
			}
		}
	}
	for (int count = length - del.size(); count < length; count++) {
		for (int judge = 0; judge < 16; judge++) {
			table[count][judge] = "";
		}
	}
	ClearVector(del);
}
void whenlackmes(string *table1, string *table2) {
	for (int i = 2; i < 16; i++) {
		//若另一张表有数据则填补
		if (table1[i] == ""&&table2[i] != "") {
			table1[i] = table2[i];
			continue;
		}
		else if (i == 4) {
			float a;
			float b;
			a = atof(table1[i].c_str());
			b = atof(table2[i].c_str());
			if (a!= b) {
				table1[i] = "";
			}
		}
		//若两个数据不同
		else if (table2[i] != table1[i]) {
			table1[i] = "";
		}
	}
}
void everyavg(string (*table)[16],vector<double>&avg,int length)//找均值
{
	float * temp = new float[11];
	float * count = new float[20];
	for (int i=1; i < length; i++) {
		for (int j = 4; j < 15; j++) {
			if (table[i][j] != "") {
				temp[j-4] = temp[j-4] + atof(table[i][j].c_str());
				count[j-4] = count[j-4] + 1;
			}
		}
	}
	for (int k = 0; k < 10; k++) {
		if (count[k] == 0) {
			avg[k] = 0;
			continue;
		}
		avg[k] = temp[k] / count[k];
	}
	delete temp;
	delete count;
}
string avgpm(string(*table)[16],int length) {//pm均值
	float sum=0;
	float count=0;
	for (int i = 0; i < length; i++) {
		if (table[i][0] != "") {
			if (table[i][15] == "bad") {
				sum += 60;
				count++;
			}
			else if (table[i][15] == "general") {
				sum += 75;
				count++;
			}
			else if (table[i][15] == "good") {
				sum+=85;
				count++;
			}
			else if (table[i][15] == "excellent") {
				sum+=95;
				count++;
			}
		}
	}
	float avg=sum/count;
	if (avg > 95 || avg == 95) {
		return "excellent";
	}
	else if ((avg > 85) || avg == 85) {
		return "good";
	}
	else if (avg > 75 || avg == 75) {
		return"general";
	}
	else {
		return "bad";
	}
}
void lackline(string (*Tt)[16], string (*Ex)[16], int t1,int t2,string (*newtable)[16]) {//两表比较并且生成新表
	int point;
	int Ct = 0, Ce = 0;
	int count = 0;
	while (Ct < t2 && Ce < t1) {
		if (Ct == 0 && Ce == 0) {
			givemeaning(Tt[Ct], newtable[count]);
			Ce++;
			Ct++;
			count++;
		}
		if (Ex[Ce][0] == ""&&Tt[Ct][0]== "") {
			break;
		}
		else if (Ex[Ce][0] == ""&&Tt[Ct][0] != "") {
			givemeaning(Tt[Ct], newtable[count]);
			Ct++;
			count++;
			continue;
		}
		else if (Ex[Ce][0] != ""&&Tt[Ct][0] == "") {
			givemeaning(Ex[Ce], newtable[count]);
			Ce++;
			count++;
			continue;
		}
		if (Ex[Ce][0] == Tt[Ct][0]) {
			whenlackmes(Ex[Ce], Tt[Ct]);
			givemeaning(Ex[Ce], newtable[count]);
			Ce++;
			Ct++;
			count++;
			continue;
		}
		if (Ex[Ce][0] > Tt[Ct][0]) {
			givemeaning(Tt[Ct], newtable[count]);
			Ct++;
			count++;
			continue;
		}
		else if (Ex[Ce][0] < Tt[Ct][0]) {
			givemeaning(Ex[Ce], newtable[count]);
			Ce++;
			count++;
			continue;
		}
	}
}
void handle(string(*excel)[16],int length) {//处理新表，若空值则用均值填充
	vector<double>avg(11);
	string pm = avgpm(excel, length); 
	everyavg(excel, avg,length);
	for (int i = 1; i < length; i++) {
		if (excel[i][0] != "") {
			for (int j = 4; j < 16; j++) {
				if (excel[i][j] == ""&&j < 15 && avg[j - 4] == 0) {
					continue;
				}
				else if (excel[i][j] == ""&&j<15) {
					excel[i][j] = to_string(avg[j - 4]);
				}
				else if (excel[i][j] == ""&&j == 15) {
					excel[i][j] = pm;
				}
			}
		}
	}
	ClearVector(avg);
}




void ques1(string(*excel)[16],int length) {
	cout << ">>>>>>>>>>>>>>>>>>>>run ques1<<<<<<<<<<<<<<<<<<<<" << endl;
	vector<float>sum(10,0);
	vector<float>count(10,0);
	for (int i = 1; i < length; i++) {
		if (excel[i][2] == "Beijing") {
			for (int j = 5; j < 15; j++) {
				if (excel[i][j] == "") {
					continue;
				}
				sum[j-5] = sum[j-5] + atof(excel[i][j].c_str());
				count[j-5] = count[j-5] + 1;
			}
		}
	}
	int c = 0;
	while (c < 10) {
		if (count[c] == 0) {
			cout << "AVG" << c + 1 << ":" << count[c] << endl;
			c++;
			continue;
		}
		cout << "AVG"<<c+1<<":" << sum[c] / count[c]<<endl;
		c++;
	}
	cout <<" >>>>>>>>>>>>>>>>>>>>ques1 end<<<<<<<<<<<<<<<<<<<<" << endl;
	ClearVector(sum);
	ClearVector(count);
}
//查找Student中家乡在广州、C1>80,C10>9
void ques2(string(*excel)[16],int length) {
	cout << ">>>>>>>>>>>>>>>>>>>>run ques2<<<<<<<<<<<<<<<<<<<<" << endl;
	int count = 0;
	for (int i = 1; i < length; i++) {
		int temp1= atoi(excel[i][5].c_str());
		int temp2= atoi(excel[i][13].c_str());
		if (excel[i][2] == "Guangzhou"&& excel[i][3] == "male"&& temp1 > 80 && temp2 > 9) {
			count++;
		}
	}
	cout << "answer:" << count<<endl;
	cout <<" >>>>>>>>>>>>>>>>>>>>ques2 end<<<<<<<<<<<<<<<<<<<<" << endl;
}
//平均值
double average(vector<double>&x, double len)
{
	double sum = 0;
	for (int i = 0; i < len; i++) // 求和
	{
		sum += x[i];
	}
	return sum / len; // 得到平均值
}
//求方差
double variance(vector<double>&x, int len)
{
	double variance = 0;
	double avg = average(x, len);
	for (int i = 0; i < len; i++) {
		variance = variance + pow((x[i] - avg), 2);
	}
	return variance / len;
}
//求标准差
double sdev(vector<double>&x, int len) {
	return sqrt(variance(x, len));
}
//建立数组GuangZhou和ShangHai
void buildtable(string(*a)[16], vector<double>&gzsum, vector<double>&shsum,int length) {
	for (int i = 0; i < length; i++) {
		if (a[i][3] == "male") {
			if (a[i][2] == "Guangzhou"&&a[i][15]!="") {
				gzsum.push_back(turnscore(a[i][15]));
			}
			else if (a[i][2] == "Shanghai"&&a[i][15] != "") {
				shsum.push_back(turnscore(a[i][15]));
			}
		}
	}
}
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
void ques3(string(*a)[16]) {
	cout <<">>>>>>>>>>>>>>>>>>>>run ques3<<<<<<<<<<<<<<<<<<<<" << endl;
	vector<double>gz;
	vector<double>sh;
	double gzz;
	double shz;
	buildtable(a, gz, sh,110);
	gzz = z_score(gz);
	shz = z_score(sh);
	if (gzz > shz) {
		cout << "Guangzhou girl nb"<<endl;
	}
	else if (gzz < shz) {
		cout << "Shanghai girl nb"<<endl;
	}
	else {
		cout << "equl"<<endl;
		cout << " >>>>>>>>>>>>>>>>>>>>ques3 end<<<<<<<<<<<<<<<<<<<<" << endl;
	}
	gz.~vector();
	sh.~vector();
	ClearVector(gz);
	ClearVector(sh);
}
void collect(string(*table)[16],vector<double>&score,int pos,int length) {
	if (pos != 15&&pos>3) {
		for (int i = 0; i < length; i++) {
			if (table[i][pos] == "") {
				continue;
			}
			else if (table[i][pos] != "") {
				score.push_back(atof(table[i][pos].c_str()));
			}
		}
	}
	else if (pos == 15) {
		for (int i = 0; i < length; i++) {
			if (table[i][pos] == "bad") {
				score.push_back(60);
			}
			else if (table[i][pos] == "general") {
				score.push_back(75);
			}
			else if (table[i][pos] == "good") {
				score.push_back(85);
			}
			else if (table[i][pos] == "excellent") {
				score.push_back(95);
			}
			else {
				continue;
			}
		}
	}
}
void coco(vector<double>&ssco, vector<double>&psco, float & r) {
	float avs;
	float avp;
	float des;
	float dep;
	avs = average(ssco, ssco.size());
	avp = average(psco, psco.size());
	des = sdev(ssco, ssco.size());
	dep = sdev(psco, psco.size());
	float temp=0;
	float x;
	float y;
	for (int i = 0; i < psco.size(); i++) {
		x = (ssco[i] - avs) / des;
		y = (psco[i] - avp) / dep;
		temp += x * y;
	}
	r = temp / float(psco.size());
}
void ques4(string(*table)[16],int length) {
	cout << ">>>>>>>>>>>>>>>>>>>>run ques4<<<<<<<<<<<<<<<<<<<<" <<endl;
	vector<double>psco;
	collect(table, psco, 15, length);
	float  r;
	for (int i = 5; i < 15; i++) {
		vector<double>ssco;
		collect(table, ssco, i, length);
		if (ssco.size() >1) {
			coco(ssco, psco, r);
			cout << "第" << i - 4<< "门成绩跟PM的相关系数:" << r << endl;
		}
		else {
			cout << "第" << i - 4 << "门成绩跟PM的相关系数有误" << endl;
		}
		ClearVector(ssco);
	}
	ClearVector(psco);
	cout << " >>>>>>>>>>>>>>>>>>>>ques4 end<<<<<<<<<<<<<<<<<<<<" << endl;
}
void getAllFiles(string path, vector<string>& files) {
	long   hFile = 0;                                           //file handle
	struct _finddata_t fileinfo;  	                            //file information  
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*.txt").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("/").append(fileinfo.name));
					getAllFiles(p.assign(path).append("/").append(fileinfo.name), files);
				}
			}
			else
			{
				files.push_back(p.assign(fileinfo.name));             //only save filename
			}
		} while (_findnext(hFile, &fileinfo) == 0);               //read the next filename
		_findclose(hFile);
	}

}
char* UTF8ToGB(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}
void readInToMatrix(fstream &in, string FilePath, string (*data)[16]) {
	in.open(FilePath, ios::in);
	if (!in.is_open()) {
		cout << "Can not find " << FilePath << endl;
		system("pause");
	}
	string buff;
	int i = 0;//line
	while (getline(in, buff)) {
		int pos = 0;
		int temp = 0;
		// string->char *
		string s_input = (string)buff.c_str();
		for (int row = 0; row < 16; row++) {
			temp = s_input.find(",", pos);
			if (temp - pos == 0) {
				data[i][row] = "";
				pos = temp+1;
				continue;
			}
			data[i][row].assign(s_input,pos, temp - pos);
			pos = temp+1;
		}
		i++;
	}
	in.close();
	cout << "get data from file" << endl;
}
int main() {
	string path = "E:\\x.txt";
	string qath = "E:\\1.CSV";
	vector<string>fileName;
	vector<string> filename;
	string newtable[120][16];
	string data[100][16];
	string cas[99][16];
	fstream in;
	fstream on;
	getAllFiles(qath, fileName);
	getAllFiles(path, filename);
	ClearVector(fileName);
	ClearVector(filename);
	readInToMatrix(on, qath, cas);
	readInToMatrix(in, path, data);
	changesn(cas,99);
	changesn(data, 100);
	comparedata(cas, data,99,100);
	comparedata(data, cas,100,99);
	lackline(data, cas,100,99, newtable);
	handle(newtable,110);
	show(newtable, 110);
	ques1(newtable,110);
	ques2(newtable,110);
	ques3(newtable);
	ques4(newtable,110);
	ofstream outFile; // 创建流对象
	outFile.open("D://test.csv", ios::out); // 打开文件
	for (int i = 0; i < 110; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			outFile << newtable[i][j] << ',';
		}
		outFile << endl;
	}
	cout << "data write in"<<endl;
	outFile.close(); // 关闭文件
}
