// Ball.h

#ifndef Ball_H
#define Ball_H

#include "ModelView.h"
#include "ShaderIF.h"

class Ball : public ModelView
{
public:
	// As before: you will likely want to add parameters to the constructor
	Ball(ShaderIF* sIF);
	virtual ~Ball();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
	void renderXxx();
private:
	ShaderIF* shaderIF;
	float ka[3], kd[3];
};

#endif
