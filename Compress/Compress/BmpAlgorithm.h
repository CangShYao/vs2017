#pragma once
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<stack>
using namespace std;

//此结构体用来存放分段后的数据
struct Result
{
	unsigned int Len;//每组有Len个元素
	unsigned int Bt;//每个元素占Bt位
};

class BmpCompress
{
protected:
	//文件头，位图头，调色板，位图数据
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER BitmapHeader;
	RGBQUAD ipRGB[256];
	//存放位图矩阵
	unsigned char * * ImageData;
	//点阵高宽，没有它无法释放矩阵内存
	int Height;
	int Width;
	//存放S型点阵
	unsigned int* dataPoint;
public:
	//压缩分段函数
	void Compress(unsigned int n, unsigned int p[], unsigned int s[], unsigned int l[], unsigned int b[]);
	//压缩函数
	void CompressBitmap(istream& fin, ostream& fout);
	//求某一数据占多少位
	unsigned int length(int i);
	//解压函数
	void DeCompressBitmap(istream& fin, ostream& fout);
	//析构函数，用于释放内存
	~BmpCompress();
};