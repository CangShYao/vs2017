#include "bSplineCurve.h"

BSplineCurve::BSplineCurve() : Curve::Curve()
{
}

BSplineCurve::BSplineCurve(int number) : Curve::Curve(number)
{
}


BSplineCurve::~BSplineCurve()
{
}

void BSplineCurve::set(int i, Vec3f v)
{
	Curve::set(i, v);
}

void BSplineCurve::Paint(ArgParser * args)
{
	Curve::Paint(args);
	int Line_Count = args->curve_tessellation;
	// painting the Bsp line
	int number = cv_vertice.size();
	glLineWidth(2.0);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < number - 3; i++)
	{
		float x0 = cv_vertice[i + 0].x(), x1 = cv_vertice[i + 1].x(),
			  x2 = cv_vertice[i + 2].x(), x3 = cv_vertice[i + 3].x();
		float y0 = cv_vertice[i + 0].y(), y1 = cv_vertice[i + 1].y(),
			  y2 = cv_vertice[i + 2].y(), y3 = cv_vertice[i + 3].y();
		float z0 = cv_vertice[i + 0].z(), z1 = cv_vertice[i + 1].z(),
			  z2 = cv_vertice[i + 2].z(), z3 = cv_vertice[i + 3].z();

		for (int i = 0; i <= Line_Count; i++)
		{
			float t = i / (Line_Count*1.0);
			float tt = t * t, ttt = t * t * t;
			float x_t = ((1 - t)*(1 - t)*(1 - t)*x0 + (3 * ttt - 6 * tt + 4)*x1 + (-3 * ttt + 3 * tt + 3 * t + 1)*x2 + ttt * x3) / 6;
			float y_t = ((1 - t)*(1 - t)*(1 - t)*y0 + (3 * ttt - 6 * tt + 4)*y1 + (-3 * ttt + 3 * tt + 3 * t + 1)*y2 + ttt * y3) / 6;
			float z_t = ((1 - t)*(1 - t)*(1 - t)*z0 + (3 * ttt - 6 * tt + 4)*z1 + (-3 * ttt + 3 * tt + 3 * t + 1)*z2 + ttt * z3) / 6;
			glVertex3f(x_t, y_t, z_t);
		}
	}
	glEnd();

	glFlush();
}

void BSplineCurve::OutputBezier(FILE * file)
{
	float arr_point[16] = {
		cv_vertice[0].x(), cv_vertice[1].x(), cv_vertice[2].x(), cv_vertice[3].x(),
		cv_vertice[0].y(), cv_vertice[1].y(), cv_vertice[2].y(), cv_vertice[3].y(),
		cv_vertice[0].z(), cv_vertice[1].z(), cv_vertice[2].z(), cv_vertice[3].z(),
		0, 0, 0, 0
	};

	Matrix matrix_point(arr_point);
	Matrix matrix_bizier(arr_bizier);
	Matrix matrix_spline(arr_bspline);
	Matrix temp;
	matrix_bizier.Inverse(temp);
	Matrix outBezier(matrix_point*matrix_spline*temp);
	fprintf(file, "\n");
	fprintf(file, "bezier\n");
	fprintf(file, "num_vertices 4\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			fprintf(file, "%f ", outBezier.Get(i, j));
		}
		fprintf(file, "\n");
	}
}

void BSplineCurve::OutputBSpline(FILE * file)
{
	float arr_point[16] = {
		cv_vertice[0].x(), cv_vertice[1].x(), cv_vertice[2].x(), cv_vertice[3].x(),
		cv_vertice[0].y(), cv_vertice[1].y(), cv_vertice[2].y(), cv_vertice[3].y(),
		cv_vertice[0].z(), cv_vertice[1].z(), cv_vertice[2].z(), cv_vertice[3].z(),
		0, 0, 0, 0
	};

	Matrix matrix_point(arr_point);
	Matrix matrix_spline(arr_bspline);
	Matrix temp;
	matrix_spline.Inverse(temp);
	Matrix outBezier(matrix_point*matrix_spline*temp);
	fprintf(file, "\n");
	fprintf(file, "bspline\n");
	fprintf(file, "num_vertices 4\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			fprintf(file, "%f ", outBezier.Get(i, j));
		}
		fprintf(file, "\n");
	}
}

void BSplineCurve::addControlPoint(int selectedPoint, float x, float y)
{
	Vec3f v(x, y, 0);
	cv_vertice.insert(cv_vertice.begin()+selectedPoint, v);
}

void BSplineCurve::deleteControlPoint(int selectedPoint)
{
	cv_vertice.erase(cv_vertice.begin() + selectedPoint);
}
