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

	void draw();  // 绘制到屏幕
	string str(); // 将向量坐标转为字符串，格式为“(x=, y=)”

	bool setX(double dX);
	double getX() const;
	bool setY(double dY);
	double getY() const;

	void setVecPosition(double dX = 0, double dY = 0);
	double getDistanceTo(const VecPosition p); //获得两点间的距离
	VecPosition setMagnitude(double d);		   //设置向量长度为d
	double getMagnitude() const;			   //获取向量长度
	double getDirection() const;			   //获取向量方向（与X轴夹角）

											   // 判断坐标是否在给定两点的X，Y之间
	bool isBetweenX(const VecPosition &p1, const VecPosition &p2);
	bool isBetweenX(const double &d1, const double &d2);
	bool isBetweenY(const VecPosition &p1, const VecPosition &p2);
	bool isBetweenY(const double &d1, const double &d2);

	// 正规化坐标
	VecPosition normalize();
	// 向量旋转
	VecPosition rotate(double angle);

	// 根据极坐标获取笛卡尔坐标
	static VecPosition getVecPositionFromPolar(double dMag, double ang);
	// 将任意角度转为（－180，180]范围
	static double normalizeAngle(double angle);

private:
	double m_x;
	double m_y;
};
