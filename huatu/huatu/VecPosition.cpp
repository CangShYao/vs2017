#include "stdafx.h"
#include <sstream>
#include <cmath>
#include "VecPosition.h"

VecPosition::VecPosition(double vx, double vy)
{
	m_x = vx;
	m_y = vy;
}

VecPosition VecPosition::operator-()
{
	m_x = m_x - 2 * m_x;
	m_y = m_y - 2 * m_y;
	return *this;
}

VecPosition VecPosition::operator+(const double & d)
{
	return VecPosition();
}

VecPosition VecPosition::operator+(const VecPosition & p)
{
	m_x += p.m_x;
	m_y += p.m_y;
	return *this;
}

VecPosition VecPosition::operator-(const double & d)
{
	return VecPosition();
}

VecPosition VecPosition::operator-(const VecPosition & p)
{
	m_x -= p.m_x;
	m_y -= p.m_y;
	return *this;
}

VecPosition VecPosition::operator*(const double & d)
{
	return VecPosition();
}

VecPosition VecPosition::operator*(const VecPosition & p)
{
	m_x *= p.m_x;
	m_y *= p.m_y;
	return *this;
}

VecPosition VecPosition::operator/(const double & d)
{
	return VecPosition();
}

VecPosition VecPosition::operator/(const VecPosition & p)
{
	m_x /= p.m_x;
	m_y /= p.m_y;
	return *this;
}

void VecPosition::operator=(const double & d)
{
}

void VecPosition::operator+=(const VecPosition & p)
{
	m_x += p.m_x;
	m_y += p.m_y;
}

void VecPosition::operator+=(const double & d)
{
}

void VecPosition::operator-=(const VecPosition & p)
{
}

void VecPosition::operator-=(const double & d)
{
}

void VecPosition::operator*=(const VecPosition & p)
{
}

void VecPosition::operator*=(const double & d)
{
}

void VecPosition::operator/=(const VecPosition & p)
{
}

void VecPosition::operator/=(const double & d)
{
}

bool VecPosition::operator!=(const VecPosition & p)
{
	if (m_x == p.m_x || m_y == p.m_y)
	{
		return false;
	}
	return true;
}

bool VecPosition::operator!=(const double & d)
{
	return false;
}

bool VecPosition::operator==(const VecPosition & p)
{
	if (m_x == p.m_x && m_y == p.m_y)
	{
		return true;
	}
	return false;
}

bool VecPosition::operator==(const double & d)
{
	return false;
}

void VecPosition::draw()
{
}

// 将向量坐标转为字符串，格式为“(x=, y=)”
string VecPosition::str()
{	
	stringstream oss1;
	oss1 << m_x;
	stringstream oss2;
	oss2 << m_y;
	string ans = "(" + oss1.str() + ", " + oss2.str() + ")";
	return ans;
}

bool VecPosition::setX(double dX)
{
	m_x = dX;
	return true;
}

double VecPosition::getX() const
{
	return m_x;
}

bool VecPosition::setY(double dY)
{
	m_y = dY;
	return true;
}

double VecPosition::getY() const
{
	return m_y;
}

void VecPosition::setVecPosition(double dX, double dY)
{
	m_x = dX;
	m_y = dY;
}

//获得两点间的距离
double VecPosition::getDistanceTo(const VecPosition p)
{
	double dis_x = m_x - p.m_x;
	double dis_y = m_y - p.m_y;
	return sqrt(dis_x * dis_x + dis_y * dis_y);
}

//设置向量长度为d
VecPosition VecPosition::setMagnitude(double d)
{
	return VecPosition();
}
