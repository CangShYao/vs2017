#pragma once
#include "surface.h"
#include "bezierCurve.h"
class SurfaceOfRevolution : public Surface
{
public:
	SurfaceOfRevolution();
	SurfaceOfRevolution(Curve * cv);
	~SurfaceOfRevolution();
	void Paint(ArgParser *args);
protected:
private:
	Curve * curve;
};