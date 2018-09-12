#include "curve.h"

Curve::Curve()
{
}

Curve::Curve(int num)
{
}

Curve::~Curve()
{
}

void Curve::set(int i, Vec3f v)
{
	cv_vertice.push_back(v);
}

void Curve::Paint(ArgParser * args)
{
	// painting points
	glPointSize(5.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	int number = cv_vertice.size();
	for (int i = 0; i < number; i++)
	{
		glVertex3f(cv_vertice[i].x(), cv_vertice[i].y(), cv_vertice[i].z());
	}
	glEnd();

	// painting the line between points
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < number; i++)
	{
		glVertex3f(cv_vertice[i].x(), cv_vertice[i].y(), cv_vertice[i].z());
	}
	glEnd();
}

int Curve::getNumVertices()
{
	return cv_vertice.size();
}

Vec3f Curve::getVertex(int i)
{
	return cv_vertice[i];
}

void Curve::moveControlPoint(int selectedPoint, float x, float y)
{
	cv_vertice[selectedPoint].Set(x, y, cv_vertice[selectedPoint].z());
}

void Curve::addControlPoint(int selectedPoint, float x, float y)
{
}

void Curve::deleteControlPoint(int selectedPoint)
{
}
