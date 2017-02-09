/*
 * Copyright (c) 2015 University of Colorado [http://www.ucdenver.edu]
 * Computer Graphics Laboratory [Min Choi, Shane Transue]
 *
 * min.choi@ucdenver.edu
 * shane.transue@ucdenver.edu
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef CAMERA_H
#define CAMERA_H

#include <Mathematics.h>
#include <Matrix4.h>

template <typename Real>
class Camera {
public:
    Camera(Real radius = Real(1));
    Camera(const Camera<Real>& camera);
    virtual ~Camera();

    void rotate(Real dTheta, Real dPhi);

    void setPerspective(Real fov, Real aspectRatio, Real znear, Real zfar);
    void setFrustum(Real left, Real right, Real top, Real bottom, Real znear, Real zfar);

    void setLookAt(const Vector3<Real>& lookAt);
    void setRotation(Real theta, Real phi);
    void setPosition(Real r, Real theta, Real phi);
    void setPosition(const Vector3<Real>& position);
    void setRadius(Real radius);
    void addRadius(Real dRadius);

    /*
     * Constructs a rotation matrix based on the three linearly indpendent
     * vectors that compose the cameras view direction, right vector, and
     * up direction. These three orthogonal vectors are composed into a 
     * single rotation matrix.
     */
    Matrix3<Real> getBasisMatrix(bool colMajor = true) const;
    Matrix4<Real> toViewMatrix() const;
    Matrix4<Real> toProjectionMatrix() const;
    Vector3<Real> toCartesianCoordinates() const;
    Vector3<Real> toSphericalCoordinates() const;

    Vector3<Real> getEyeDirection() const;
    Vector3<Real> getUpDirection() const;
    Vector3<Real> getRightDirection() const;

    Matrix4<Real>& getViewMatrix();
    Matrix4<Real>& getProjectionMatrix();
    Real& getRadius();
    Real& getFOV();
    Vector3<Real>& getEye();
    Vector3<Real>& getLookAt();
    Vector3<Real>& getUp();
    Vector3<Real>& getRight();

    const Matrix4<Real>& getViewMatrix() const;
    const Matrix4<Real>& getProjectionMatrix() const;

    const Real& getRadius() const;
    const Vector3<Real>& getEye() const;
    const Vector3<Real>& getLookAt() const;
    const Vector3<Real>& getUp() const;
    const Vector3<Real>& getRight() const;

protected:
    void compile();
	void inverse_compile();

protected:
    Matrix4<Real> view;
    Matrix4<Real> projection;

    Vector3<Real> eye;
    Vector3<Real> lookAt;

    Vector3<Real> up;
    Vector3<Real> right;
    Vector3<Real> dir;

    Real r, theta, phi;
    Real fov;
};

template <typename Real>
Camera<Real>::Camera(Real radius) {
    this->r = radius;
    this->theta = Real(0);
    this->phi = Real(HALF_PI);

    this->eye = Vector3<Real>::UnitZ();
    this->lookAt = Vector3<Real>::Zero();
    this->up = Vector3<Real>::UnitY();

    this->compile();
}

template <typename Real>
Camera<Real>::Camera(const Camera<Real>& camera) {
    this->view = camera.view;
    this->eye = camera.eye;
    this->lookAt = camera.lookAt;
    this->up = camera.up;
    this->r = camera.r;
    this->theta = camera.theta;
    this->phi = camera.phi;
}

template <typename Real>
Camera<Real>::~Camera() {}

template <typename Real>
void Camera<Real>::rotate(Real dTheta, Real dPhi) {
    this->theta += dTheta;
    this->phi += dPhi;
    this->compile();
}

template <typename Real>
void Camera<Real>::setPerspective(Real fov, Real aspectRatio, Real znear, Real zfar) {
    Real ymax = znear * std::tan(fov * Real(PI) / Real(360));
    Real xmax = ymax * aspectRatio;
    this->fov = fov;
    this->setFrustum(-xmax, xmax, ymax, -ymax, znear, zfar);
}

template <typename Real>
void Camera<Real>::setFrustum(Real left, Real right, Real top, Real bottom, Real znear, Real zfar) {
    this->projection.zero();

    Real temp, temp2, temp3, temp4;
    temp = Real(2) * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;

    this->projection.set(0, temp / temp2);
    this->projection.set(5, temp / temp3);
    this->projection.set(8, (right + left) / temp2);
    this->projection.set(9, (top + bottom) / temp3);
    this->projection.set(10, (-zfar - znear) / temp4);
    this->projection.set(11, Real(-1));
    this->projection.set(14, (-temp * zfar) / temp4);
}

template <typename Real>
void Camera<Real>::setLookAt(const Vector3<Real>& lookAt) {
    this->lookAt = lookAt;
    this->compile();
}

template <typename Real>
void Camera<Real>::setRotation(Real theta, Real phi) {
    this->theta = theta;
    this->phi = phi;
    this->compile();
}

template <typename Real>
void Camera<Real>::setPosition(Real r, Real theta, Real phi) {
    this->r = r;
    this->theta = theta;
    this->phi = phi;
    this->compile();
}

template <typename Real>
void Camera<Real>::setPosition(const Vector3<Real>& position) {
    this->r = position.x();
    this->theta = position.y();
    this->phi = position.z();
    this->compile();
}

template <typename Real>
void Camera<Real>::setRadius(Real radius) {
    this->r = radius;
    this->compile();
}

template <typename Real>
void Camera<Real>::addRadius(Real dRadius) {
    if ( r + dRadius < 1.0f || r + dRadius > 500.0f ) return;
    this->r += dRadius;
    this->compile();
}

template <typename Real>
Matrix3<Real> Camera<Real>::getBasisMatrix(bool colMajor) const {
    Matrix3<Real> matrix;

    if ( colMajor ) {
        matrix.setColumn(0, this->dir);
        matrix.setColumn(1, this->up);
        matrix.setColumn(2, this->right);
    }
    else {
        matrix.setRow(0, this->dir);
        matrix.setRow(1, this->up);
        matrix.setRow(2, this->right);
    }

    return matrix;
}

template <typename Real>
Matrix4<Real> Camera<Real>::toViewMatrix() const {
    this->compile();
    return this->view;
}

template <typename Real>
Matrix4<Real> Camera<Real>::toProjectionMatrix() const {
    return this->projection;
}

template <typename Real>
Vector3<Real> Camera<Real>::toCartesianCoordinates() const {
    return SphereicalToCartesian<Real>(this->r, this->theta, this->phi);
}

template <typename Real>
Vector3<Real> Camera<Real>::toSphericalCoordinates() const {
    return Vector3<Real>(this->r, this->theta, this->phi);
}

template <typename Real>
Vector3<Real> Camera<Real>::getEyeDirection() const {
    return Vector3<Real>(this->eye, this->lookAt);
}

template <typename Real>
Vector3<Real> Camera<Real>::getUpDirection() const {
    return this->up;
}

template <typename Real>
Vector3<Real> Camera<Real>::getRightDirection() const {
    return this->right;
}

template <typename Real>
Matrix4<Real>& Camera<Real>::getViewMatrix() {
    return this->view;
}

template <typename Real>
Matrix4<Real>& Camera<Real>::getProjectionMatrix() {
    return this->projection;
}

template <typename Real>
Real& Camera<Real>::getRadius() {
    return this->r;
}

template <typename Real>
Real& Camera<Real>::getFOV() {
    return this->fov;
}

template <typename Real>
Vector3<Real>& Camera<Real>::getEye() {
    return this->eye;
}

template <typename Real>
Vector3<Real>& Camera<Real>::getLookAt() {
    return this->lookAt;
}

template <typename Real>
Vector3<Real>& Camera<Real>::getUp() {
    return this->up;
}

template <typename Real>
Vector3<Real>& Camera<Real>::getRight() {
    return this->right;
}

template <typename Real>
const Matrix4<Real>& Camera<Real>::getViewMatrix() const {
    return this->view;
}

template <typename Real>
const Matrix4<Real>& Camera<Real>::getProjectionMatrix() const {
    return this->projection;
}

template <typename Real>
const Real& Camera<Real>::getRadius() const {
    return this->r;
}

template <typename Real>
const Vector3<Real>& Camera<Real>::getEye() const {
    this->compile();
    return this->eye;
}

template <typename Real>
const Vector3<Real>& Camera<Real>::getLookAt() const {
    this->compile();
    return this->lookAt;
}

template <typename Real>
const Vector3<Real>& Camera<Real>::getUp() const {
    this->compile();
    return this->up;
}


template <typename Real>
const Vector3<Real>& Camera<Real>::getRight() const {
    this->compile();
    return this->right;
}

template <typename Real>
void Camera<Real>::compile() {
    this->eye = SphereicalToCartesian<Real>(this->r, this->theta, this->phi);
    this->up = -SphereicalToCartesian_dPhi<Real>(this->r, this->theta, this->phi);
    this->right = SphereicalToCartesian_dTheta<Real>(this->r, this->theta, this->phi);
    this->dir = SphereicalToCartesian_dPhiCrossdTheta(this->r, this->theta, this->phi);

    //--------------------------------------------------------------------------
    // Sphereical coordinates use a z-up axis, therefore we have to swap
    // the y and z components of the position.
    //--------------------------------------------------------------------------
    this->eye.swapYZ();
    this->right.swapYZ();
    this->up.swapYZ();
    this->dir.swapYZ();

    //--------------------------------------------------------------------------
    // Normalize these vectors to form a basis.
    //--------------------------------------------------------------------------
    this->right.normalize();
    this->up.normalize();
    this->dir.normalize();

    this->view = Matrix4<Real>::LookAt(this->eye, this->lookAt, this->up);
}

template <typename Real>
void Camera<Real>::inverse_compile() {
	/* Calculating r, theta and phi by using eye vector. */
	this->eye.swapYZ();
	Vector3<Real> result = CartesianToSpherical(this->eye.x(), this->eye.y(), this->eye.z());
	this->r = result.getX();
	this->theta = result.getY();
	this->phi = result.getZ();

	this->up = -SphereicalToCartesian_dPhi<Real>(this->r, this->theta, this->phi);
	this->right = SphereicalToCartesian_dTheta<Real>(this->r, this->theta, this->phi);
	this->dir = SphereicalToCartesian_dPhiCrossdTheta(this->r, this->theta, this->phi);

	this->eye.swapYZ();
	this->right.swapYZ();
	this->up.swapYZ();
	this->dir.swapYZ();

	this->right.normalize();
	this->up.normalize();
	this->dir.normalize();

	this->view = Matrix4<Real>::LookAt(this->eye, this->lookAt, this->up);
}

typedef Camera<float> Cameraf;
typedef Camera<double> Camerad;

#endif
