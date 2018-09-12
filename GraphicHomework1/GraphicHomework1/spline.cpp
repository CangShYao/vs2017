#include "spline.h"

Spline::Spline()
{
}

Spline::~Spline()
{
}

void Spline::Paint(ArgParser * args)
{
}

void Spline::OutputBezier(FILE * file)
{
}

void Spline::OutputBSpline(FILE * file)
{
}

int Spline::getNumVertices()
{
	return 0;
}

Vec3f Spline::getVertex(int i)
{
	return Vec3f();
}

void Spline::moveControlPoint(int selectedPoint, float x, float y)
{
}

void Spline::addControlPoint(int selectedPoint, float x, float y)
{
}

void Spline::deleteControlPoint(int selectedPoint)
{
}

TriangleMesh * Spline::OutputTriangles(ArgParser * args)
{
	TriangleMesh * answer;
	return answer;
}
