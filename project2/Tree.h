// Tree.h

#ifndef Tree_H
#define Tree_H

#include "ModelView.h"
#include "ShaderIF.h"

class Tree : public ModelView
{
public:
	// As before: you will likely want to add parameters to the constructor
	Tree(ShaderIF* sIF);
	virtual ~Tree();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
	void renderXxx();
private:
	ShaderIF* shaderIF;
	float ka[3], kd[3];
};

#endif
