#include "bezierCurve.h"

BezierCurve::BezierCurve() : Curve::Curve()
{
}

BezierCurve::BezierCurve(int number) : Curve::Curve(number)
{
}


BezierCurve::~BezierCurve()
{

}

void BezierCurve::set(int i, Vec3f v)
{
	Curve::set(i, v);
}

void BezierCurve::Paint(ArgParser * args)
{
	Curve::Paint(args);
	int Line_Count = args->curve_tessellation;
	// painting the Bezier line
	int number = cv_vertice.size();
	glLineWidth(2.0);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	
	int n = (number - 1) / 3;
	for (int i = 0; i < n; i++)
	{
		int j = 3 * i;
		float x0 = cv_vertice[j + 0].x(), x1 = cv_vertice[j + 1].x(),
			  x2 = cv_vertice[j + 2].x(), x3 = cv_vertice[j + 3].x();
		float y0 = cv_vertice[j + 0].y(), y1 = cv_vertice[j + 1].y(),
			  y2 = cv_vertice[j + 2].y(), y3 = cv_vertice[j + 3].y();
		float z0 = cv_vertice[j + 0].z(), z1 = cv_vertice[j + 1].z(),
			  z2 = cv_vertice[j + 2].z(), z3 = cv_vertice[j + 3].z();

		for (int i = 0; i <= Line_Count; i++)
		{
			float t = i / (Line_Count*1.0);
			float t_1 = 1 - t, tt = t * t, ttt = t * t * t;
			float x_t = t_1 * t_1 * t_1*x0 + 3 * t*t_1*t_1*x1 + 3 * tt*t_1*x2 + ttt*x3;
			float y_t = t_1 * t_1 * t_1*y0 + 3 * t*t_1*t_1*y1 + 3 * tt*t_1*y2 + ttt*y3;
			float z_t = t_1 * t_1 * t_1*z0 + 3 * t*t_1*t_1*z1 + 3 * tt*t_1*z2 + ttt*z3;
			glVertex3f(x_t, y_t, z_t);
		}
	}
	glEnd();

	glFlush();
}

void BezierCurve::OutputBSpline(FILE * file)
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
	matrix_spline.Inverse(temp);
	Matrix outBSpline(matrix_point*matrix_bizier*temp);
	fprintf(file, "\n");
	fprintf(file, "bspline\n");
	fprintf(file, "num_vertices 4\n");
	for (int i =0;i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			fprintf(file, "%f ", outBSpline.Get(i, j));
		}
		fprintf(file, "\n");
	}
}

void BezierCurve::OutputBezier(FILE * file)
{
	float arr_point[16] = {
		cv_vertice[0].x(), cv_vertice[1].x(), cv_vertice[2].x(), cv_vertice[3].x(),
		cv_vertice[0].y(), cv_vertice[1].y(), cv_vertice[2].y(), cv_vertice[3].y(),
		cv_vertice[0].z(), cv_vertice[1].z(), cv_vertice[2].z(), cv_vertice[3].z(),
		0, 0, 0, 0
	};

	Matrix matrix_point(arr_point);
	Matrix matrix_bizier(arr_bizier);
	Matrix temp;
	matrix_bizier.Inverse(temp);
	Matrix outBezier(matrix_point*matrix_bizier*temp);
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
