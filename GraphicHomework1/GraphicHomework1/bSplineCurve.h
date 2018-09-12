#pragma once
#include "curve.h"
class BSplineCurve : public Curve
{
public:
	BSplineCurve();
	BSplineCurve(int number);
	~BSplineCurve();
	void set(int i, Vec3f v);
	void Paint(ArgParser *args);
	void OutputBezier(FILE *file);
	void OutputBSpline(FILE *file);
	void addControlPoint(int selectedPoint, float x, float y);
	void deleteControlPoint(int selectedPoint);
protected:
private:
};