#pragma once

#include <Vector3.h>


template <class Real>
class Spring {
	static_assert(std::is_integral<Real>::value || std::is_floating_point<Real>::value,
		"[Class Spring:Type] Error: Data type must be an integral or floating point numerical representation.");

public:
	/*
	*	Variables
	*/
	//The position info of the two particles. They will be used only when it is necessary.
	Vector3<Real> p0_position;
	Vector3<Real> p1_position;


	/*
	*	Constants
	*/
	//The spring connects two particles.
	size_t p0;
	size_t p1;

	//The rest length of the spring.
	Real d_r;

	//The stiffness of the spring.
	float k;
};