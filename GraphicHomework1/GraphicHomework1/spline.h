#pragma once
#include <stdio.h>
#include <vector>
#include "matrix.h"
#include "triangle_mesh.h"
#include "arg_parser.h"
#include "glut.h"

static float arr_bizier[] = {
		-1.0,  3.0, -3.0, 1.0,
		 3.0, -6.0,  3.0, 0.0,
		-3.0,  3.0,  0.0, 0.0,
		 1.0,  0.0,  0.0, 0.0
};

static float arr_bspline[] = {
		-1 / 6.0,  3 / 6.0, -3 / 6.0, 1 / 6.0,
		 3 / 6.0, -6 / 6.0,  0 / 6.0, 4 / 6.0,
		-3 / 6.0,  3 / 6.0,  3 / 6.0, 1 / 6.0,
		 1 / 6.0,  0 / 6.0,  0 / 6.0, 0 / 6.0
};

class Spline
{
public:
	Spline();
	virtual ~Spline();
	// ���ڻ�ͼ��FOR VISUALIZATION
	virtual void Paint(ArgParser *args);

	// ����ʵ����������ת����FOR CONVERTING BETWEEN SPLINE TYPES
	virtual void OutputBezier(FILE *file);
	virtual void OutputBSpline(FILE *file);

	// ���ڵõ����Ƶ��FOR CONTROL POINT PICKING
	virtual int getNumVertices();
	virtual Vec3f getVertex(int i);

	// ���ڱ༭������FOR EDITING OPERATIONS
	virtual void moveControlPoint(int selectedPoint, float x, float y);
	virtual void addControlPoint(int selectedPoint, float x, float y);
	virtual void deleteControlPoint(int selectedPoint);

	// ���ڲ��������ε�FOR GENERATING TRIANGLES
	virtual TriangleMesh* OutputTriangles(ArgParser *args);

private:

};