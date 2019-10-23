// Bench.h

#ifndef Bench_H
#define Bench_H

#include "ModelView.h"
#include "ShaderIF.h"

class Bench : public ModelView
{
public:
	// As before: you will likely want to add parameters to the constructor
	Bench(ShaderIF* sIF);
	virtual ~Bench();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
	void renderXxx();
private:
	ShaderIF* shaderIF;
	float ka[3], kd[3];
};

#endif
