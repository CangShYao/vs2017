#pragma once
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<stack>
using namespace std;

//�˽ṹ��������ŷֶκ������
struct Result
{
	unsigned int Len;//ÿ����Len��Ԫ��
	unsigned int Bt;//ÿ��Ԫ��ռBtλ
};

class BmpCompress
{
protected:
	//�ļ�ͷ��λͼͷ����ɫ�壬λͼ����
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER BitmapHeader;
	RGBQUAD ipRGB[256];
	//���λͼ����
	unsigned char * * ImageData;
	//����߿�û�����޷��ͷž����ڴ�
	int Height;
	int Width;
	//���S�͵���
	unsigned int* dataPoint;
public:
	//ѹ���ֶκ���
	void Compress(unsigned int n, unsigned int p[], unsigned int s[], unsigned int l[], unsigned int b[]);
	//ѹ������
	void CompressBitmap(istream& fin, ostream& fout);
	//��ĳһ����ռ����λ
	unsigned int length(int i);
	//��ѹ����
	void DeCompressBitmap(istream& fin, ostream& fout);
	//���������������ͷ��ڴ�
	~BmpCompress();
};