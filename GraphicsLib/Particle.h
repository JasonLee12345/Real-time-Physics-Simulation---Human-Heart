#pragma once

#include <Vector3.h>


template <class Real>
class Particle {
	static_assert(std::is_integral<Real>::value || std::is_floating_point<Real>::value,
		"[Class Particle:Type] Error: Data type must be an integral or floating point numerical representation.");

public:
	/*
	*	Variables
	*/
	Vector3<Real> position;
	Vector3<Real> force;
	Vector3<Real> velocity;


	/*
	*	Constants
	*/
	Real mass;
};