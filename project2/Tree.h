#ifndef Tree_H
#define Tree_H

#include "ModelView.h"
#include "ShaderIF.h"
#include "Cylinder.h"
#include "Block.h"

class Tree : public ModelView
{
public:
	Tree(ShaderIF* sIF, double xMinPos, double xMaxPos, double positionAlongY, double positionAlongZ, double radius,
	double blX, double blockPos[], double leavesSize[],
	double blockColor[], double treeTrunkColor[]);
	virtual ~Tree();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
	void renderTree() const;
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
