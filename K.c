#include "udf.h"

DEFINE_PROPERTY(cell_thermal_conductivity, c, t)
{
	real k_base;
	real k_nano;
	real k_nanofluid;
	real phi = 0.01; // volume fraction of nanoparticle
	real temp = C_T(c, t); // temperature of the fluid zone
	real delta;

	// calculate the thermal conductivity of base fluid
	if (temp < 285.15)
		k_base = 0.136742342;
	else if (temp >= 285.15 && temp <= 698.15)
		k_base = 0.14644 + 2.0353e-5 * temp - 1.9367e-7 * temp * temp + 1.0614e-11 * temp * temp * temp;
	else if (temp > 698.15)
		k_base = 0.069864;

	// calculate the thermal conductivity of nano particle
	k_nano = 148.14 - 0.56883 * temp + 9.794e-4 * temp * temp - 8.0417e-7 * temp * temp * temp + 2.5595e-10 * temp * temp * temp * temp;

	// calculate the delta term
	delta = pow((3 * phi - 1) * k_nano + (2 - 3 * phi) * k_base, 2) + 8 * k_nano * k_base;

	// calculate the thermal conductivity of nanofluid
	k_nanofluid = 0.25 * ((3 * phi - 1) * k_nano + (2 - 3 * phi) * k_base + sqrt(delta));

	return k_nanofluid;
}