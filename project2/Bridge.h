#ifndef Bridge_H
#define Bridge_H

#include "ModelView.h"
#include "ShaderIF.h"
#include "Cylinder.h"
#include "Block.h"

class Bridge : public ModelView
{
public:
	Bridge(ShaderIF* sIF, double xMinPos, double xMaxPos,
	double frontRightPostPos[], double frontLeftPostPos[], double backRightPostPos[], double backLeftPostPos[],
	double radius,
	double blX, double basePos1[], double basePos2[], double basePos3[], double bridgeBaseSize[], double wallPieceSize[],
	double cornerPostColor[], double bridgeBaseColor[]);
	virtual ~Bridge();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
	void renderBridge() const;
private:
	ShaderIF* shaderIF;
	GLuint vao[1];
	GLuint vbo[1]; // stores both cylinder and block points
	float ka[3], kd[3];
	double xmin, xmax, ymin, ymax, zmin, zmax;
	Block* bridgeBase[3];
	Block* wallPieces[2];
	Cylinder* posts[4];
};

#endif
