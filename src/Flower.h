#ifndef Flower_H
#define Flower_H

#include "ModelView.h"
#include "ShaderIF.h"
#include "Cylinder.h"
#include "Block.h"

class Flower : public ModelView
{
public:
	Flower(ShaderIF* sIF, double xMinPos, double xMaxPos, double positionAlongY, double positionAlongZ, double radius,
	double flowerX, double flowerPos[], double flowerSize[],
	double flowerColor[], double stemColor[]);
	virtual ~Flower();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
	void renderFlower() const;
private:
	ShaderIF* shaderIF;
	GLuint vao[1];
	GLuint vbo[1]; // stores both cylinder and block points
	float ka[3], kd[3];
	double xmin, xmax, ymin, ymax, zmin, zmax;
	Cylinder* cylinder;
	Block* block;
};

#endif
