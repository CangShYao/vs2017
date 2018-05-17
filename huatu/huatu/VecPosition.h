#pragma once
#include <string>
using namespace std;
class VecPosition
{
public:
	VecPosition(double vx = 0,double vy = 0);

	VecPosition operator-();
	VecPosition operator+(const double &d);
	VecPosition operator+(const VecPosition &p);
	VecPosition operator-(const double &d);
	VecPosition operator-(const VecPosition &p);
	VecPosition operator*(const double &d);
	VecPosition operator*(const VecPosition &p);
	VecPosition operator/(const double &d);
	VecPosition operator/(const VecPosition &p);
	void operator=(const double &d);
	void operator+=(const VecPosition &p);
	void operator+=(const double &d);
	void operator-=(const VecPosition &p);
	void operator-=(const double &d);
	void operator*=(const VecPosition &p);
	void operator*=(const double &d);
	void operator/=(const VecPosition &p);
	void operator/=(const double &d);
	bool operator!=(const VecPosition &p);
	bool operator!=(const double &d);
	bool operator==(const VecPosition &p);
	bool operator==(const double &d);

	void draw();  // ���Ƶ���Ļ
	string str(); // ����������תΪ�ַ�������ʽΪ��(x=, y=)��

	bool setX(double dX);
	double getX() const;
	bool setY(double dY);
	double getY() const;

	void setVecPosition(double dX = 0, double dY = 0);
	double getDistanceTo(const VecPosition p); //��������ľ���
	VecPosition setMagnitude(double d);		   //������������Ϊd
	double getMagnitude() const;			   //��ȡ��������
	double getDirection() const;			   //��ȡ����������X��нǣ�

											   // �ж������Ƿ��ڸ��������X��Y֮��
	bool isBetweenX(const VecPosition &p1, const VecPosition &p2);
	bool isBetweenX(const double &d1, const double &d2);
	bool isBetweenY(const VecPosition &p1, const VecPosition &p2);
	bool isBetweenY(const double &d1, const double &d2);

	// ���滯����
	VecPosition normalize();
	// ������ת
	VecPosition rotate(double angle);

	// ���ݼ������ȡ�ѿ�������
	static VecPosition getVecPositionFromPolar(double dMag, double ang);
	// ������Ƕ�תΪ����180��180]��Χ
	static double normalizeAngle(double angle);

private:
	double m_x;
	double m_y;
};
