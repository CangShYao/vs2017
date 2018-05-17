#include "BmpAlgorithm.h"

//压缩分段函数
void BmpCompress::Compress(unsigned int n, unsigned int p[], unsigned int s[], unsigned int l[], unsigned int b[])
{
	int Lmax = 256;
	int header = 11;
	s[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		b[i] = length(p[i]);
		int bmax = b[i];
		s[i] = s[i - 1] + bmax;
		l[i] = 1;
		for (int j = 2; j <= i&&j <= Lmax; j++)
		{
			if (bmax < b[i - j + 1])
				bmax = b[i - j + 1];
			if (s[i]>s[i - j] + j*bmax)
			{
				s[i] = s[i - j] + j*bmax;
				l[i] = j;
			}
		}
		s[i] += header;
	}
}
//求某一数据占几位
unsigned int BmpCompress::length(int i)
{
	unsigned int k = 1;
	i = i / 2;
	while (i>0)
	{
		k++;
		i = i / 2;
	}
	return k;
}
//压缩函数
void BmpCompress::CompressBitmap(istream& fin, ostream& fout)
{
	//读图像文件
	//读文件头
	fin.read((char*)&FileHeader, sizeof(BITMAPFILEHEADER));
	//读位图头
	fin.read((char*)&BitmapHeader, sizeof(BITMAPINFOHEADER));
	//读调色板
	for (int i = 0; i < 256; i++)
		fin.read((char*)&ipRGB[i], sizeof(RGBQUAD));
	//读数据，声明一个指针数组
	//矩阵的长和宽
	Height = BitmapHeader.biHeight;
	Width = BitmapHeader.biWidth;
	//存放点阵信息
	ImageData = new unsigned char*[Height];
	for (int i = 0; i<Height; i++)
		ImageData[i] = new unsigned char[Width];
	//读数据
	for (int i = 0; i<Height; i++)
		for (int j = 0; j <Width; j++)
			fin.read((char*)&ImageData[i][j], 1);
	//将数据以S型遍历
	//注意要+1
	dataPoint = new unsigned int[Height*Width + 1];
	unsigned int flag = 1;
	dataPoint[0] = 0;
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
		{
			//偶数
			if (i % 2 == 0)
				dataPoint[flag++] = (unsigned int)ImageData[i][j];
			else
				dataPoint[flag++] = (unsigned int)ImageData[i][Width - 1 - j];
		}
	//初始化压缩需要的辅助数组
	//分段
	int bmpSize = Height*Width;
	unsigned int* bmpSegment = new unsigned int[bmpSize + 1];
	unsigned int* bmpLength = new unsigned int[bmpSize + 1];
	unsigned int* bmpBits = new unsigned int[bmpSize + 1];
	Compress(bmpSize, dataPoint, bmpSegment, bmpLength, bmpBits);
	//写压缩文件
	//写文件
	//先写前面的
	fout.write((char*)&FileHeader, sizeof(BITMAPFILEHEADER));
	fout.write((char*)&BitmapHeader, sizeof(BITMAPINFOHEADER));
	for (int i = 0; i < 256; i++)
		fout.write((char*)&ipRGB[i], sizeof(RGBQUAD));
	//从分段信息中取数据
	stack<unsigned int> my;
	unsigned int flag1 = bmpSize;
	unsigned int flag2 = bmpSize;
	//共有多少数据
	unsigned int m = 0;
	while (flag1 != 0 && flag2 != 0)
	{
		m++;
		my.push(bmpBits[flag2]);
		my.push(bmpLength[flag1]);
		flag2 = flag2 - bmpLength[flag2];
		flag1 = flag1 - bmpLength[flag1];
	}
	//最终的组数信息保存在Res中
	Result* pResult = new Result[m];
	unsigned int i = 0;//用来下面计数
	while (!my.empty())
	{
		pResult[i].Len = my.top();
		my.pop();
		pResult[i].Bt = my.top();
		my.pop();
		i++;
	}

	int Rstore = 1;
	for (int i = 0; i < m; i++)
	{
		unsigned int max2 = 0;
		for (int j = Rstore; j < Rstore + pResult[i].Len; j++)
		{
			if (max2 < dataPoint[j])
				max2 = dataPoint[j];
		}
		pResult[i].Bt = length(max2);
		Rstore += pResult[i].Len;
	}
	//写文件前记录共有多少段数据
	fout.write((char*)&m, sizeof(unsigned int));
	//段长和位长都要-1
	int Flag = 1;
	unsigned int writeFile = 0;
	unsigned int mark = 32;
	for (int i = 0; i < m; i++)
	{
		//对段头进行处理，段头应有8位
		unsigned int Head = pResult[i].Len - 1;
		//直接移位
		if ((mark >= 8) && mark != 0)
		{
			writeFile = writeFile << 8;
			writeFile = writeFile | Head;
			mark -= 8;
		}
		//否则应分段
		else
		{
			unsigned int temp = Head;
			temp = temp >> (8 - mark);
			Head = (Head << (mark + 24)) >> (mark + 24);
			writeFile = writeFile << mark;
			writeFile = writeFile | temp;
			//够32位写一次文件
			fout.write((char*)&writeFile, sizeof(unsigned int));
			writeFile = 0;
			int t = 8 - mark;
			writeFile = writeFile << t;
			writeFile = writeFile | Head;
			mark = 32 - t;
		}
		if (mark == 0)
		{
			fout.write((char*)&writeFile, sizeof(unsigned int));
			writeFile = 0;
			mark = 32;
		}
		//对段内元素占的位进行处理，注意减一，且有3位
		unsigned int Degre = pResult[i].Bt - 1;
		if ((mark >= 3) && mark != 0)
		{
			writeFile = writeFile << 3;
			writeFile = writeFile | Degre;
			mark -= 3;
		}
		//同样的分段处理
		else
		{
			unsigned int temp = Degre;
			temp = temp >> (3 - mark);
			Degre = (Degre << (mark + 29)) >> (mark + 29);
			writeFile = writeFile << mark;
			writeFile = writeFile | temp;
			//够32位写一次文件
			fout.write((char*)&writeFile, sizeof(unsigned int));
			writeFile = 0;
			int t = 3 - mark;
			writeFile = writeFile << t;
			writeFile = writeFile | Degre;
			mark = 32 - t;
		}
		if (mark == 0)
		{
			fout.write((char*)&writeFile, sizeof(unsigned int));
			writeFile = 0;
			mark = 32;
		}
		//对像素点进行操作，每个像素点占的位数为pRes[i].Bt
		for (int j = Flag; j < Flag + pResult[i].Len; j++)
		{
			unsigned int data = dataPoint[j];
			unsigned int Dchild = pResult[i].Bt;
			if ((mark >= Dchild) && mark != 0)
			{
				writeFile = writeFile << Dchild;
				writeFile = writeFile | data;
				mark -= Dchild;
			}
			//同样的分段处理
			else
			{
				unsigned int temp = data;
				temp = temp >> (Dchild - mark);
				data = (data << (mark + 32 - Dchild)) >> (mark + 32 - Dchild);
				writeFile = writeFile << mark;
				writeFile = writeFile | temp;
				//够32位写一次文件
				fout.write((char*)&writeFile, sizeof(unsigned int));
				writeFile = 0;
				int t = Dchild - mark;
				writeFile = writeFile << t;
				writeFile = writeFile | data;
				mark = 32 - t;
			}
			if (mark == 0)
			{
				fout.write((char*)&writeFile, sizeof(unsigned int));
				writeFile = 0;
				mark = 32;
			}
		}
		//重要，每处理一段数据，更新下标（加段长），准备处理下一段数据
		Flag += pResult[i].Len;
	}
	//最后不足32，补0，补0
	for (int i = 0; i < mark; i++)
		writeFile <<= 1;
	fout.write((char*)&writeFile, sizeof(unsigned int));
	//临时申请的空间就在本函数内释放，其余的在析构函数中释放
	delete[] pResult;
	delete[] bmpLength;
	delete[] bmpSegment;
	delete[] bmpBits;
}
//解压函数
void BmpCompress::DeCompressBitmap(istream& fin, ostream& fout)
{
	//读文件头
	fin.read((char*)&FileHeader, sizeof(BITMAPFILEHEADER));
	//读位图头
	fin.read((char*)&BitmapHeader, sizeof(BITMAPINFOHEADER));
	//矩阵的长和宽
	Height = BitmapHeader.biHeight;
	Width = BitmapHeader.biWidth;
	//读调色板
	for (int i = 0; i < 256; i++)
		fin.read((char*)&ipRGB[i], sizeof(RGBQUAD));
	//还原S型数组
	dataPoint = new unsigned int[Height*Width];
	//标记作用
	unsigned int mark = 32;
	int Flag = 0;
	//读入共有多少段
	unsigned int FileLength = 0;
	fin.read((char*)&FileLength, sizeof(unsigned int));
	//存放读入的文件
	unsigned int ReadFile = 0;
	fin.read((char*)&ReadFile, sizeof(unsigned int));
	for (int i = 0; i < FileLength; i++)
	{
		//取段头元素，注意+1
		unsigned int head1;
		if (mark >= 8)
		{
			head1 = (ReadFile >> 24) + 1;
			ReadFile <<= 8;
			mark -= 8;
		}
		//段头存在跨位
		else
		{
			unsigned int temp = ReadFile >> (32 - mark);
			//读入新数据
			ReadFile = 0;
			fin.read((char*)&ReadFile, sizeof(unsigned int));
			int t = 8 - mark;
			unsigned int temp2 = ReadFile >> (32 - t);
			head1 = ((temp << t) | temp2) + 1;
			//顶掉t位数据
			ReadFile <<= t;
			mark = 32 - t;
		}
		if (mark == 0)
		{
			ReadFile = 0;
			fin.read((char*)&ReadFile, sizeof(unsigned int));
			mark = 32;
		}
		//取每一段有多少位
		unsigned int by1;
		if (mark >= 3)
		{
			by1 = (ReadFile >> 29) + 1;
			ReadFile <<= 3;
			mark -= 3;
		}
		else
		{
			unsigned int temp = ReadFile >> (32 - mark);
			//读入新数据
			ReadFile = 0;
			fin.read((char*)&ReadFile, sizeof(unsigned int));
			int t = 3 - mark;
			unsigned int temp2 = ReadFile >> (32 - t);
			by1 = ((temp << t) | temp2) + 1;
			//顶掉t位数据
			ReadFile <<= t;
			mark = 32 - t;
		}
		if (mark == 0)
		{
			ReadFile = 0;
			fin.read((char*)&ReadFile, sizeof(unsigned int));
			mark = 32;
		}
		//取数据点
		for (int j = 0; j < head1; j++)
		{
			//每个元素占Dchild位
			unsigned int Dchild = by1;
			if (mark >= Dchild)
			{
				//保存数据
				dataPoint[Flag++] = ReadFile >> (32 - Dchild);
				ReadFile = ReadFile << Dchild;
				mark -= Dchild;
			}
			//同样的分段处理
			else
			{
				unsigned int temp = ReadFile >> (32 - mark);
				//读入新数据
				ReadFile = 0;
				fin.read((char*)&ReadFile, sizeof(unsigned int));
				//还需要处理多少位
				int t = Dchild - mark;
				unsigned int temp2 = ReadFile >> (32 - t);
				dataPoint[Flag++] = (temp << t) | temp2;
				ReadFile <<= t;
				mark = 32 - t;
			}
			if (mark == 0)
			{
				ReadFile = 0;
				fin.read((char*)&ReadFile, sizeof(unsigned int));
				mark = 32;
			}
		}
	}
	//因为有补0的缘故，后面多余的数据不需要处理
	//还原S型点阵后，把S型点阵转化为矩阵
	ImageData = new unsigned char*[Height];
	for (int i = 0; i < Height; i++)
		ImageData[i] = new unsigned char[Width];
	//遍历数组
	int index = 0;
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (i % 2 == 0)
				ImageData[i][j] = (unsigned char)dataPoint[index++];
			else
				ImageData[i][Width - 1 - j] = (unsigned char)dataPoint[index++];
		}
	}
	//写图像数据
	//写文件头
	fout.write((char*)&FileHeader, sizeof(BITMAPFILEHEADER));
	//写位图头
	fout.write((char*)&BitmapHeader, sizeof(BITMAPINFOHEADER));
	//写调色板
	for (int i = 0; i < 256; i++)
		fout.write((char*)&ipRGB[i], sizeof(RGBQUAD));
	//写点阵数据
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
			fout.write((char*)&ImageData[i][j], 1);
}
//析构函数释放内存
BmpCompress::~BmpCompress()
{
	//释放点阵
	for (int i = 0; i < Height; i++)
		delete[] ImageData[i];
	delete[] ImageData;
	//释放S型数组
	delete[] dataPoint;
}
