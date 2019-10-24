#version 410 core

// Phong Lighting model

in PVA
{
	vec3 ecPosition;  // "Q" in our lighting model pictures
	vec3 ecUnitNormal;// "nHat" in our lighting model pictures
} pvaIn;

// for lighting model:
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
	vec3 vHat;
	if (ec_lds[3][3] == 0)
	{
		vHat = normalize(-ecPosition);
	}
	else
	{
		vHat = normalize(-ec_lds[0][2]/ec_lds[0][0], -ec_lds[1][2]/ec_lds[1][1], 1);
	}


	vec3 liHat = vec3(0.0, 0.0, 1.0); // directional light in EC at eye (a flashlight)

	float rKaLa = ka[0] * La[0];
	float gKaLa = ka[1] * La[1];
	float bKaLa = ka[2] * La[2];

	float iHat[] = {0, 0, 1};
	vec3 normal = vec3(1, 0, -1);

	if (dot(normal, vHat) < 0)
	{
		normal = -normal;
	}

	float rKdINorm = kd[0] * dot(iHat, normal);
	float gKdINorm = kd[1] * dot(iHat, normal);
	float bKdINorm = kd[2] * dot(iHat, normal);

	float r = rKaLa + rKdINorm;
	float g = gKaLa + gKdINorm;
	float b = bKaLa + bKdINorm;

	return vec4(r, g, b, 1.0);
}

void main ()
{
	fragmentColor = evaluateLightingModel();
}
