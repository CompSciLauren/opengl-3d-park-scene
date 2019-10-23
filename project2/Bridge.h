// Bridge.h

#ifndef Bridge_H
#define Bridge_H

#include "ModelView.h"
#include "ShaderIF.h"
#include "Cylinder.h"
#include "Block.h"

class Bridge : public ModelView
{
public:
	Bridge(ShaderIF* sIF, double xMinPos, double xMaxPos, double positionAlongY, double positionAlongZ, double radius,
	double blX, double blockPosAlongY, double blZ, double bridgeBaseSize[],
	double cornerPostColor[], double bridgeBaseColor[]);
	virtual ~Bridge();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
	void renderBridge() const;
private:
	ShaderIF* shaderIF;
	GLuint vao[1];
	GLuint vbo[1]; // stores both trunk and treetop points
	int numTrunkTriStripPoints;
	float ka[3], kd[3];
	double xb, yb, rBridgeTop, rTrunk, height;
	double xmin, xmax, ymin, ymax, zmin, zmax;
	Cylinder* cylinder;
	Block* bridgeBase;
};

#endif
