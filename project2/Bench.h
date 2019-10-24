#ifndef Bench_H
#define Bench_H

#include "ModelView.h"
#include "ShaderIF.h"
#include "Cylinder.h"
#include "Block.h"

class Bench : public ModelView
{
public:
	Bench(ShaderIF* sIF, double xMinPos, double xMaxPos,
	double frontRightLegPos[], double frontLeftLegPos[], double backRightLegPos[], double backLeftLegPos[],
	double radius, double blX, double seatPos[], double seatSize[], double backRestSize[],
	double blockColor[], double benchColor[]);
	virtual ~Bench();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
	void renderBench() const;
private:
	ShaderIF* shaderIF;
	GLuint vao[1];
	GLuint vbo[1]; // stores both cylinder and block points
	int numTrunkTriStripPoints;
	float ka[3], kd[3];
	double xb, yb, rBenchTop, rTrunk, height;
	int numBenchTopPoints, numTrunkPoints;
	double xmin, xmax, ymin, ymax, zmin, zmax;
	Cylinder* legs[4];
	Block* benchSeat;
	Block* backRest;
};

#endif
