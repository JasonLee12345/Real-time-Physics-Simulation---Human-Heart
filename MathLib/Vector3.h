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
#ifndef VECTOR_3_H
#define VECTOR_3_H

#include <iostream>
#include <cmath>
#include <type_traits>
#include <iomanip>

template <typename Real>
class Vector3;

template <typename Real>
Vector3<Real> operator + (const Vector3<Real>& u, const Vector3<Real>& v);

template <typename Real>
Vector3<Real> operator - (const Vector3<Real>& u, const Vector3<Real>& v);

template <typename Real>
Vector3<Real> operator - (const Vector3<Real>& v);

template <typename Real>
Vector3<Real> operator * (const Vector3<Real>& v, Real scalar);

template <typename Real>
Vector3<Real> operator * (Real scalar, const Vector3<Real>& v);

template <typename Real>
Vector3<Real> operator / (const Vector3<Real>& v, Real scalar);

template <typename Real>
std::ostream& operator << (std::ostream& out, const Vector3<Real>& vector);

template <typename Real>
std::istream& operator >> (std::istream& in, Vector3<Real>& vector);

/* 
 * Vector3: Representation of any numerical vector in three dimensions.
 *
 * (x, y, z)
 * 
 * Implements the mathematical defintion of a Vector3. Do not perform long 
 * "temp-chains" using overloaded operators. This implementaton does not utilize 
 * template meta programming.
 * See: http://www.flipcode.com/archives/Faster_Vector_Math_Using_Templates.shtml
 *
 * This implementation also foregoes vectorization (SSE).
 * This implementation is aimed at a flexibility while preserving 
 * understandability and complete modularity.
 */
template <typename Real>
class Vector3 {
    static_assert(std::is_integral<Real>::value || std::is_floating_point<Real>::value, 
    "[Vector3:Type] Error: Vector3 Real type must be an integral or floating point numerical representation.");

    enum Axis { X, Y, Z, COMPONENT_COUNT };

public:
    Vector3(Real x = Real(0), Real y = Real(0), Real z = Real(0));
    Vector3(const Vector3<Real>& v);
    Vector3(Real v[3]);
    Vector3(const Vector3<Real>& from, const Vector3<Real>& to);
    ~Vector3();

    void add(const Vector3<Real>& v);
    void subtract(const Vector3<Real>& v);
    void multiply(Real scalar);
    void normalize();
    void inverse();
    
    void zero();
    bool isZero(Real epsilon);
    bool isEqual(const Vector3<Real>& v);
    bool isEquivalent(const Vector3<Real>& v, Real epsilon) const;

    template <typename RealCastType>
    Vector3<RealCastType> cast();

    Vector3<Real> normalized() const;
    Vector3<Real> cross(const Vector3<Real>& v) const;
    Vector3<Real> linearInterpolation(const Vector3<Real>& v, Real t);
    double dot(const Vector3<Real>& v) const;
    
    double angle(const Vector3<Real>& v) const;
    double magnitude() const;
    double length() const;
    double lengthSquared() const;
    double norm() const;
    double normSquared() const;
    double distance(const Vector3<Real>& v) const;
    double distanceSquared(const Vector3<Real>& v) const;

    void swapXY();
    void swapXZ();
    void swapYZ();

    void set(Real x, Real y, Real z);
    void set(const Vector3<Real>& v);
    void setX(Real x);
    void setY(Real y);
    void setZ(Real z);

    const Real& getX() const;
    const Real& getY() const;
    const Real& getZ() const;
    const Real& x() const;
	const Real& y() const;
	const Real& z() const;
	
    Real& getX();
    Real& getY();
    Real& getZ();
	Real& x();
	Real& y();
	Real& z();

    const Real* const constData() const;
    operator const Real* const () const;
    Real operator () (const Vector3<Real>& v) const;
    bool operator () (const Vector3<Real>& u, const Vector3<Real>& v) const;

    Real& operator [] (std::size_t index);

    friend Vector3<Real> operator + <> (const Vector3<Real>& u, const Vector3<Real>& v);
    friend Vector3<Real> operator - <> (const Vector3<Real>& u, const Vector3<Real>& v);
    friend Vector3<Real> operator - <> (const Vector3<Real>& v);
    friend Vector3<Real> operator * <> (const Vector3<Real>& v, Real scalar);
    friend Vector3<Real> operator * <> (Real scalar, const Vector3<Real>& v);
    friend Vector3<Real> operator / <> (const Vector3<Real>& v, Real scalar);

    friend std::ostream& operator << <> (std::ostream& out, const Vector3<Real>& v);
    friend std::istream& operator >> <> (std::istream& in, Vector3<Real>& v);

    Vector3<Real> operator - (const Vector3<Real>& v) const;
	Vector3<Real> operator + (const Vector3<Real>& v) const;
    Vector3<Real> operator / (const Real& scalar) const;
	Vector3<Real> operator * (const Real& scalar) const;
	Vector3<Real> operator * (const Vector3<Real>& v) const;

    Vector3<Real>& operator = (const Vector3<Real>& v);

    Vector3<Real>& operator += (const Vector3<Real>& v);
    Vector3<Real>& operator -= (const Vector3<Real>& v);
    Vector3<Real>& operator *= (const Vector3<Real>& v);
    Vector3<Real>& operator *= (Real scalar);

    bool operator == (const Vector3<Real>& v) const;
	bool operator != (const Vector3<Real>& v) const;
	
    bool operator < (const Vector3<Real>& v);
    bool operator <= (const Vector3<Real>& v);
    bool operator > (const Vector3<Real>& v);
    bool operator >= (const Vector3<Real>& v);

    static Vector3<Real> Add(const Vector3<Real>& u, const Vector3<Real>& v);
    static Vector3<Real> Subtract(const Vector3<Real>& u, const Vector3<Real>& v);
    static Vector3<Real> Multiply(Real scalar, const Vector3<Real>& v);
    static Vector3<Real> Normalize(const Vector3<Real>& v);
    static Vector3<Real> Cross(const Vector3<Real>& u, const Vector3<Real>& v);
    static Vector3<Real> LinearInterpolation(const Vector3<Real>& u, const Vector3<Real>& v, Real t);
    static Vector3<Real> Project(const Vector3<Real>& u, const Vector3<Real>& v);

    static double Angle(const Vector3<Real>& u, const Vector3<Real>& v);
    static double Dot(const Vector3<Real>& u, const Vector3<Real>& v);
    static double Magnitude(const Vector3<Real>& v);
    static double Norm(const Vector3<Real>& v);
    static double NormSquared(const Vector3<Real>& v);
    static double Length(const Vector3<Real>& v);
    static double LengthSquared(const Vector3<Real>& v);
    static double Distance(const Vector3<Real>& u, const Vector3<Real>& v);
    static double DistanceSquared(const Vector3<Real>& u, const Vector3<Real>& v);

    static Vector3<Real> Zero();
	static Vector3<Real> UnitX();
	static Vector3<Real> UnitY();
	static Vector3<Real> UnitZ();
    static Vector3<Real> UnitNX();
    static Vector3<Real> UnitNY();
    static Vector3<Real> UnitNZ();

protected:
    Real data[COMPONENT_COUNT];
};

template <typename Real>
Vector3<Real>::Vector3(Real x, Real y, Real z) {
    this->data[X] = x;
    this->data[Y] = y;
    this->data[Z] = z;
}

template <typename Real>
Vector3<Real>::Vector3(const Vector3<Real>& v) {
    this->data[X] = v.data[X];
    this->data[Y] = v.data[Y];
    this->data[Z] = v.data[Z];
}

template <typename Real>
Vector3<Real>::Vector3(Real v[3]) {
    this->data[X] = v[0];
    this->data[Y] = v[1];
    this->data[Z] = v[2];
}

template <typename Real>
Vector3<Real>::Vector3(const Vector3<Real>& from, const Vector3<Real>& to) {
    this->data[X] = to.data[X] - from.data[X];
    this->data[Y] = to.data[Y] - from.data[Y];
    this->data[Z] = to.data[Z] - from.data[Z];
}

template <typename Real>
Vector3<Real>::~Vector3() {}

template <typename Real>
void Vector3<Real>::add(const Vector3<Real>& v) {
    this->data[X] += v.data[X];
    this->data[Y] += v.data[Y];
    this->data[Z] += v.data[Z];
}

template <typename Real>
void Vector3<Real>::subtract(const Vector3<Real>& v) {
    this->data[X] -= v.data[X];
    this->data[Y] -= v.data[Y];
    this->data[Z] -= v.data[Z];
}

template <typename Real>
void Vector3<Real>::multiply(Real scalar) {
    this->data[X] *= scalar;
    this->data[Y] *= scalar;
    this->data[Z] *= scalar;
}

template <typename Real>
void Vector3<Real>::normalize() {
    double invLen = 1.0 / static_cast<double>(this->length());
    this->data[X] *= Real(invLen);
    this->data[Y] *= Real(invLen);
    this->data[Z] *= Real(invLen);
}

template <typename Real>
void Vector3<Real>::inverse() {
    this->data[X] = -this->data[X];
    this->data[Y] = -this->data[Y];
    this->data[Z] = -this->data[Z];
}
    
template <typename Real>
void Vector3<Real>::zero() {
    this->data[X] = Real(0);
    this->data[Y] = Real(0);
    this->data[Z] = Real(0);
}

template <typename Real>
bool Vector3<Real>::isZero(Real epsilon) {
    if ( (this->data[X] > -epsilon) && 
         (this->data[X] < epsilon ) &&
         (this->data[Y] > -epsilon) &&
         (this->data[Y] < epsilon ) &&
         (this->data[Z] > -epsilon) &&
         (this->data[Z] < epsilon ) )
    return true;
    else return false;
}

template <typename Real>
bool Vector3<Real>::isEqual(const Vector3<Real>& v) {
    if ( *this == vector ) return true;
    return false;
}

template <typename Real>
bool Vector3<Real>::isEquivalent(const Vector3<Real>& v, Real epsilon) const {
    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ )
        if ( this->data[i] < (v.data[i] - epsilon) || this->data[i] > (v.data[i] + epsilon) ) return false;
    return true;
}

template <typename Real>
template <typename RealCastType>
Vector3<RealCastType> Vector3<Real>::cast() {
    return Vector3<RealCastType>(static_cast<RealCastType>(this->data[X]), static_cast<RealCastType>(this->data[Y]), static_cast<RealCastType>(this->data[Z]));
}

template <typename Real>
Vector3<Real> Vector3<Real>::normalized() const {
    Vector3<Real> result = (*this);
    return Vector3<Real>::Normalize(result);
}

template <typename Real>
Vector3<Real> Vector3<Real>::cross(const Vector3<Real>& v) const {
    return Vector3<Real>::Cross(*this, v);
}

template <typename Real>
Vector3<Real> Vector3<Real>::linearInterpolation(const Vector3<Real>& v, Real t) {
    return Vector3<Real>::LinearInterpolation(*this, v, t);
}

template <typename Real>
double Vector3<Real>::dot(const Vector3<Real>& v) const {
    return Vector3<Real>::Dot(*this, v);
}

template <typename Real>
double Vector3<Real>::angle(const Vector3<Real>& v) const {
    return Vector3<Real>::Angle(*this, v);
}

template <typename Real>
double Vector3<Real>::magnitude() const {
    return Vector3<Real>::Magnitude(*this);
}

template <typename Real>
double Vector3<Real>::length() const {
    return Vector3<Real>::Length(*this);
}

template <typename Real>
double Vector3<Real>::lengthSquared() const {
    return Vector3<Real>::LengthSquared(*this);
}

template <typename Real>
double Vector3<Real>::norm() const {
    return Vector3<Real>::Norm(*this);
}

template <typename Real>
double Vector3<Real>::normSquared() const {
    return Vector3<Real>::NormSquared(*this);
}

template <typename Real>
double Vector3<Real>::distance(const Vector3<Real>& v) const {
    return Vector3<Real>::Distance(*this, v);
}

template <typename Real>
double Vector3<Real>::distanceSquared(const Vector3<Real>& v) const {
    return Vector3<Real>::DistanceSquared(*this, v);
}

template <typename Real>
void Vector3<Real>::swapXY() {
    std::swap(this->data[X], this->data[Y]);
}

template <typename Real>
void Vector3<Real>::swapXZ() {
    std::swap(this->data[X], this->data[Z]);
}

template <typename Real>
void Vector3<Real>::swapYZ() {
    std::swap(this->data[Y], this->data[Z]);
}

template <typename Real>
void Vector3<Real>::set(Real x, Real y, Real z) {
    this->data[X] = x;
    this->data[Y] = y;
    this->data[Z] = z;
}

template <typename Real>
void Vector3<Real>::set(const Vector3<Real>& v) {
    this->data[X] = v.data[X];
    this->data[Y] = v.data[Y];
    this->data[Z] = v.data[Z];
}

template <typename Real>
void Vector3<Real>::setX(Real x) {
    this->data[X] = x;
}

template <typename Real>
void Vector3<Real>::setY(Real y) {
    this->data[Y] = y;
}

template <typename Real>
void Vector3<Real>::setZ(Real z) {
    this->data[Z] = z;
}

template <typename Real>
const Real& Vector3<Real>::getX() const {
    return this->data[X];
}

template <typename Real>
const Real& Vector3<Real>::getY() const {
    return this->data[Y];
}

template <typename Real>
const Real& Vector3<Real>::getZ() const {
    return this->data[Z];
}

template <typename Real>
const Real& Vector3<Real>::x() const {
    return this->data[X];
}

template <typename Real>
const Real& Vector3<Real>::y() const {
    return this->data[Y];
}

template <typename Real>
const Real& Vector3<Real>::z() const {
    return this->data[Z];
}
	
template <typename Real>
Real& Vector3<Real>::getX() {
    return this->data[X];
}

template <typename Real>
Real& Vector3<Real>::getY() {
    return this->data[Y];
}

template <typename Real>
Real& Vector3<Real>::getZ() {
    return this->data[Z];
}

template <typename Real>
Real& Vector3<Real>::x() {
    return this->data[X];
}

template <typename Real>
Real& Vector3<Real>::y() {
    return this->data[Y];
}

template <typename Real>
Real& Vector3<Real>::z() {
    return this->data[Z];
}

template <typename Real>
const Real* const Vector3<Real>::constData() const {
    return this->data;
}

template <typename Real>
Vector3<Real>::operator const Real* const () const {
    return this->data;
}

template <typename Real>
Real Vector3<Real>::operator () (const Vector3<Real>& v) const {
    return this->data[X] + this->data[Y] + this->data[Z];
}

template <typename Real>
bool Vector3<Real>::operator () (const Vector3<Real>& u, const Vector3<Real>& v) const {
    if ( u.data[X] == v.data[X] && u.data[Y] == v.data[Y] && u.data[Z] == v.data[Z] ) return true;
    return false;
}

template <typename Real>
Real& Vector3<Real>::operator [] (std::size_t index) {
    if ( index >= COMPONENT_COUNT ) throw std::exception("[Vector3:[]] Error: Index out of bounds.");
    return this->data[index];
}

template <typename Real>
Vector3<Real> operator + (const Vector3<Real>& u, const Vector3<Real>& v) {
    Vector3<Real> result;
    result.data[Vector3<Real>::X] = u.data[Vector3<Real>::X] + v.data[Vector3<Real>::X];
    result.data[Vector3<Real>::Y] = u.data[Vector3<Real>::Y] + v.data[Vector3<Real>::Y];
    result.data[Vector3<Real>::Z] = u.data[Vector3<Real>::Z] + v.data[Vector3<Real>::Z];
    return result;
}

template <typename Real>
Vector3<Real> operator - (const Vector3<Real>& u, const Vector3<Real>& v) {
    Vector3<Real> result;
    result.data[Vector3<Real>::X] = u.data[Vector3<Real>::X] - v.data[Vector3<Real>::X];
    result.data[Vector3<Real>::Y] = u.data[Vector3<Real>::Y] - v.data[Vector3<Real>::Y];
    result.data[Vector3<Real>::Z] = u.data[Vector3<Real>::Z] - v.data[Vector3<Real>::Z];
    return result;
}

template <typename Real>
Vector3<Real> operator - (const Vector3<Real>& v) {
    return Vector3<Real>(-v.data[Vector3<Real>::X], -v.data[Vector3<Real>::Y], -v.data[Vector3<Real>::Z]);
}

template <typename Real>
Vector3<Real> operator * (const Vector3<Real>& v, Real scalar) {
    Vector3<Real> result;
    result.data[Vector3<Real>::X] = v.data[Vector3<Real>::X] * scalar;
    result.data[Vector3<Real>::Y] = v.data[Vector3<Real>::Y] * scalar;
    result.data[Vector3<Real>::Z] = v.data[Vector3<Real>::Z] * scalar;
    return result;
}

template <typename Real>
Vector3<Real> operator * (Real scalar, const Vector3<Real>& v) {
    Vector3<Real> result;
    result.data[Vector3<Real>::X] = scalar * v.data[Vector3<Real>::X];
    result.data[Vector3<Real>::Y] = scalar * v.data[Vector3<Real>::Y];
    result.data[Vector3<Real>::Z] = scalar * v.data[Vector3<Real>::Z];
    return result;
}

template <typename Real>
Vector3<Real> operator / (const Vector3<Real>& v, Real scalar) {
    Vector3<Real> result;
    result.data[Vector3<Real>::X] = v.data[Vector3<Real>::X] / scalar;
    result.data[Vector3<Real>::Y] = v.data[Vector3<Real>::Y] / scalar;
    result.data[Vector3<Real>::Z] = v.data[Vector3<Real>::Z] / scalar;
    return result;
}

template <typename Real>
std::ostream& operator << (std::ostream& out, const Vector3<Real>& v) {
    std::cout << std::fixed << std::setprecision(6);
    out << "[x:" << v.data[Vector3<Real>::X] << " y:" << v.data[Vector3<Real>::Y] << " z:" << v.data[Vector3<Real>::Z] << "]" << std::endl;
    return out;
}

template <typename Real>
std::istream& operator >> (std::istream& in, Vector3<Real>& v) {
    in >> v.data[Vector3<Real>::X];
    in >> v.data[Vector3<Real>::Y];
    in >> v.data[Vector3<Real>::Z];
    return in;
}

template <typename Real>
Vector3<Real> Vector3<Real>::operator - (const Vector3<Real>& v) const {
    Vector3<Real> result;
    result.data[X] = this->data[X] - v.data[X];
    result.data[Y] = this->data[Y] - v.data[Y];
    result.data[Z] = this->data[Z] - v.data[Z];
    return result;
}

template <typename Real>
Vector3<Real> Vector3<Real>::operator + (const Vector3<Real>& v) const {
    Vector3<Real> result;
    result.data[X] = this->data[X] + v.data[X];
    result.data[Y] = this->data[Y] + v.data[Y];
    result.data[Z] = this->data[Z] + v.data[Z];
    return result;
}

template <typename Real>
Vector3<Real> Vector3<Real>::operator / (const Real& scalar) const {
    Vector3<Real> result;
    result.data[X] = this->data[X] / scalar;
    result.data[Y] = this->data[Y] / scalar;
    result.data[Z] = this->data[Z] / scalar;
    return result;
}

template <typename Real>
Vector3<Real> Vector3<Real>::operator * (const Real& scalar) const {
    Vector3<Real> result;
    result.data[X] = this->data[X] * scalar;
    result.data[Y] = this->data[Y] * scalar;
    result.data[Z] = this->data[Z] * scalar;
    return result;
}

template <typename Real>
Vector3<Real> Vector3<Real>::operator * (const Vector3<Real>& v) const {
    Vector3<Real> result;
    result.data[X] = this->data[X] * v.data[X];
    result.data[Y] = this->data[Y] * v.data[Y];
    result.data[Z] = this->data[Z] * v.data[Z];
    return result;
}

template <typename Real>
Vector3<Real>& Vector3<Real>::operator = (const Vector3<Real>& v) {
    if ( this == &v ) return *this;
    this->data[X] = v.data[X];
    this->data[Y] = v.data[Y];
    this->data[Z] = v.data[Z];
    return *this;
}

template <typename Real>
Vector3<Real>& Vector3<Real>::operator += (const Vector3<Real>& v) {
    this->data[X] += v.data[X];
    this->data[Y] += v.data[Y];
    this->data[Z] += v.data[Z];
    return *this;
}

template <typename Real>
Vector3<Real>& Vector3<Real>::operator -= (const Vector3<Real>& v) {
    this->data[X] -= v.data[X];
    this->data[Y] -= v.data[Y];
    this->data[Z] -= v.data[Z];
    return *this;
}

template <typename Real>
Vector3<Real>& Vector3<Real>::operator *= (const Vector3<Real>& v) {
    this->data[X] *= v.data[X];
    this->data[Y] *= v.data[Y];
    this->data[Z] *= v.data[Z];
    return *this;
}

template <typename Real>
Vector3<Real>& Vector3<Real>::operator *= (Real scalar) {
    this->data[X] *= scalar;
    this->data[Y] *= scalar;
    this->data[Z] *= scalar;
    return *this;
}

template <typename Real>
bool Vector3<Real>::operator == (const Vector3<Real>& v) const {
    if ( this->data[X] == v.data[X] && 
         this->data[Y] == v.data[Y] && 
         this->data[Z] == v.data[Z] ) return true;
    return false;
}

template <typename Real>
bool Vector3<Real>::operator != (const Vector3<Real>& v) const {
    return !(*this == vector);
}
	
template <typename Real>
bool Vector3<Real>::operator < (const Vector3<Real>& v) {
    if ( this->norm() < v.norm() ) return true;
    return false;
}

template <typename Real>
bool Vector3<Real>::operator <= (const Vector3<Real>& v) {
    if ( this->norm() <= v.norm() ) return true;
    return false;
}

template <typename Real>
bool Vector3<Real>::operator > (const Vector3<Real>& v) {
    if ( this->norm() > v.norm() ) return true;
    return false;
}

template <typename Real>
bool Vector3<Real>::operator >= (const Vector3<Real>& v) {
    if ( this->norm() >= v.norm() ) return true;
    return false;
}

template <typename Real>
Vector3<Real> Vector3<Real>::Add(const Vector3<Real>& u, const Vector3<Real>& v) {
    Vector3<Real> result;
    result.data[X] = u.data[X] + v.data[X];
    result.data[Y] = u.data[Y] + v.data[Y];
    result.data[Z] = u.data[Z] + v.data[Z];
    return result;
}

template <typename Real>
Vector3<Real> Vector3<Real>::Subtract(const Vector3<Real>& u, const Vector3<Real>& v) {
    Vector3<Real> result;
    result.data[X] = u.data[X] - v.data[X];
    result.data[Y] = u.data[Y] - v.data[Y];
    result.data[Z] = u.data[Z] - v.data[Z];
    return result;
}

template <typename Real>
Vector3<Real> Vector3<Real>::Multiply(Real scalar, const Vector3<Real>& v) {
    Vector3<Real> result;
    result.data[X] = scalar * v.data[X];
    result.data[Y] = scalar * v.data[Y];
    result.data[Z] = scalar * v.data[Z];
    return result;
}

template <typename Real>
Vector3<Real> Vector3<Real>::Normalize(const Vector3<Real>& v) {
    Vector3<Real> result;
    double invLen = 1.0 / static_cast<double>(v.length());
    result.data[X] = v.data[X] * Real(invLen);
    result.data[Y] = v.data[Y] * Real(invLen);
    result.data[Z] = v.data[Z] * Real(invLen);
    return result;
}

template <typename Real>
Vector3<Real> Vector3<Real>::Cross(const Vector3<Real>& u, const Vector3<Real>& v) {
    Vector3<Real> result;
    result.data[X] = ((u.data[Y] * v.data[Z]) - (u.data[Z] * v.data[Y]));
    result.data[Y] = ((u.data[Z] * v.data[X]) - (u.data[X] * v.data[Z]));
    result.data[Z] = ((u.data[X] * v.data[Y]) - (u.data[Y] * v.data[X]));
    return result;
}

template <typename Real>
Vector3<Real> Vector3<Real>::LinearInterpolation(const Vector3<Real>& u, const Vector3<Real>& v, Real t) {
    return (a * t) + b * (Real(1) - t);
}

template <typename Real>
Vector3<Real> Vector3<Real>::Project(const Vector3<Real>& u, const Vector3<Real>& v) {
    Vector3<Real> uNormalized = u.normalized();
    Vector3<Real> vNormalized = v.normalized();
    Real dot = u.dot(v);
    Real mag = dot * v.norm();
    return (v * mag);
}

template <typename Real>
double Vector3<Real>::Angle(const Vector3<Real>& u, const Vector3<Real>& v) {
    return std::acos((this->data[X] * vector.data[X] + this->data[Y] * vector.data[Y] + this->data[Z] * vector.data[Z]) / (this->norm() * vector.norm()));
}

template <typename Real>
double Vector3<Real>::Dot(const Vector3<Real>& u, const Vector3<Real>& v) {
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

template <typename Real>
double Vector3<Real>::Magnitude(const Vector3<Real>& v) {
    return std::sqrt(Vector3<Real>::NormSquared(v));
}

template <typename Real>
double Vector3<Real>::Norm(const Vector3<Real>& v) {
    return std::sqrt(Vector3<Real>::NormSquared(v));
}

template <typename Real>
double Vector3<Real>::NormSquared(const Vector3<Real>& v) {
    return std::pow(v.data[X], Real(2)) + std::pow(v.data[Y], Real(2)) + std::pow(v.data[Z], Real(2));
}

template <typename Real>
double Vector3<Real>::Length(const Vector3<Real>& v) {
    return std::sqrt(Vector3<Real>::LengthSquared(v));
}

template <typename Real>
double Vector3<Real>::LengthSquared(const Vector3<Real>& v) {
    return std::pow(v.data[X], Real(2)) + std::pow(v.data[Y], Real(2)) + std::pow(v.data[Z], Real(2));
}

template <typename Real>
double Vector3<Real>::Distance(const Vector3<Real>& u, const Vector3<Real>& v) {
    return std::sqrt(Vector3<Real>::DistanceSquared(u, v));
}

template <typename Real>
double Vector3<Real>::DistanceSquared(const Vector3<Real>& u, const Vector3<Real>& v) {
    return std::pow(u.data[X] - v.data[X], Real(2)) + std::pow(u.data[Y] - v.data[Y], Real(2)) + std::pow(u.data[Z] - v.data[Z], Real(2));
}

template <typename Real>
Vector3<Real> Vector3<Real>::Zero() {
    return Vector3<Real>();
}

template <typename Real>
Vector3<Real> Vector3<Real>::UnitX() {
    return Vector3<Real>(Real(1), Real(0), Real(0));
}

template <typename Real>
Vector3<Real> Vector3<Real>::UnitY() {
    return Vector3<Real>(Real(0), Real(1), Real(0));
}

template <typename Real>
Vector3<Real> Vector3<Real>::UnitZ() {
    return Vector3<Real>(Real(0), Real(0), Real(1));
}

template <typename Real>
Vector3<Real> Vector3<Real>::UnitNX() {
    return Vector3<Real>(Real(-1), Real(0), Real(0));
}

template <typename Real>
Vector3<Real> Vector3<Real>::UnitNY() {
    return Vector3<Real>(Real(0), Real(-1), Real(0));
}

template <typename Real>
Vector3<Real> Vector3<Real>::UnitNZ() {
    return Vector3<Real>(Real(0), Real(0), Real(-1));
}

typedef Vector3<long double> Vector3ld;
typedef Vector3<double> Vector3d;
typedef Vector3<float> Vector3f;
typedef Vector3<long> Vector3l;
typedef Vector3<int> Vector3i;
typedef Vector3<short> Vector3s;
typedef Vector3<long double> Vec3ld;
typedef Vector3<double> Vec3d;
typedef Vector3<float> Vec3f;
typedef Vector3<long> Vec3l;
typedef Vector3<int> Vec3i;
typedef Vector3<short> Vec3s;

typedef Vector3<float> Vec3;

#endif
