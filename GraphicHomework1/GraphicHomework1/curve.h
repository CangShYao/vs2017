#pragma once
#include "spline.h"
class Curve : public Spline
{
public:
	Curve();
	Curve(int number);
	~Curve();

	void set(int i, Vec3f v);
	void Paint(ArgParser *args);
	int getNumVertices();
	Vec3f getVertex(int i);
	void moveControlPoint(int selectedPoint, float x, float y);
	void addControlPoint(int selectedPoint, float x, float y);
	void deleteControlPoint(int selectedPoint);
protected:
	vector<Vec3f> cv_vertice;
private:
	
};
