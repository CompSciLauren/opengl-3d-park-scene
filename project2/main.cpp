// main.c++: Starter for EECS 672 Projects 2-4

#include "ExtendedController.h"
#include "Cylinder.h"
#include "TEMPLATE_Subclass.h"

void createScene(ExtendedController& c, ShaderIF* sIF)
{
	// TODO: Implement this function
}

void set3DViewingInformation(double overallBB[])
{
	// Be able to see entire screen initially (viewing strategy #1)
	ModelView::setMCRegionOfInterest(overallBB);

	// MC -> EC:
	double minX = overallBB[0];
	double maxX = overallBB[1];
	double minY = overallBB[2];
	double maxY = overallBB[3];
	double minZ = overallBB[4];
	double maxZ = overallBB[5];

	double midX = (maxX + minX) / 2;
	double midY = (maxY + minY) / 2;
	double midZ = (maxZ + minZ) / 2;

	// Calculate radius for x, y, and z
	double xRadius = (maxX - minX) / 2;
	double yRadius = (maxY - minY) / 2;
	double zRadius = (maxZ - minZ) / 2;

	// Set radius to be x or y or z (whichever value is greatest)
	double radius = xRadius;
	if (yRadius > radius)
	{
		radius = yRadius;
	}
	if (zRadius > radius)
	{
		radius = zRadius;
	}

	// TODO: Compute/set eye, center, up
	cryph::AffPoint eye;
	cryph::AffPoint center(midX, midY, midZ);
	cryph::AffVector up;
	ModelView::setEyeCenterUp(eye, center, up);

	// EC -> LDS:

	// Specify the initial projection type desired
	ModelView::setProjection(PERSPECTIVE);

	// TODO: Compute/set ecZmin, ecZmax (It is often useful to exaggerate
	//       these limits somewhat to prevent unwanted depth clipping.)
	double ecZmin, ecZmax;
	ModelView::setECZminZmax(ecZmin, ecZmax);

	// TODO: Compute/set ecZpp
	double ecZpp;
	ModelView::setProjectionPlaneZ(ecZpp);
}

int main(int argc, char* argv[])
{
	ExtendedController c("Feel the Snow Tribute", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);

	ShaderIF* sIF = new ShaderIF("shaders/basic.vsh", "shaders/phong.fsh");

	createScene(c, sIF);

	glClearColor(1.0, 1.0, 1.0, 1.0);

	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	std::cout << "Bounding box: " << xyz[0] << " <= x <= " << xyz[1] << '\n';
	std::cout << "              " << xyz[2] << " <= y <= " << xyz[3] << '\n';
	std::cout << "              " << xyz[4] << " <= z <= " << xyz[5] << "\n\n";
	set3DViewingInformation(xyz);

	c.run();

	delete sIF;

	return 0;
}
