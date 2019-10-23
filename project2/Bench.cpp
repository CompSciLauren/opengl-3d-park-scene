// Bench.c++

#include "Bench.h"

Bench::Bench(ShaderIF* sIF, double xMinPos, double xMaxPos,
double frontRightLegPos[], double frontLeftLegPos[], double backRightLegPos[], double backLeftLegPos[],
double radius, double blX, double blockPosAlongY, double blZ, double benchSize[],
double blockColor[], double legsColor[]) : shaderIF(sIF)
{
	double x1 = 0.2;
	double x2 = 0.25;
	xmin = x1;
	xmax = x2;
	ymin = frontRightLegPos[0] - radius;
	ymax = frontRightLegPos[0] + radius;
	zmin = frontRightLegPos[1] - radius;
	zmax = frontRightLegPos[1] + radius;

	legs[0] = new Cylinder(sIF, xMinPos, xMaxPos, frontRightLegPos[0], frontRightLegPos[1], radius, legsColor);
	legs[1] = new Cylinder(sIF, xMinPos, xMaxPos, frontLeftLegPos[0], frontLeftLegPos[1], radius, legsColor);
	legs[2] = new Cylinder(sIF, xMinPos, xMaxPos, backRightLegPos[0], backRightLegPos[1], radius, legsColor);
	legs[3] = new Cylinder(sIF, xMinPos, xMaxPos, backLeftLegPos[0], backLeftLegPos[1], radius, legsColor);
	block = new Block(sIF, blX, blockPosAlongY, blZ, benchSize, blockColor);
}

Bench::~Bench()
{
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Bench::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Bench::render()
{
	// save current and establish new current shader program
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	// draw the triangles using our vertex and fragment shaders
	glUseProgram(shaderIF->getShaderPgmID());

	// establish "mc_ec" and "ec_lds" matrices
	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);
	float m[16];
	glUniformMatrix4fv(shaderIF->ppuLoc("mc_ec"), 1, false, mc_ec.extractColMajor(m));
	glUniformMatrix4fv(shaderIF->ppuLoc("ec_lds"), 1, false, mc_ec.extractColMajor(m));
	renderBench();

	// reestablish previous shader program
	glUseProgram(pgm);
}

void Bench::renderBench() const
{
	legs[0]->render();
	legs[1]->render();
	legs[2]->render();
	legs[3]->render();
	block->render();
}
