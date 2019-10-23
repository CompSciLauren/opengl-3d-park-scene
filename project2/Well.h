// Well.h

#ifndef Well_H
#define Well_H

#include "ModelView.h"
#include "ShaderIF.h"

class Well : public ModelView
{
public:
	// As before: you will likely want to add parameters to the constructor
	Well(ShaderIF* sIF);
	virtual ~Well();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
	void renderXxx();
private:
	ShaderIF* shaderIF;
	float ka[3], kd[3];
};

#endif
