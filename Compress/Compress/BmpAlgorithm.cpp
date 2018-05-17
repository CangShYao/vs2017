#include "BmpAlgorithm.h"

//ѹ���ֶκ���
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
//��ĳһ����ռ��λ
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
//ѹ������
void BmpCompress::CompressBitmap(istream& fin, ostream& fout)
{
	//��ͼ���ļ�
	//���ļ�ͷ
	fin.read((char*)&FileHeader, sizeof(BITMAPFILEHEADER));
	//��λͼͷ
	fin.read((char*)&BitmapHeader, sizeof(BITMAPINFOHEADER));
	//����ɫ��
	for (int i = 0; i < 256; i++)
		fin.read((char*)&ipRGB[i], sizeof(RGBQUAD));
	//�����ݣ�����һ��ָ������
	//����ĳ��Ϳ�
	Height = BitmapHeader.biHeight;
	Width = BitmapHeader.biWidth;
	//��ŵ�����Ϣ
	ImageData = new unsigned char*[Height];
	for (int i = 0; i<Height; i++)
		ImageData[i] = new unsigned char[Width];
	//������
	for (int i = 0; i<Height; i++)
		for (int j = 0; j <Width; j++)
			fin.read((char*)&ImageData[i][j], 1);
	//��������S�ͱ���
	//ע��Ҫ+1
	dataPoint = new unsigned int[Height*Width + 1];
	unsigned int flag = 1;
	dataPoint[0] = 0;
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
		{
			//ż��
			if (i % 2 == 0)
				dataPoint[flag++] = (unsigned int)ImageData[i][j];
			else
				dataPoint[flag++] = (unsigned int)ImageData[i][Width - 1 - j];
		}
	//��ʼ��ѹ����Ҫ�ĸ�������
	//�ֶ�
	int bmpSize = Height*Width;
	unsigned int* bmpSegment = new unsigned int[bmpSize + 1];
	unsigned int* bmpLength = new unsigned int[bmpSize + 1];
	unsigned int* bmpBits = new unsigned int[bmpSize + 1];
	Compress(bmpSize, dataPoint, bmpSegment, bmpLength, bmpBits);
	//дѹ���ļ�
	//д�ļ�
	//��дǰ���
	fout.write((char*)&FileHeader, sizeof(BITMAPFILEHEADER));
	fout.write((char*)&BitmapHeader, sizeof(BITMAPINFOHEADER));
	for (int i = 0; i < 256; i++)
		fout.write((char*)&ipRGB[i], sizeof(RGBQUAD));
	//�ӷֶ���Ϣ��ȡ����
	stack<unsigned int> my;
	unsigned int flag1 = bmpSize;
	unsigned int flag2 = bmpSize;
	//���ж�������
	unsigned int m = 0;
	while (flag1 != 0 && flag2 != 0)
	{
		m++;
		my.push(bmpBits[flag2]);
		my.push(bmpLength[flag1]);
		flag2 = flag2 - bmpLength[flag2];
		flag1 = flag1 - bmpLength[flag1];
	}
	//���յ�������Ϣ������Res��
	Result* pResult = new Result[m];
	unsigned int i = 0;//�����������
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
	//д�ļ�ǰ��¼���ж��ٶ�����
	fout.write((char*)&m, sizeof(unsigned int));
	//�γ���λ����Ҫ-1
	int Flag = 1;
	unsigned int writeFile = 0;
	unsigned int mark = 32;
	for (int i = 0; i < m; i++)
	{
		//�Զ�ͷ���д�����ͷӦ��8λ
		unsigned int Head = pResult[i].Len - 1;
		//ֱ����λ
		if ((mark >= 8) && mark != 0)
		{
			writeFile = writeFile << 8;
			writeFile = writeFile | Head;
			mark -= 8;
		}
		//����Ӧ�ֶ�
		else
		{
			unsigned int temp = Head;
			temp = temp >> (8 - mark);
			Head = (Head << (mark + 24)) >> (mark + 24);
			writeFile = writeFile << mark;
			writeFile = writeFile | temp;
			//��32λдһ���ļ�
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
		//�Զ���Ԫ��ռ��λ���д���ע���һ������3λ
		unsigned int Degre = pResult[i].Bt - 1;
		if ((mark >= 3) && mark != 0)
		{
			writeFile = writeFile << 3;
			writeFile = writeFile | Degre;
			mark -= 3;
		}
		//ͬ���ķֶδ���
		else
		{
			unsigned int temp = Degre;
			temp = temp >> (3 - mark);
			Degre = (Degre << (mark + 29)) >> (mark + 29);
			writeFile = writeFile << mark;
			writeFile = writeFile | temp;
			//��32λдһ���ļ�
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
		//�����ص���в�����ÿ�����ص�ռ��λ��ΪpRes[i].Bt
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
			//ͬ���ķֶδ���
			else
			{
				unsigned int temp = data;
				temp = temp >> (Dchild - mark);
				data = (data << (mark + 32 - Dchild)) >> (mark + 32 - Dchild);
				writeFile = writeFile << mark;
				writeFile = writeFile | temp;
				//��32λдһ���ļ�
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
		//��Ҫ��ÿ����һ�����ݣ������±꣨�Ӷγ�����׼��������һ������
		Flag += pResult[i].Len;
	}
	//�����32����0����0
	for (int i = 0; i < mark; i++)
		writeFile <<= 1;
	fout.write((char*)&writeFile, sizeof(unsigned int));
	//��ʱ����Ŀռ���ڱ��������ͷţ�������������������ͷ�
	delete[] pResult;
	delete[] bmpLength;
	delete[] bmpSegment;
	delete[] bmpBits;
}
//��ѹ����
void BmpCompress::DeCompressBitmap(istream& fin, ostream& fout)
{
	//���ļ�ͷ
	fin.read((char*)&FileHeader, sizeof(BITMAPFILEHEADER));
	//��λͼͷ
	fin.read((char*)&BitmapHeader, sizeof(BITMAPINFOHEADER));
	//����ĳ��Ϳ�
	Height = BitmapHeader.biHeight;
	Width = BitmapHeader.biWidth;
	//����ɫ��
	for (int i = 0; i < 256; i++)
		fin.read((char*)&ipRGB[i], sizeof(RGBQUAD));
	//��ԭS������
	dataPoint = new unsigned int[Height*Width];
	//�������
	unsigned int mark = 32;
	int Flag = 0;
	//���빲�ж��ٶ�
	unsigned int FileLength = 0;
	fin.read((char*)&FileLength, sizeof(unsigned int));
	//��Ŷ�����ļ�
	unsigned int ReadFile = 0;
	fin.read((char*)&ReadFile, sizeof(unsigned int));
	for (int i = 0; i < FileLength; i++)
	{
		//ȡ��ͷԪ�أ�ע��+1
		unsigned int head1;
		if (mark >= 8)
		{
			head1 = (ReadFile >> 24) + 1;
			ReadFile <<= 8;
			mark -= 8;
		}
		//��ͷ���ڿ�λ
		else
		{
			unsigned int temp = ReadFile >> (32 - mark);
			//����������
			ReadFile = 0;
			fin.read((char*)&ReadFile, sizeof(unsigned int));
			int t = 8 - mark;
			unsigned int temp2 = ReadFile >> (32 - t);
			head1 = ((temp << t) | temp2) + 1;
			//����tλ����
			ReadFile <<= t;
			mark = 32 - t;
		}
		if (mark == 0)
		{
			ReadFile = 0;
			fin.read((char*)&ReadFile, sizeof(unsigned int));
			mark = 32;
		}
		//ȡÿһ���ж���λ
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
			//����������
			ReadFile = 0;
			fin.read((char*)&ReadFile, sizeof(unsigned int));
			int t = 3 - mark;
			unsigned int temp2 = ReadFile >> (32 - t);
			by1 = ((temp << t) | temp2) + 1;
			//����tλ����
			ReadFile <<= t;
			mark = 32 - t;
		}
		if (mark == 0)
		{
			ReadFile = 0;
			fin.read((char*)&ReadFile, sizeof(unsigned int));
			mark = 32;
		}
		//ȡ���ݵ�
		for (int j = 0; j < head1; j++)
		{
			//ÿ��Ԫ��ռDchildλ
			unsigned int Dchild = by1;
			if (mark >= Dchild)
			{
				//��������
				dataPoint[Flag++] = ReadFile >> (32 - Dchild);
				ReadFile = ReadFile << Dchild;
				mark -= Dchild;
			}
			//ͬ���ķֶδ���
			else
			{
				unsigned int temp = ReadFile >> (32 - mark);
				//����������
				ReadFile = 0;
				fin.read((char*)&ReadFile, sizeof(unsigned int));
				//����Ҫ�������λ
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
	//��Ϊ�в�0��Ե�ʣ������������ݲ���Ҫ����
	//��ԭS�͵���󣬰�S�͵���ת��Ϊ����
	ImageData = new unsigned char*[Height];
	for (int i = 0; i < Height; i++)
		ImageData[i] = new unsigned char[Width];
	//��������
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
	//дͼ������
	//д�ļ�ͷ
	fout.write((char*)&FileHeader, sizeof(BITMAPFILEHEADER));
	//дλͼͷ
	fout.write((char*)&BitmapHeader, sizeof(BITMAPINFOHEADER));
	//д��ɫ��
	for (int i = 0; i < 256; i++)
		fout.write((char*)&ipRGB[i], sizeof(RGBQUAD));
	//д��������
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
			fout.write((char*)&ImageData[i][j], 1);
}
//���������ͷ��ڴ�
BmpCompress::~BmpCompress()
{
	//�ͷŵ���
	for (int i = 0; i < Height; i++)
		delete[] ImageData[i];
	delete[] ImageData;
	//�ͷ�S������
	delete[] dataPoint;
}
