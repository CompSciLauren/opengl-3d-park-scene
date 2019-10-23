// Tree.c++

#include "Tree.h"

Tree::Tree(ShaderIF* sIF, double x, double y, double z,
double blX, double blY, double blZ, double blSize1, double blSize2, double blSize3,
double r, double g, double b) : shaderIF(sIF)
{
	double x1 = 0.2, x2 = 0.25;
	xmin = x1;
	xmax = x2;
	ymin = x - z;
	ymax = x + z;
	zmin = y - z;
	zmax = y + z;

	cylinder = new Cylinder(sIF, x, y, z);
	block = new Block(sIF, blX, blY, blZ, blSize1, blSize2, blSize3, r, g, b);
}

Tree::~Tree()
{
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Tree::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Tree::render()
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
	renderTree();

	// reestablish previous shader program
	glUseProgram(pgm);
}

void Tree::renderTree() const
{
	// set GLSL's "ka" and "kd" uniforms using this object's "ka" and "kd"
	//    instance variables
	// ...
	cylinder->render();
	block->render();
	// glBindVertexArray(vao[0]);
	// // draw trunk first because treetop overwrites it
	// glUniform4i(shaderIF->ppuLoc("treePart"), 0); // '0' means trunk
	// int numTrunkTriStripPoints = 2 * numTrunkPoints;
	// // draw tree top
	// glDrawArrays(GL_TRIANGLE_STRIP, 0, numTrunkTriStripPoints); // offset: 0
	// glDrawArrays(GL_TRIANGLE_FAN, numTrunkTriStripPoints, numTreeTopPoints);
}
