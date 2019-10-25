#include "ExtendedController.h"
#include "Bench.h"
#include "Tree.h"
#include "Block.h"
#include "Bridge.h"

void createTreesForScene(ExtendedController& c, ShaderIF* sIF)
{
	// tree position along Y axis
	double treeTrunksPosAlongY[] = {0.01, 0.03, 0.26, 0.06, 0.20, 0.13};

	// tree position along Z axis
	double treeTrunksPosAlongZ[] = {1.56, 1.4, 1.34, 1.53, 1.32, 1.37};

	// tree colors
	double treeTrunkColor[] = {165, 100, 6};
	double rLeafColor[] = {77, 95, 51, 37, 129, 9};
	double gLeafColor[] = {168, 195, 151, 87, 202, 168};
	double bLeafColor[] = {59, 75, 31, 27, 147, 114};

	// add trees
	double leavesSize[] = {0.022, 0.022, 0.022};

	for (int i = 0; i < 6; i++)
	{
		double treeLeafColor[] = {rLeafColor[i], gLeafColor[i], bLeafColor[i]};
		double treeLeavesPosAlongY = treeTrunksPosAlongY[i] - 0.009;
		double treeLeavesPosAlongZ = treeTrunksPosAlongZ[i] - 0.01;

		double blockPos[] = {treeLeavesPosAlongY, treeLeavesPosAlongZ};

		c.addModel(new Tree(sIF, 0.2, 0.23,
		treeTrunksPosAlongY[i], treeTrunksPosAlongZ[i], // position of trunks
		0.05, 0.23,
		blockPos, // position of leaves
		leavesSize, // size of leaves
		treeLeafColor, treeTrunkColor)); // colors
	}
}

void createBenchesForScene(ExtendedController& c, ShaderIF* sIF)
{
	// bench
	double backRestSize[] = {0.009, 0.003, 0.021};

	// bench position along Y axis
	double seatPosAlongY[] = {0.025, 0.025};

	// bench position along Z axis
	double seatPosAlongZ[] = {1.45, 1.48};

	// bench color
	double benchColor[] = {0, 204, 204};

	// legs color
	double legsColor[] = {64, 64, 64};

	// add benches
	double seatSize[] = {0.003, 0.009, 0.021};
	for (int i = 0; i < 2; i++)
	{
		// bench seat position (Y and Z combined)
		double seatPos[i] = {seatPosAlongY[i], seatPosAlongZ[i]};

		double frontRightLegPos[] = {seatPosAlongY[i] + 0.002, seatPosAlongZ[i] + 0.002}; // yPos, zPos
		double frontLeftLegPos[] = {seatPosAlongY[i] + 0.002, seatPosAlongZ[i] + 0.019}; // yPos, zPos
		double backRightLegPos[] = {seatPosAlongY[i] + 0.007, seatPosAlongZ[i] + 0.002}; // yPos, zPos
		double backLeftLegPos[] = {seatPosAlongY[i] + 0.007, seatPosAlongZ[i] + 0.019}; // yPos, zPos

		c.addModel(new Bench(sIF, 0.2, 0.205,
		frontRightLegPos, frontLeftLegPos, backRightLegPos, backLeftLegPos,
		0.035, 0.205,
		seatPos, seatSize, backRestSize,
		benchColor, legsColor));
	}
}

void createBridgesForScene(ExtendedController& c, ShaderIF* sIF)
{
	double wallPieceSize[] = {0.009, 0.05, 0.005};
	double baseSize[] = {0.003, 0.05, 0.023};
	double cornerPostSize[] = {0.022, 0.022, 0.022};
	double bridgeBaseColor[] = {153, 0, 0};
	double cornerPostColor[] = {102, 0, 0};

	// base positions
	double basePosAlongY[] = {0.2, 0.13};
	double basePosAlongZ[] = {1.52, 1.4};

	for (int i = 0; i < 2; i++)
	{
		// bridge base position (Y and Z combined)
		double basePos[i] = {basePosAlongY[i], basePosAlongZ[i]};

		double frontRightPostPos[] = {basePosAlongY[i] + 0.002, basePosAlongZ[i] + 0.002}; // yPos, zPos
		double frontLeftPostPos[] = {basePosAlongY[i] + 0.002, basePosAlongZ[i] + 0.019}; // yPos, zPos
		double backRightPostPos[] = {basePosAlongY[i] + 0.05, basePosAlongZ[i] + 0.002}; // yPos, zPos
		double backLeftPostPos[] = {basePosAlongY[i] + 0.05, basePosAlongZ[i] + 0.019}; // yPos, zPos

		c.addModel(new Bridge(sIF, 0.2, 0.215,
		frontRightPostPos, frontLeftPostPos, backRightPostPos, backLeftPostPos,
		0.05, 0.2,
		basePos, baseSize, wallPieceSize,
		cornerPostColor, bridgeBaseColor));
	}
}

void createScene(ExtendedController& c, ShaderIF* sIF)
{	
	// grass
	double grassColor[] = {0, 92, 9};
	double grassSize[] = {0.001, 0.3, 0.3};
	double grassPos[] = {-0.009, 1.29};
	c.addModel(new Block(sIF, 0.2, grassPos, grassSize, grassColor));

	// dirt
	double dirtColor[] = {101, 67, 33};
	double dirtSize[] = {0.01, 0.3, 0.3};
	double dirtPos[] = {-0.009, 1.29};
	c.addModel(new Block(sIF, 0.19, dirtPos, dirtSize, dirtColor));

	// river
	double riverColor[] = {28,163,236};
	double riverSize[] = {0.007, 0.02, 0.12};
	double riverPos[] = {0.22, 1.469};
	c.addModel(new Block(sIF, 0.195, riverPos, riverSize, riverColor));

	double riverColor2[] = {28,163,236};
	double riverSize2[] = {0.007, 0.08, 0.02};
	double riverPos2[] = {0.15, 1.469};
	c.addModel(new Block(sIF, 0.195, riverPos2, riverSize2, riverColor2));

	double riverColor3[] = {28,163,236};
	double riverSize3[] = {0.007, 0.02, 0.199};
	double riverPos3[] = {0.148, 1.29};
	c.addModel(new Block(sIF, 0.195, riverPos3, riverSize3, riverColor3));

	// add benches, trees, and bridges
	createBenchesForScene(c, sIF);
	createTreesForScene(c, sIF);
	createBridgesForScene(c, sIF);
}

void set3DViewingInformation(double overallBB[])
{
	// be able to see entire screen initially (viewing strategy #1)
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

	// calculate radius for x, y, and z
	double xRadius = (maxX - minX) / 2;
	double yRadius = (maxY - minY) / 2;
	double zRadius = (maxZ - minZ) / 2;

	// set radius to be x or y or z (whichever value is greatest)
	double radius = xRadius;
	if (yRadius > radius)
	{
		radius = yRadius;
	}
	if (zRadius > radius)
	{
		radius = zRadius;
	}

	// compute/set eye, center, up
	double distance = 3.5 * radius;
	cryph::AffVector directionFromCenterToEye = cryph::AffVector(0, 0, 1);
	cryph::AffPoint center(midX, midY, midZ);
	cryph::AffPoint eye = center + (distance * directionFromCenterToEye);
	cryph::AffVector up = cryph::AffVector(1, 0, 0);
	ModelView::setEyeCenterUp(eye, center, up);

	// EC -> LDS:

	// specify the initial projection type desired
	ModelView::setProjection(PERSPECTIVE);

	// compute/set ecZmin, ecZmax (it is often useful to exaggerate
	// these limits somewhat to prevent unwanted depth clipping)
	double ecZmin = -distance - radius;
	double ecZmax = -distance + radius;
	ModelView::setECZminZmax(ecZmin, ecZmax);

	// compute/set ecZpp
	double ecZpp = ecZmax;
	ModelView::setProjectionPlaneZ(ecZpp);
}

int main(int argc, char* argv[])
{
	ExtendedController c("Feel the Snow Tribute", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);

	ShaderIF* sIF = new ShaderIF("shaders/basic.vsh", "shaders/phong.fsh");

	createScene(c, sIF);

	glClearColor(0.529, 0.808, 0.922, 1.0);

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
