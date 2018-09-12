#include "surfaceOfRevolution.h"

SurfaceOfRevolution::SurfaceOfRevolution()
{
}

SurfaceOfRevolution::SurfaceOfRevolution(Curve * cv)
{
	curve = cv;
}

SurfaceOfRevolution::~SurfaceOfRevolution()
{
}

void SurfaceOfRevolution::Paint(ArgParser * args)
{
	curve->Paint(args);
}
