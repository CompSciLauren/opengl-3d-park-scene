#version 410 core

// phong.fsh - a fragment shader that implements a Phong Lighting model.

in PVA
{
	vec3 ecPosition;  // "Q" in our lighting model pictures
	vec3 ecUnitNormal;// "nHat" in our lighting model pictures
} pvaIn;

// for lighing model:
uniform mat4 ec_lds; // so projection type and hence vHat can be determined

// phong material properties (RGB reflectances);
uniform vec3 ka = vec3(0.8, 0.0, 0.0); // default: darkish red
uniform vec3 kd = vec3(0.8, 0.0, 0.0); // default: darkish red
// lighting environment
// RGB strength of assumed ambient light:
uniform vec3 La = vec3(0.15, 0.15, 0.15);

// output color from the lighting model:
out vec4 fragmentColor;

// implements simple Lambert shading (NOTE: We assume a single directional light source defined in EC (liHat))
vec4 evaluateLightingModel()
{
	vec3 liHat = vec3(0.0, 0.0, 1.0); // directional light in EC at eye (a flashlight)

	float rKaLa = ka[0] * La[0];
	float gKaLa = ka[1] * La[1];
	float bKaLa = ka[2] * La[2];

	float r = rKaLa + kd[0];
	float g = gKaLa + kd[1];
	float b = bKaLa + kd[2];

	return vec4(r, g, b, 1.0);
}

void main ()
{
	fragmentColor = evaluateLightingModel();
}
