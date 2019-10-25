#include "Flower.h"

Flower::Flower(ShaderIF* sIF, double xMinPos, double xMaxPos, double positionAlongY, double positionAlongZ, double radius,
double blX, double blockPos[], double leavesSize[], double blockColor[], double stemColor[]) : shaderIF(sIF)
{
	ymin = positionAlongY - radius;
	ymax = positionAlongY + radius;
	zmin = positionAlongZ - radius;
	zmax = positionAlongZ + radius;

	cylinder = new Cylinder(sIF, xMinPos, xMaxPos, positionAlongY, positionAlongZ, radius, stemColor);
	block = new Block(sIF, blX, blockPos, leavesSize, blockColor);
}

Flower::~Flower()
{
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Flower::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Flower::render()
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
	renderFlower();

	// reestablish previous shader program
	glUseProgram(pgm);
}

void Flower::renderFlower() const
{
	cylinder->render();
	block->render();
}
