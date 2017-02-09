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
#ifndef VECTOR_4_H
#define VECTOR_4_H

#include <iostream>
#include <cmath>
#include <type_traits>
#include <iomanip>
#include "Vector3.h"

/* Forward Declaration for Templated Friends */
template <typename Real>
class Vector4;

/*
 * Templated Friends
 * See: http://www.parashift.com/c++-faq-lite/template-friends.html
 */
template <typename Real>
Vector4<Real> operator + (const Vector4<Real>& u, const Vector4<Real>& v);

template <typename Real>
Vector4<Real> operator - (const Vector4<Real>& u, const Vector4<Real>& v);

template <typename Real>
Vector4<Real> operator - (const Vector4<Real>& v);

template <typename Real>
Vector4<Real> operator * (const Vector4<Real>& v, Real scalar);

template <typename Real>
Vector4<Real> operator * (Real scalar, const Vector4<Real>& v);

template <typename Real>
Vector4<Real> operator / (const Vector4<Real>& v, Real scalar);

template <typename Real>
std::ostream& operator << (std::ostream& out, const Vector4<Real>& vector);

template <typename Real>
std::istream& operator >> (std::istream& in, Vector4<Real>& vector);

/* 
 * Vector4: Representation of any numerical vector in four dimensions.
 *
 * (w, x, y, z)
 * 
 * Implements the mathematical defintion of a Vector4. Do not perform long 
 * "temp-chains" using overloaded operators. This implementaton does not utilize 
 * template meta programming.
 * See: http://www.flipcode.com/archives/Faster_Vector_Math_Using_Templates.shtml
 *
 * This implementation also foregoes vectorization (SSE).
 * This implementation is aimed at a flexibility while preserving 
 * understandability and complete modularity.
 */
template <typename Real>
class Vector4 {
    static_assert(std::is_integral<Real>::value || std::is_floating_point<Real>::value, 
    "[Vector4:Type] Error: Vector4 Real type must be an integral or floating point numerical representation.");

    enum Axis { X, Y, Z, W, COMPONENT_COUNT };

public:
    Vector4(Real w = Real(0), Real x = Real(0), Real y = Real(0), Real z = Real(0));
    Vector4(const Vector4<Real>& v);
    Vector4(const Vector3<Real>& v, Real w = Real(1));
    Vector4(Real v[4]);
    ~Vector4();

    void add(const Vector4<Real>& v);
    void subtract(const Vector4<Real>& v);
    void multiply(Real scalar);
    void normalize();
    void inverse();

    void zero();
    bool isZero(Real epsilon);
    bool isEqual(const Vector4<Real>& v);
    bool isEquivalent(const Vector4<Real>& v, Real epsilon) const;

    template <typename RealCastType>
    Vector4<RealCastType> cast();

    Vector4<Real> normalized() const;
    double dot(const Vector4<Real>& v) const;
    
    double magnitude() const;
    double length() const;
    double lengthSquared() const;
    double norm() const;
    double normSquared() const;
    double distance(const Vector4<Real>& v) const;
    double distanceSquared(const Vector4<Real>& v) const;

    void set(Real w, Real x, Real y, Real z);
    void set(const Vector4<Real>& v);
    void setW(Real w);
    void setX(Real x);
    void setY(Real y);
    void setZ(Real z);

    const Real& getW() const;
    const Real& getX() const;
    const Real& getY() const;
    const Real& getZ() const;
    const Real& w() const;
    const Real& x() const;
	const Real& y() const;
	const Real& z() const;
	
    Real& getW();
    Real& getX();
    Real& getY();
    Real& getZ();
    Real& w();
	Real& x();
	Real& y();
	Real& z();

    const Real* const constData() const;
    operator const Real* const () const;
    Real operator () (const Vector4<Real>& v) const;
    bool operator () (const Vector4<Real>& u, const Vector4<Real>& v) const;

    Real& operator [] (std::size_t index);

    friend Vector4<Real> operator + <> (const Vector4<Real>& u, const Vector4<Real>& v);
    friend Vector4<Real> operator - <> (const Vector4<Real>& u, const Vector4<Real>& v);
    friend Vector4<Real> operator - <> (const Vector4<Real>& v);
    friend Vector4<Real> operator * <> (const Vector4<Real>& v, Real scalar);
    friend Vector4<Real> operator * <> (Real scalar, const Vector4<Real>& v);
    friend Vector4<Real> operator / <> (const Vector4<Real>& v, Real scalar);

    friend std::ostream& operator << <> (std::ostream& out, const Vector4<Real>& v);
    friend std::istream& operator >> <> (std::istream& in, Vector4<Real>& v);

    Vector4<Real> operator - (const Vector4<Real>& v) const;
	Vector4<Real> operator + (const Vector4<Real>& v) const;
	Vector4<Real> operator * (const Real& scalar) const;
	Vector4<Real> operator * (const Vector4<Real>& v) const;

    Vector4<Real>& operator = (const Vector4<Real>& v);

    Vector4<Real>& operator += (const Vector4<Real>& v);
    Vector4<Real>& operator -= (const Vector4<Real>& v);
    Vector4<Real>& operator *= (const Vector4<Real>& v);
    Vector4<Real>& operator *= (Real scalar);

    bool operator == (const Vector4<Real>& v) const;
	bool operator != (const Vector4<Real>& v) const;

    bool operator < (const Vector4<Real>& v);
    bool operator <= (const Vector4<Real>& v);
    bool operator > (const Vector4<Real>& v);
    bool operator >= (const Vector4<Real>& v);

    static Vector4<Real> Add(const Vector4<Real>& u, const Vector4<Real>& v);
    static Vector4<Real> Subtract(const Vector4<Real>& u, const Vector4<Real>& v);
    static Vector4<Real> Multiply(Real scalar, const Vector4<Real>& v);
    static Vector4<Real> Normalize(const Vector4<Real>& v);
    static Vector4<Real> LinearInterpolation(const Vector4<Real>& u, const Vector4<Real>& v, Real t);
    static Vector4<Real> Project(const Vector4<Real>& u, const Vector4<Real>& v);

    static double Dot(const Vector4<Real>& u, const Vector4<Real>& v);
    static double Magnitude(const Vector4<Real>& v);
    static double Norm(const Vector4<Real>& v);
    static double NormSquared(const Vector4<Real>& v);
    static double Length(const Vector4<Real>& v);
    static double LengthSquared(const Vector4<Real>& v);
    static double Distance(const Vector4<Real>& u, const Vector4<Real>& v);
    static double DistanceSquared(const Vector4<Real>& u, const Vector4<Real>& v);

    static Vector4<Real> Zero();
    static Vector4<Real> UnitW();
	static Vector4<Real> UnitX();
	static Vector4<Real> UnitY();
	static Vector4<Real> UnitZ();
    static Vector4<Real> UnitNW();
    static Vector4<Real> UnitNX();
    static Vector4<Real> UnitNY();
    static Vector4<Real> UnitNZ();

protected:
    Real data[COMPONENT_COUNT];
};

template <typename Real>
Vector4<Real>::Vector4(Real w, Real x, Real y, Real z) {
    this->data[W] = w;
    this->data[X] = x;
    this->data[Y] = y;
    this->data[Z] = z;
}

template <typename Real>
Vector4<Real>::Vector4(const Vector4<Real>& v) {
    this->data[W] = v.data[W];
    this->data[X] = v.data[X];
    this->data[Y] = v.data[Y];
    this->data[Z] = v.data[Z];
}

template <typename Real>
Vector4<Real>::Vector4(const Vector3<Real>& v, Real w) {
    this->data[W] = w;
    this->data[X] = v.x();
    this->data[Y] = v.y();
    this->data[Z] = v.z();
}

template <typename Real>
Vector4<Real>::Vector4(Real v[4]) {
    this->data[W] = v[0];
    this->data[X] = v[1];
    this->data[Y] = v[2];
    this->data[Z] = v[3];
}

template <typename Real>
Vector4<Real>::~Vector4() {}

template <typename Real>
void Vector4<Real>::add(const Vector4<Real>& v) {
    this->data[W] += v.data[W];
    this->data[X] += v.data[X];
    this->data[Y] += v.data[Y];
    this->data[Z] += v.data[Z];
}

template <typename Real>
void Vector4<Real>::subtract(const Vector4<Real>& v) {
    this->data[W] -= v.data[W];
    this->data[X] -= v.data[X];
    this->data[Y] -= v.data[Y];
    this->data[Z] -= v.data[Z];
}

template <typename Real>
void Vector4<Real>::multiply(Real scalar) {
    this->data[W] *= scalar;
    this->data[X] *= scalar;
    this->data[y] *= scalar;
    this->data[Z] *= scalar;
}

template <typename Real>
void Vector4<Real>::normalize() {
    double invLen = 1.0 / static_cast<double>(this->length());
    this->data[W] *= Real(invLen);
    this->data[X] *= Real(invLen);
    this->data[Y] *= Real(invLen);
    this->data[Z] *= Real(invLen);
}

template <typename Real>
void Vector4<Real>::inverse() {
    this->data[W] = -this->data[W];
    this->data[X] = -this->data[X];
    this->data[Y] = -this->data[Y];
    this->data[Z] = -this->data[Z];
}

template <typename Real>
void Vector4<Real>::zero() {
    this->data[W] = Real(0);
    this->data[X] = Real(0);
    this->data[Y] = Real(0);
    this->data[Z] = Real(0);
}

template <typename Real>
bool Vector4<Real>::isZero(Real epsilon) {
    if ( (this->data[W] > -epsilon) && 
         (this->data[W] < epsilon ) &&
         (this->data[X] > -epsilon) && 
         (this->data[X] < epsilon ) &&
         (this->data[Y] > -epsilon) &&
         (this->data[Y] < epsilon ) &&
         (this->data[Z] > -epsilon) &&
         (this->data[Z] < epsilon ) )
    return true;
    else return false;
}

template <typename Real>
bool Vector4<Real>::isEqual(const Vector4<Real>& v) {
    if ( *this == vector ) return true;
    return false;
}

template <typename Real>
bool Vector4<Real>::isEquivalent(const Vector4<Real>& v, Real epsilon) const {
    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ )
        if ( this->data[i] < (v.data[i] - epsilon) || this->data[i] > (v.data[i] + epsilon) ) return false;
    return true;
}

template <typename Real>
template <typename RealCastType>
Vector4<RealCastType> Vector4<Real>::cast() {
    return Vector4<RealCastType>(static_cast<RealCastType>(this->data[W]), static_cast<RealCastType>(this->data[X]), static_cast<RealCastType>(this->data[Y]), static_cast<RealCastType>(this->data[Z]));
}

template <typename Real>
Vector4<Real> Vector4<Real>::normalized() const {
    return Vector4<Real>::Normalize(*this);
}

template <typename Real>
double Vector4<Real>::dot(const Vector4<Real>& v) const {
    return Vector4<Real>::Dot(*this, v);
}

template <typename Real>
double Vector4<Real>::magnitude() const {
    return Vector4<Real>::Magnitude(*this);
}

template <typename Real>
double Vector4<Real>::length() const {
    return Vector4<Real>::Length(*this);
}

template <typename Real>
double Vector4<Real>::lengthSquared() const {
    return Vector4<Real>::LengthSquared(*this);
}

template <typename Real>
double Vector4<Real>::norm() const {
    return Vector4<Real>::Norm(*this);
}

template <typename Real>
double Vector4<Real>::normSquared() const {
    return Vector4<Real>::NormSquared(*this);
}

template <typename Real>
double Vector4<Real>::distance(const Vector4<Real>& v) const {
    return Vector4<Real>::Distance(*this, v);
}

template <typename Real>
double Vector4<Real>::distanceSquared(const Vector4<Real>& v) const {
    return Vector4<Real>::DistanceSquared(*this, v);
}

template <typename Real>
void Vector4<Real>::set(Real w, Real x, Real y, Real z) {
    this->data[W] = w;
    this->data[X] = x;
    this->data[Y] = y;
    this->data[Z] = z;
}

template <typename Real>
void Vector4<Real>::set(const Vector4<Real>& v) {
    this->data[W] = v.data[W];
    this->data[X] = v.data[X];
    this->data[Y] = v.data[Y];
    this->data[Z] = v.data[Z];
}

template <typename Real>
void Vector4<Real>::setW(Real w) {
    this->data[W] = w;
}

template <typename Real>
void Vector4<Real>::setX(Real x) {
    this->data[X] = x;
}

template <typename Real>
void Vector4<Real>::setY(Real y) {
    this->data[Y] = y;
}

template <typename Real>
void Vector4<Real>::setZ(Real z) {
    this->data[Z] = z;
}

template <typename Real>
const Real& Vector4<Real>::getW() const {
    return this->data[W];
}

template <typename Real>
const Real& Vector4<Real>::getX() const {
    return this->data[X];
}

template <typename Real>
const Real& Vector4<Real>::getY() const {
    return this->data[Y];
}

template <typename Real>
const Real& Vector4<Real>::getZ() const {
    return this->data[Z];
}

template <typename Real>
const Real& Vector4<Real>::w() const {
    return this->data[W];
}

template <typename Real>
const Real& Vector4<Real>::x() const {
    return this->data[X];
}

template <typename Real>
const Real& Vector4<Real>::y() const {
    return this->data[Y];
}

template <typename Real>
const Real& Vector4<Real>::z() const {
    return this->data[Z];
}
	
template <typename Real>
Real& Vector4<Real>::getW() {
    return this->data[W];
}

template <typename Real>
Real& Vector4<Real>::getX() {
    return this->data[X];
}

template <typename Real>
Real& Vector4<Real>::getY() {
    return this->data[y];
}

template <typename Real>
Real& Vector4<Real>::getZ() {
    return this->data[Z];
}

template <typename Real>
Real& Vector4<Real>::w() {
    return this->data[W];
}

template <typename Real>
Real& Vector4<Real>::x() {
    return this->data[X];
}

template <typename Real>
Real& Vector4<Real>::y() {
    return this->data[Y];
}

template <typename Real>
Real& Vector4<Real>::z() {
    return this->data[Z];
}

template <typename Real>
const Real* const Vector4<Real>::constData() const {
    return this->data;
}

template <typename Real>
Vector4<Real>::operator const Real* const () const {
    return this->data;
}

template <typename Real>
Real Vector4<Real>::operator () (const Vector4<Real>& v) const {
    return this->data[W] + this->data[X] + this->data[Y] + this->data[Z];
}

template <typename Real>
bool Vector4<Real>::operator () (const Vector4<Real>& u, const Vector4<Real>& v) const {
    if ( u.data[W] == v.data[W] && u.data[X] == v.data[X] && u.data[Y] == v.data[Y] && u.data[Z] == v.data[Z] ) return true;
    return false;
}

template <typename Real>
Real& Vector4<Real>::operator [] (std::size_t index) {
    if ( index >= COMPONENT_COUNT ) throw std::exception("[Vector4:[]] Error: Index out of bounds.");
    return this->data[index];
}

template <typename Real>
Vector4<Real> operator + (const Vector4<Real>& u, const Vector4<Real>& v) {
    Vector4<Real> result;
    result.data[Vector4<Real>::W] = u.data[Vector4<Real>::W] + v.data[Vector4<Real>::W];
    result.data[Vector4<Real>::X] = u.data[Vector4<Real>::X] + v.data[Vector4<Real>::X];
    result.data[Vector4<Real>::Y] = u.data[Vector4<Real>::Y] + v.data[Vector4<Real>::Y];
    result.data[Vector4<Real>::Z] = u.data[Vector4<Real>::Z] + v.data[Vector4<Real>::Z];
    return result;
}

template <typename Real>
Vector4<Real> operator - (const Vector4<Real>& u, const Vector4<Real>& v) {
    Vector4<Real> result;
    result.data[Vector4<Real>::W] = u.data[Vector4<Real>::W] - v.data[Vector4<Real>::W];
    result.data[Vector4<Real>::X] = u.data[Vector4<Real>::X] - v.data[Vector4<Real>::X];
    result.data[Vector4<Real>::Y] = u.data[Vector4<Real>::Y] - v.data[Vector4<Real>::Y];
    result.data[Vector4<Real>::Z] = u.data[Vector4<Real>::Z] - v.data[Vector4<Real>::Z];
    return result;
}

template <typename Real>
Vector4<Real> operator - (const Vector4<Real>& v) {
    return Vector4<Real>(-v.data[Vector4<Real>::W], -v.data[Vector4<Real>::X] -v.data[Vector4<Real>::Y], -v.data[Vector4<Real>::Z]);
}

template <typename Real>
Vector4<Real> operator * (const Vector4<Real>& v, Real scalar) {
    Vector4<Real> result;
    result.data[Vector4<Real>::W] = v.data[Vector4<Real>::W] * scalar;
    result.data[Vector4<Real>::X] = v.data[Vector4<Real>::X] * scalar;
    result.data[Vector4<Real>::Y] = v.data[Vector4<Real>::Y] * scalar;
    result.data[Vector4<Real>::Z] = v.data[Vector4<Real>::Z] * scalar;
    return result;
}

template <typename Real>
Vector4<Real> operator * (Real scalar, const Vector4<Real>& v) {
    Vector4<Real> result;
    result.data[Vector4<Real>::W] = scalar * v.data[Vector4<Real>::W];
    result.data[Vector4<Real>::X] = scalar * v.data[Vector4<Real>::X];
    result.data[Vector4<Real>::Y] = scalar * v.data[Vector4<Real>::Y];
    result.data[Vector4<Real>::Z] = scalar * v.data[Vector4<Real>::Z];
    return result;
}

template <typename Real>
Vector4<Real> operator / (const Vector4<Real>& v, Real scalar) {
    Vector4<Real> result;
    result.data[Vector4<Real>::W] = v.data[Vector4<Real>::W] / scalar;
    result.data[Vector4<Real>::X] = v.data[Vector4<Real>::X] / scalar;
    result.data[Vector4<Real>::Y] = v.data[Vector4<Real>::Y] / scalar;
    result.data[Vector4<Real>::Z] = v.data[Vector4<Real>::Z] / scalar;
    return result;
}

template <typename Real>
std::ostream& operator << (std::ostream& out, const Vector4<Real>& v) {
    std::cout << std::fixed << std::setprecision(6);
    out << "[w:" << v.data[Vector4<Real>::W] << " x:" << v.data[Vector4<Real>::X] << " y:" << v.data[Vector4<Real>::Y] << " z:" << v.data[Vector4<Real>::Z] << "]" << std::endl;
    return out;
}

template <typename Real>
std::istream& operator >> (std::istream& in, Vector4<Real>& v) {
    in >> v.data[Vector4<Real>::W];
    in >> v.data[Vector4<Real>::X];
    in >> v.data[Vector4<Real>::Y];
    in >> v.data[Vector4<Real>::Z];
    return in;
}

template <typename Real>
Vector4<Real> Vector4<Real>::operator - (const Vector4<Real>& v) const {
    Vector4<Real> result;
    result.data[W] = this->data[W] - v.data[W];
    result.data[X] = this->data[X] - v.data[X];
    result.data[Y] = this->data[Y] - v.data[Y];
    result.data[Z] = this->data[Z] - v.data[Z];
    return result;
}

template <typename Real>
Vector4<Real> Vector4<Real>::operator + (const Vector4<Real>& v) const {
    Vector4<Real> result;
    result.data[W] = this->data[W] + v.data[W];
    result.data[X] = this->data[X] + v.data[X];
    result.data[Y] = this->data[Y] + v.data[Y];
    result.data[Z] = this->data[Z] + v.data[Z];
    return result;
}

template <typename Real>
Vector4<Real> Vector4<Real>::operator * (const Real& scalar) const {
    Vector4<Real> result;
    result.data[W] = this->data[W] * scalar;
    result.data[X] = this->data[X] * scalar;
    result.data[Y] = this->data[Y] * scalar;
    result.data[Z] = this->data[Z] * scalar;
    return result;
}

template <typename Real>
Vector4<Real> Vector4<Real>::operator * (const Vector4<Real>& v) const {
    Vector4<Real> result;
    result.data[W] = this->data[W] * v.data[W];
    result.data[X] = this->data[X] * v.data[X];
    result.data[Y] = this->data[Y] * v.data[Y];
    result.data[Z] = this->data[Z] * v.data[Z];
    return result;
}

template <typename Real>
Vector4<Real>& Vector4<Real>::operator = (const Vector4<Real>& v) {
    if ( this == &v ) return *this;
    this->data[W] = v.data[W];
    this->data[X] = v.data[X];
    this->data[Y] = v.data[Y];
    this->data[Z] = v.data[Z];
    return *this;
}

template <typename Real>
Vector4<Real>& Vector4<Real>::operator += (const Vector4<Real>& v) {
    this->data[W] += v.data[W];
    this->data[X] += v.data[X];
    this->data[Y] += v.data[Y];
    this->data[Z] += v.data[Z];
    return *this;
}

template <typename Real>
Vector4<Real>& Vector4<Real>::operator -= (const Vector4<Real>& v) {
    this->data[W] -= v.data[W];
    this->data[X] -= v.data[X];
    this->data[Y] -= v.data[Y];
    this->data[Z] -= v.data[Z];
    return *this;
}

template <typename Real>
Vector4<Real>& Vector4<Real>::operator *= (const Vector4<Real>& v) {
    this->data[W] *= v.data[W];
    this->data[X] *= v.data[X];
    this->data[Y] *= v.data[Y];
    this->data[Z] *= v.data[Z];
    return *this;
}

template <typename Real>
Vector4<Real>& Vector4<Real>::operator *= (Real scalar) {
    this->data[W] *= scalar;
    this->data[X] *= scalar;
    this->data[Y] *= scalar;
    this->data[Z] *= scalar;
    return *this;
}

template <typename Real>
bool Vector4<Real>::operator == (const Vector4<Real>& v) const {
    if ( this->data[W] == v.data[W] &&
         this->data[X] == v.data[X] && 
         this->data[Y] == v.data[Y] && 
         this->data[Z] == v.data[Z] ) return true;
    return false;
}

template <typename Real>
bool Vector4<Real>::operator != (const Vector4<Real>& v) const {
    return !(*this == vector);
}

template <typename Real>
bool Vector4<Real>::operator < (const Vector4<Real>& v) {
    if ( this->norm() < v.norm() ) return true;
    return false;
}

template <typename Real>
bool Vector4<Real>::operator <= (const Vector4<Real>& v) {
    if ( this->norm() <= v.norm() ) return true;
    return false;
}

template <typename Real>
bool Vector4<Real>::operator > (const Vector4<Real>& v) {
    if ( this->norm() > v.norm() ) return true;
    return false;
}

template <typename Real>
bool Vector4<Real>::operator >= (const Vector4<Real>& v) {
    if ( this->norm() >= v.norm() ) return true;
    return false;
}

template <typename Real>
Vector4<Real> Vector4<Real>::Add(const Vector4<Real>& u, const Vector4<Real>& v) {
    Vector4<Real> result;
    result.data[W] = u.data[W] + v.data[W];
    result.data[X] = u.data[X] + v.data[X];
    result.data[Y] = u.data[Y] + v.data[Y];
    result.data[Z] = u.data[Z] + v.data[Z];
    return result;
}

template <typename Real>
Vector4<Real> Vector4<Real>::Subtract(const Vector4<Real>& u, const Vector4<Real>& v) {
    Vector4<Real> result;
    result.data[W] = u.data[W] - v.data[W];
    result.data[X] = u.data[X] - v.data[X];
    result.data[Y] = u.data[Y] - v.data[Y];
    result.data[Z] = u.data[Z] - v.data[Z];
    return result;
}

template <typename Real>
Vector4<Real> Vector4<Real>::Multiply(Real scalar, const Vector4<Real>& v) {
    Vector4<Real> result = v;
    result.data[W] *= scalar;
    result.data[X] *= scalar;
    result.data[Y] *= scalar;
    result.data[Z] *= scalar;
    return result;
}

template <typename Real>
Vector4<Real> Vector4<Real>::Normalize(const Vector4<Real>& v) {
    Vector4<Real> result;
    double invlen = 1.0 / static_cast<double>(v.length());
    result.data[W] *= Real(invlen);
    result.data[X] *= Real(invlen);
    result.data[Y] *= Real(invlen);
    result.data[Z] *= Real(invlen);
    return result;
}

template <typename Real>
Vector4<Real> Vector4<Real>::LinearInterpolation(const Vector4<Real>& u, const Vector4<Real>& v, Real t) {
    return (a * t) + b * (Real(1) - t);
}

template <typename Real>
Vector4<Real> Vector4<Real>::Project(const Vector4<Real>& u, const Vector4<Real>& v) {
    Vector4<Real> uNormalized = u.normalized();
    Vector4<Real> vNormalized = v.normalized();
    Real dot = u.dot(v);
    Real mag = dot * v.norm();
    return (v * mag);
}

template <typename Real>
double Vector4<Real>::Dot(const Vector4<Real>& u, const Vector4<Real>& v) {
    return u.w() * v.w() + u.x() * v.x() + u.y() * v.y() + u.z() * v.y();
}

template <typename Real>
double Vector4<Real>::Magnitude(const Vector4<Real>& v) {
    return std::sqrt(Vector4<Real>::NormSquared(v));
}

template <typename Real>
double Vector4<Real>::Norm(const Vector4<Real>& v) {
    return std::sqrt(Vector4<Real>::NormSquared(v));
}

template <typename Real>
double Vector4<Real>::NormSquared(const Vector4<Real>& v) {
    return std::pow(v.data[W], Real(2)) + std::pow(v.data[X], Real(2)) + std::pow(v.data[Y], Real(2)) + std::pow(v.data[Z], Real(2));
}

template <typename Real>
double Vector4<Real>::Length(const Vector4<Real>& v) {
    return std::sqrt(Vector4<Real>::LengthSquared(v));
}

template <typename Real>
double Vector4<Real>::LengthSquared(const Vector4<Real>& v) {
    return std::pow(v.data[W], Real(2)) + std::pow(v.data[X], Real(2)) + std::pow(v.data[Y], Real(2)) + std::pow(v.data[Z], Real(2));
}

template <typename Real>
double Vector4<Real>::Distance(const Vector4<Real>& u, const Vector4<Real>& v) {
    return std::sqrt(Vector4<Real>::DistanceSquared(u, v));
}

template <typename Real>
double Vector4<Real>::DistanceSquared(const Vector4<Real>& u, const Vector4<Real>& v) {
    return std::pow(u.data[W] - v.data[W], Real(2)) + std::pow(u.data[X] - v.data[X], Real(2)) + std::pow(u.data[Y] - v.data[Y], Real(2)) + std::pow(u.data[Z] - v.data[Z], Real(2));
}

template <typename Real>
Vector4<Real> Vector4<Real>::Zero() {
    return Vector4<Real>();
}

template <typename Real>
Vector4<Real> Vector4<Real>::UnitW() {
    return Vector4<Real>(Real(1), Real(0), Real(0), Real(0));
}

template <typename Real>
Vector4<Real> Vector4<Real>::UnitX() {
    return Vector4<Real>(Real(0), Real(1), Real(0), Real(0));
}

template <typename Real>
Vector4<Real> Vector4<Real>::UnitY() {
    return Vector4<Real>(Real(0), Real(0), Real(1), Real(0));
}

template <typename Real>
Vector4<Real> Vector4<Real>::UnitZ() {
    return Vector4<Real>(Real(0), Real(0), Real(0), Real(1));
}

template <typename Real>
Vector4<Real> Vector4<Real>::UnitNW() {
    return Vector4<Real>(Real(-1), Real(0), Real(0), Real(0));
}

template <typename Real>
Vector4<Real> Vector4<Real>::UnitNX() {
    return Vector4<Real>(Real(0), Real(-1), Real(0), Real(0));
}

template <typename Real>
Vector4<Real> Vector4<Real>::UnitNY() {
    return Vector4<Real>(Real(0), Real(0), Real(-1), Real(0));
}

template <typename Real>
Vector4<Real> Vector4<Real>::UnitNZ() {
    return Vector4<Real>(Real(0), Real(0), Real(0), Real(-1));
}

typedef Vector4<long double> Vector4ld;
typedef Vector4<double> Vector4d;
typedef Vector4<float> Vector4f;
typedef Vector4<long> Vector4l;
typedef Vector4<int> Vector4i;
typedef Vector4<short> Vector4s;
typedef Vector4<long double> Vec4ld;
typedef Vector4<double> Vec4d;
typedef Vector4<float> Vec4f;
typedef Vector4<long> Vec4l;
typedef Vector4<int> Vec4i;
typedef Vector4<short> Vec4s;

typedef Vector4<float> Vec4;

#endif
