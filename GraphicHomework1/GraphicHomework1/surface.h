#pragma once
#include "spline.h"

class Surface : public Spline
{
public:
	Surface();
	~Surface();
	void set(int i, Vec3f v);
	void Paint(ArgParser *args);
protected:
	vector<Vec3f> sur_point;
};