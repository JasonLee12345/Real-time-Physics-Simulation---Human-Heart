
#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

static const double PI = 3.14159265;
static const double HALF_PI = 1.57079633;

/* R(r, t, p) = rsin(phi)cos(theta)i + rsin(phi)sin(theta)j + rcos(phi)k */
template <typename Real>
inline Vector3<Real> SphereicalToCartesian(Real r, Real theta, Real phi) {
    Vector3<Real> result;
    result.x() = r * std::sin(phi) * std::cos(theta);
    result.y() = r * std::sin(phi) * std::sin(theta);
    result.z() = r * std::cos(phi);
    return result;
}

/* Rt(r, t, p) = -rsin(pphi)sin(theta)i + rsin(phi)cos(theta)j + 0k */
template <typename Real>
inline Vector3<Real> SphereicalToCartesian_dTheta(Real r, Real theta, Real phi) {
    Vector3<Real> result;
    result.x() = -r * std::sin(phi) * std::sin(theta);
    result.y() = r * std::sin(phi) * std::cos(theta);
    result.z() = Real(0);
    return result;
}

/* Rp(r, t, p) = rcos(phi)cos(theta)i + rcos(phi)sin(theta)j - rsin(phi)k */
template <typename Real>
inline Vector3<Real> SphereicalToCartesian_dPhi(Real r, Real theta, Real phi) {
    Vector3<Real> result;
    result.x() = r * std::cos(phi) * std::cos(theta);
    result.y() = r * std::cos(phi) * std::sin(theta);
    result.z() = -r * std::sin(phi);
    return result;
}

/* Rp X Rt = r^2 * sin^2(phi)cos(theta)i + r^2 * sin^2(phi)sin(theta)j + r^2 * sin(phi)cos(phi)k */
template <typename Real>
inline Vector3<Real> SphereicalToCartesian_dPhiCrossdTheta(Real r, Real theta, Real phi) {
    Vector3<Real> result;
    Real rs = (r*r);
    result.x() = rs * std::pow(std::sin(phi), Real(2)) * std::cos(theta);
    result.y() = rs * std::pow(std::sin(phi), Real(2)) * std::sin(theta);
    result.z() = rs * std::sin(phi) * std::cos(phi);
    return result;
}

template <typename Real>
inline Vector3<Real> CartesianToSpherical(Real x, Real y, Real z) {
	Vector3<Real> result;
	float r = static_cast<float>(sqrt(x * x + y * y + z * z));
	float theta = atanf(y / x);
	float phi = acosf(z / r);
	result.x() = r;
	result.y() = theta;
	result.z() = phi;
	return result;
}

#endif
