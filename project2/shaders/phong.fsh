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
		vHat = normalize(-pvaIn.ecPosition);
	}
	else
	{
		vHat = normalize(vec3(-ec_lds[0][2]/ec_lds[0][0], -ec_lds[1][2]/ec_lds[1][1], 1));
	}

	vec3 liHat = vec3(0.0, 0.0, 1.0); // directional light in EC at eye (a flashlight)
	vec3 nHat = pvaIn.ecUnitNormal;

	if (dot(nHat, vHat) < 0)
	{
		nHat = -nHat;
	}

	vec3 rgb = (ka * La) + kd * dot(liHat, nHat);

	return vec4(rgb, 1.0);
}

void main ()
{
	fragmentColor = evaluateLightingModel();
}
