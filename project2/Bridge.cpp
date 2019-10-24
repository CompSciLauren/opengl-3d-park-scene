#include "Bridge.h"

Bridge::Bridge(ShaderIF* sIF, double xMinPos, double xMaxPos,
double frontRightPostPos[], double frontLeftPostPos[], double backRightPostPos[], double backLeftPostPos[],
double radius,
double blX, double basePos[], double bridgeBaseSize[], double wallPieceSize[],
double cornerPostColor[], double bridgeBaseColor[]) : shaderIF(sIF)
{
	ymin = frontRightPostPos[0] - radius;
	ymax = frontRightPostPos[0] + radius;
	zmin = frontRightPostPos[1] - radius;
	zmax = frontRightPostPos[1] + radius;

	double secondWallPiecePos[] = {basePos[0], basePos[1] + 0.019};

	posts[0] = new Cylinder(sIF, xMinPos, xMaxPos, frontRightPostPos[0], frontRightPostPos[1], radius, cornerPostColor);
	posts[1] = new Cylinder(sIF, xMinPos, xMaxPos, frontLeftPostPos[0], frontLeftPostPos[1], radius, cornerPostColor);
	posts[2] = new Cylinder(sIF, xMinPos, xMaxPos, backRightPostPos[0], backRightPostPos[1], radius, cornerPostColor);
	posts[3] = new Cylinder(sIF, xMinPos, xMaxPos, backLeftPostPos[0], backLeftPostPos[1], radius, cornerPostColor);
	bridgeBase = new Block(sIF, blX, basePos, bridgeBaseSize, bridgeBaseColor);
	wallPieces[0] = new Block(sIF, blX, basePos, wallPieceSize, cornerPostColor);
	wallPieces[1] = new Block(sIF, blX, secondWallPiecePos, wallPieceSize, cornerPostColor);
}

Bridge::~Bridge()
{
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Bridge::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Bridge::render()
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
	renderBridge();

	// reestablish previous shader program
	glUseProgram(pgm);
}

void Bridge::renderBridge() const
{
	bridgeBase->render();
	posts[0]->render();
	posts[1]->render();
	posts[2]->render();
	posts[3]->render();
	wallPieces[0]->render();
	wallPieces[1]->render();
}
