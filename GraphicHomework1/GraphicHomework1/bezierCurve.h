#pragma once
#include "curve.h"
class BezierCurve : public Curve
{
public:
	BezierCurve();
	BezierCurve(int number);
	~BezierCurve();

	void set(int i, Vec3f v);
	void Paint(ArgParser *args);
	void OutputBSpline(FILE *file);
	void OutputBezier(FILE *file);

private:
};
