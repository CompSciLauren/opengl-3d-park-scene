// Cylinder.c++

#include <iostream>
#include <math.h>

#include "Cylinder.h"

// This simple Cylinder class creates a cylinder along the x-axis:
// (x1, yb, zb) to (x2, yb, zb) with radius = r
Cylinder::Cylinder(ShaderIF* sIF, double positionAlongY, double positionAlongZ, double radius,
double treeTrunkColor[]) : shaderIF(sIF) 
{
	double x1 = 0.2;
	double x2 = 0.25;
	xmin = x1;
	xmax = x2;
	ymin = positionAlongY - radius;
	ymax = positionAlongY + radius;
	zmin = positionAlongZ - radius;
	zmax = positionAlongZ + radius;

	kd[0] = treeTrunkColor[0]/255;
	kd[1] = treeTrunkColor[1]/255;
	kd[2] = treeTrunkColor[2]/255;
	defineCylinder(x1, x2, positionAlongY, positionAlongZ, radius);
}

Cylinder::~Cylinder()
{
	glDeleteBuffers(2, vbo);
	glDeleteVertexArrays(1, vao);
}

const int N_POINTS_AROUND_SLICE = 18; // number points around a cross-section

void Cylinder::defineCylinder(double x1, double x2, double positionAlongY, double positionAlongZ, double radius)
{
	typedef float vec3[3];
	int nPoints = 2 * (N_POINTS_AROUND_SLICE + 1); // "+1" because last point = first
	vec3* coords = new vec3[nPoints];
	vec3* normals = new vec3[nPoints];
	double theta = 0.0;
	double dTheta = 2.0*M_PI/N_POINTS_AROUND_SLICE;

	// define coords and normals for a GL_TRIANGLE_STRIP that approximates a cylinder
	for (int i=0 ; i<=N_POINTS_AROUND_SLICE ; i++)
	{
		// create two points and their corresponding (and common) normal vectors
		int j = 2 * i;
		double ny = radius * cos(theta);
		double nz = radius * sin(theta);
		coords[j][0] = x1;
		coords[j][1] = positionAlongY + radius * ny;
		coords[j][2] = positionAlongZ + radius * nz;

		normals[j][0] = 0;
		normals[j][1] = ny;
		normals[j][2] = nz;
		
		coords[j+1][0] = x2;
		coords[j+1][1] = positionAlongY + radius * ny;
		coords[j+1][2] = positionAlongZ + radius * nz;
		
		normals[j+1][0] = 0;
		normals[j+1][1] = ny;
		normals[j+1][2] = nz;
		theta += dTheta;
	}

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(2, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, nPoints * sizeof(vec3), coords, GL_STATIC_DRAW);

	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, nPoints * sizeof(vec3), normals, GL_STATIC_DRAW);

	glVertexAttribPointer(shaderIF->pvaLoc("mcNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

	delete [] coords;
	delete [] normals;
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Cylinder::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

bool Cylinder::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	// cylinder does not look for events. Just hand off back to inherited handleCommand
	return this->ModelView::handleCommand(anASCIIChar, ldsX, ldsY);
}

void Cylinder::renderCylinder()
{
	glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 2*(N_POINTS_AROUND_SLICE+1));
}

void Cylinder::render()
{
	typedef float vec3[3];
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);
	float mat[16];
	glUniformMatrix4fv(shaderIF->ppuLoc("mc_ec"), 1, false, mc_ec.extractColMajor(mat));
	glUniformMatrix4fv(shaderIF->ppuLoc("ec_lds"), 1, false, ec_lds.extractColMajor(mat));

	renderCylinder();

	glUseProgram(pgm);
}
