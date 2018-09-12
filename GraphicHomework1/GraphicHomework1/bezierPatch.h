#pragma once
#include "surface.h"
class BezierPatch : public Surface
{
public:
	BezierPatch();
	~BezierPatch();
	void set(int i, Vec3f v);
protected:
private:
};