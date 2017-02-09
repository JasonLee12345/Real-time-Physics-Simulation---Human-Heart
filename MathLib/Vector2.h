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
#ifndef VECTOR_2_H
#define VECTOR_2_H

#include <iostream>
#include <cmath>
#include <type_traits>
#include <iomanip>

template <typename Real>
class Vector2;

template <typename Real>
Vector2<Real> operator + (const Vector2<Real>& u, const Vector2<Real>& v);

template <typename Real>
Vector2<Real> operator - (const Vector2<Real>& u, const Vector2<Real>& v);

template <typename Real>
Vector2<Real> operator - (const Vector2<Real>& v);

template <typename Real>
Vector2<Real> operator * (const Vector2<Real>& v, Real scalar);

template <typename Real>
Vector2<Real> operator * (Real scalar, const Vector2<Real>& v);

template <typename Real>
Vector2<Real> operator / (const Vector2<Real>& v, Real scalar);

template <typename Real>
std::ostream& operator << (std::ostream& out, const Vector2<Real>& vector);

template <typename Real>
std::istream& operator >> (std::istream& in, Vector2<Real>& vector);

/* 
 * Vector2: Representation of any numerical vector in two dimensions.
 *
 * (x, y)
 * 
 * Implements the mathematical defintion of a Vector2. Do not perform long 
 * "temp-chains" using overloaded operators. This implementaton does not utilize 
 * template meta programming.
 * See: http://www.flipcode.com/archives/Faster_Vector_Math_Using_Templates.shtml
 *
 * This implementation also foregoes vectorization (SSE).
 * This implementation is aimed at a flexibility while preserving 
 * understandability and complete modularity.
 */
template <typename Real>
class Vector2 {
    static_assert(std::is_integral<Real>::value || std::is_floating_point<Real>::value, 
    "[Vector2:Type] Error: Vector2 Real type must be an integral or floating point numerical representation.");

    enum Axis { X, Y, COMPONENT_COUNT };

public:
    Vector2(Real x = Real(0), Real y = Real(0));
    Vector2(const Vector2<Real>& v);
    Vector2(Real v[2]);
    Vector2(const Vector2<Real>& from, const Vector2<Real>& to);
    ~Vector2();

    void add(const Vector2<Real>& v);
    void subtract(const Vector2<Real>& v);
    void multiply(Real scalar);
    void normalize();
    void inverse();
    
    void zero();
    bool isZero(Real epsilon);
    bool isEqual(const Vector2<Real>& v);
    bool isEquivalent(const Vector2<Real>& v, Real epsilon) const;

    template <typename RealCastType>
    Vector2<RealCastType> cast();

    Vector2<Real> normalized() const;
    Vector2<Real> linearInterpolation(const Vector2<Real>& v, Real t);
    double dot(const Vector2<Real>& v) const;
    
    double angle(const Vector2<Real>& v) const;
    double magnitude() const;
    double length() const;
    double lengthSquared() const;
    double norm() const;
    double normSquared() const;
    double distance(const Vector2<Real>& v) const;
    double distanceSquared(const Vector2<Real>& v) const;

    void set(Real x, Real y);
    void set(const Vector2<Real>& v);
    void setX(Real x);
    void setY(Real y);

    const Real& getX() const;
    const Real& getY() const;
    const Real& x() const;
	const Real& y() const;
	
    Real& getX();
    Real& getY();
	Real& x();
	Real& y();

    const Real* const constData() const;
    operator const Real* const () const;
    Real operator () (const Vector2<Real>& v) const;
    bool operator () (const Vector2<Real>& u, const Vector2<Real>& v) const;

    Real& operator [] (std::size_t index);
    const Real& operator [] (std::size_t index) const;

    friend Vector2<Real> operator + <> (const Vector2<Real>& u, const Vector2<Real>& v);
    friend Vector2<Real> operator - <> (const Vector2<Real>& u, const Vector2<Real>& v);
    friend Vector2<Real> operator - <> (const Vector2<Real>& v);
    friend Vector2<Real> operator * <> (const Vector2<Real>& v, Real scalar);
    friend Vector2<Real> operator * <> (Real scalar, const Vector2<Real>& v);
    friend Vector2<Real> operator / <> (const Vector2<Real>& v, Real scalar);

    friend std::ostream& operator << <> (std::ostream& out, const Vector2<Real>& v);
    friend std::istream& operator >> <> (std::istream& in, Vector2<Real>& v);

    Vector2<Real> operator - (const Vector2<Real>& v) const;
	Vector2<Real> operator + (const Vector2<Real>& v) const;
	Vector2<Real> operator * (const Real& scalar) const;
	Vector2<Real> operator * (const Vector2<Real>& v) const;

    Vector2<Real>& operator = (const Vector2<Real>& v);

    Vector2<Real>& operator += (const Vector2<Real>& v);
    Vector2<Real>& operator -= (const Vector2<Real>& v);
    Vector2<Real>& operator *= (const Vector2<Real>& v);
    Vector2<Real>& operator *= (Real scalar);

    bool operator == (const Vector2<Real>& v) const;
	bool operator != (const Vector2<Real>& v) const;
	
    bool operator < (const Vector2<Real>& v);
    bool operator <= (const Vector2<Real>& v);
    bool operator > (const Vector2<Real>& v);
    bool operator >= (const Vector2<Real>& v);

    static Vector2<Real> Add(const Vector2<Real>& u, const Vector2<Real>& v);
    static Vector2<Real> Subtract(const Vector2<Real>& u, const Vector2<Real>& v);
    static Vector2<Real> Multiply(Real scalar, const Vector2<Real>& v);
    static Vector2<Real> Normalize(const Vector2<Real>& v);
    static Vector2<Real> LinearInterpolation(const Vector2<Real>& u, const Vector2<Real>& v, Real t);
    static Vector2<Real> Project(const Vector2<Real>& u, const Vector2<Real>& v);

    static double Angle(const Vector2<Real>& u, const Vector2<Real>& v);
    static double Dot(const Vector2<Real>& u, const Vector2<Real>& v);
    static double Magnitude(const Vector2<Real>& v);
    static double Norm(const Vector2<Real>& v);
    static double NormSquared(const Vector2<Real>& v);
    static double Length(const Vector2<Real>& v);
    static double LengthSquared(const Vector2<Real>& v);
    static double Distance(const Vector2<Real>& u, const Vector2<Real>& v);
    static double DistanceSquared(const Vector2<Real>& u, const Vector2<Real>& v);

    static Vector2<Real> Zero();
	static Vector2<Real> UnitX();
	static Vector2<Real> UnitY();
    static Vector2<Real> UnitNX();
    static Vector2<Real> UnitNY();

protected:
    Real data[COMPONENT_COUNT];
};

template <typename Real>
Vector2<Real>::Vector2(Real x, Real y) {
    this->data[X] = x;
    this->data[Y] = y;
}

template <typename Real>
Vector2<Real>::Vector2(const Vector2<Real>& v) {
    this->data[X] = v.data[X];
    this->data[Y] = v.data[Y];
}

template <typename Real>
Vector2<Real>::Vector2(Real v[2]) {
    this->data[X] = v[0];
    this->data[Y] = v[1];
}

template <typename Real>
Vector2<Real>::Vector2(const Vector2<Real>& from, const Vector2<Real>& to) {
    this->data[X] = to.data[X] - from.data[X];
    this->data[Y] = to.data[Y] - from.data[Y];
}

template <typename Real>
Vector2<Real>::~Vector2() {}

template <typename Real>
void Vector2<Real>::add(const Vector2<Real>& v) {
    this->data[X] += v.data[X];
    this->data[Y] += v.data[Y];
}

template <typename Real>
void Vector2<Real>::subtract(const Vector2<Real>& v) {
    this->data[X] -= v.data[X];
    this->data[Y] -= v.data[Y];
}

template <typename Real>
void Vector2<Real>::multiply(Real scalar) {
    this->data[X] *= scalar;
    this->data[y] *= scalar;
}

template <typename Real>
void Vector2<Real>::normalize() {
    double invLen = 1.0 / static_cast<double>(this->length());
    this->data[X] *= Real(invLen);
    this->data[Y] *= Real(invLen);
}

template <typename Real>
void Vector2<Real>::inverse() {
    this->data[X] = -this->data[X];
    this->data[Y] = -this->data[Y];
}
    
template <typename Real>
void Vector2<Real>::zero() {
    this->data[X] = Real(0);
    this->data[Y] = Real(0);
}

template <typename Real>
bool Vector2<Real>::isZero(Real epsilon) {
    if ( (this->data[X] > -epsilon) && 
         (this->data[X] < epsilon ) &&
         (this->data[Y] > -epsilon) &&
         (this->data[Y] < epsilon ) )
    return true;
    else return false;
}

template <typename Real>
bool Vector2<Real>::isEqual(const Vector2<Real>& v) {
    if ( *this == vector ) return true;
    return false;
}

template <typename Real>
bool Vector2<Real>::isEquivalent(const Vector2<Real>& v, Real epsilon) const {
    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ )
        if ( this->data[i] < (v.data[i] - epsilon) || this->data[i] > (v.data[i] + epsilon) ) return false;
    return true;
}

template <typename Real>
template <typename RealCastType>
Vector2<RealCastType> Vector2<Real>::cast() {
    return Vector2<RealCastType>(static_cast<RealCastType>(this->data[X]), static_cast<RealCastType>(this->data[Y]));
}

template <typename Real>
Vector2<Real> Vector2<Real>::normalized() const {
    return Vector2<Real>::Normalize(*this);
}

template <typename Real>
Vector2<Real> Vector2<Real>::linearInterpolation(const Vector2<Real>& v, Real t) {
    return Vector2<Real>::LinearInterpolation(*this, v, t);
}

template <typename Real>
double Vector2<Real>::dot(const Vector2<Real>& v) const {
    return Vector2<Real>::Dot(*this, v);
}
    
template <typename Real>
double Vector2<Real>::angle(const Vector2<Real>& v) const {
    return Vector2<Real>::Angle(*this, v);
}

template <typename Real>
double Vector2<Real>::magnitude() const {
    return Vector2<Real>::Magnitude(*this);
}

template <typename Real>
double Vector2<Real>::length() const {
    return Vector2<Real>::Length(*this);
}

template <typename Real>
double Vector2<Real>::lengthSquared() const {
    return Vector2<Real>::LengthSquared(*this);
}

template <typename Real>
double Vector2<Real>::norm() const {
    return Vector2<Real>::Norm(*this);
}

template <typename Real>
double Vector2<Real>::normSquared() const {
    return Vector2<Real>::NormSquared(*this);
}

template <typename Real>
double Vector2<Real>::distance(const Vector2<Real>& v) const {
    return Vector2<Real>::Distance(*this, v);
}

template <typename Real>
double Vector2<Real>::distanceSquared(const Vector2<Real>& v) const {
    return Vector2<Real>::DistanceSquared(*this, v);
}

template <typename Real>
void Vector2<Real>::set(Real x, Real y) {
    this->data[X] = x;
    this->data[Y] = y;
}

template <typename Real>
void Vector2<Real>::set(const Vector2<Real>& v) {
    this->data[X] = v.data[X];
    this->data[Y] = v.data[Y];
}

template <typename Real>
void Vector2<Real>::setX(Real x) {
    this->data[Y] = y;
}

template <typename Real>
void Vector2<Real>::setY(Real y) {
    this->data[Y] = y;
}

template <typename Real>
const Real& Vector2<Real>::getX() const {
    return this->data[X];
}

template <typename Real>
const Real& Vector2<Real>::getY() const {
    return this->data[Y];
}

template <typename Real>
const Real& Vector2<Real>::x() const {
    return this->data[X];
}

template <typename Real>
const Real& Vector2<Real>::y() const {
    return this->data[Y];
}
	
template <typename Real>
Real& Vector2<Real>::getX() {
    return this->data[X];
}

template <typename Real>
Real& Vector2<Real>::getY() {
    return this->data[Y];
}

template <typename Real>
Real& Vector2<Real>::x() {
    return this->data[X];
}

template <typename Real>
Real& Vector2<Real>::y() {
    return this->data[Y];
}

template <typename Real>
const Real* const Vector2<Real>::constData() const {
    return this->data;
}

template <typename Real>
Vector2<Real>::operator const Real* const () const {
    return this->data;
}

template <typename Real>
Real Vector2<Real>::operator () (const Vector2<Real>& v) const {
    return this->data[X] + this->data[Y];
}

template <typename Real>
bool Vector2<Real>::operator () (const Vector2<Real>& u, const Vector2<Real>& v) const {
    if ( u.data[X] == v.data[X] && u.data[Y] == v.data[Y] ) return true;
    return false;
}

template <typename Real>
Real& Vector2<Real>::operator [] (std::size_t index) {
    if ( index >= COMPONENT_COUNT ) throw std::exception("[Vector2:[]] Error: Index out of bounds.");
    return this->data[index];
}

template <typename Real>
const Real& Vector2<Real>::operator [] (std::size_t index) const {
    if ( index >= COMPONENT_COUNT ) throw std::exception("[Vector2:[]] Error: Index out of bounds.");
    return this->data[index];
}

template <typename Real>
Vector2<Real> operator + (const Vector2<Real>& u, const Vector2<Real>& v) {
    Vector2<Real> result;
    result.data[Vector2<Real>::X] = u.data[Vector2<Real>::X] + v.data[Vector2<Real>::X];
    result.data[Vector2<Real>::Y] = u.data[Vector2<Real>::Y] + v.data[Vector2<Real>::Y];
    return result;
}

template <typename Real>
Vector2<Real> operator - (const Vector2<Real>& u, const Vector2<Real>& v) {
    Vector2<Real> result;
    result.data[Vector2<Real>::X] = u.data[Vector2<Real>::X] - v.data[Vector2<Real>::X];
    result.data[Vector2<Real>::Y] = u.data[Vector2<Real>::Y] - v.data[Vector2<Real>::Y];
    return result;
}

template <typename Real>
Vector2<Real> operator - (const Vector2<Real>& v) {
    return Vector2<Real>(-v.data[Vector2<Real>::X], -v.data[Vector2<Real>::Y]);
}

template <typename Real>
Vector2<Real> operator * (const Vector2<Real>& v, Real scalar) {
    Vector2<Real> result;
    result.data[Vector2<Real>::X] = v.data[Vector2<Real>::X] * scalar;
    result.data[Vector2<Real>::Y] = v.data[Vector2<Real>::Y] * scalar;
    return result;
}

template <typename Real>
Vector2<Real> operator * (Real scalar, const Vector2<Real>& v) {
    Vector2<Real> result;
    result.data[Vector2<Real>::X] = scalar * v.data[Vector2<Real>::X];
    result.data[Vector2<Real>::Y] = scalar * v.data[Vector2<Real>::Y];
    return result;
}

template <typename Real>
Vector2<Real> operator / (const Vector2<Real>& v, Real scalar) {
    Vector2<Real> result;
    result.data[Vector2<Real>::X] = v.data[Vector2<Real>::X] / scalar;
    result.data[Vector2<Real>::Y] = v.data[Vector2<Real>::Y] / scalar;
    return result;
}

template <typename Real>
std::ostream& operator << (std::ostream& out, const Vector2<Real>& v) {
    std::cout << std::fixed << std::setprecision(6);
    out << "[x:" << v.data[Vector2<Real>::X] << " y:" << v.data[Vector2<Real>::Y] << "]" << std::endl;
    return out;
}

template <typename Real>
std::istream& operator >> (std::istream& in, Vector2<Real>& v) {
    in >> v.data[Vector2<Real>::X];
    in >> v.data[Vector2<Real>::Y];
    return in;
}

template <typename Real>
Vector2<Real> Vector2<Real>::operator - (const Vector2<Real>& v) const {
    Vector2<Real> result;
    result.data[X] = this->data[X] - v.data[X];
    result.data[Y] = this->data[Y] - v.data[Y];
    return result;
}

template <typename Real>
Vector2<Real> Vector2<Real>::operator + (const Vector2<Real>& v) const {
    Vector2<Real> result;
    result.data[X] = this->data[X] + v.data[X];
    result.data[Y] = this->data[Y] + v.data[Y];
    return result;
}

template <typename Real>
Vector2<Real> Vector2<Real>::operator * (const Real& scalar) const {
    Vector2<Real> result;
    result.data[X] = this->data[X] * scalar;
    result.data[Y] = this->data[Y] * scalar;
    return result;
}

template <typename Real>
Vector2<Real> Vector2<Real>::operator * (const Vector2<Real>& v) const {
    Vector2<Real> result;
    result.data[X] = this->data[X] * v.data[X];
    result.data[Y] = this->data[Y] * v.data[Y];
    return result;
}

template <typename Real>
Vector2<Real>& Vector2<Real>::operator = (const Vector2<Real>& v) {
    if ( this == &v ) return *this;
    this->data[X] = v.data[X];
    this->data[Y] = v.data[Y];
    return *this;
}

template <typename Real>
Vector2<Real>& Vector2<Real>::operator += (const Vector2<Real>& v) {
    this->data[X] += v.data[X];
    this->data[Y] += v.data[Y];
    return *this;
}

template <typename Real>
Vector2<Real>& Vector2<Real>::operator -= (const Vector2<Real>& v) {
    this->data[X] -= v.data[X];
    this->data[Y] -= v.data[Y];
    return *this;
}

template <typename Real>
Vector2<Real>& Vector2<Real>::operator *= (const Vector2<Real>& v) {
    this->data[X] *= v.data[X];
    this->data[Y] *= v.data[Y];
    return *this;
}

template <typename Real>
Vector2<Real>& Vector2<Real>::operator *= (Real scalar) {
    this->data[X] *= scalar;
    this->data[Y] *= scalar;
    return *this;
}

template <typename Real>
bool Vector2<Real>::operator == (const Vector2<Real>& v) const {
    if ( this->data[X] == v.data[X] && 
         this->data[Y] == v.data[Y] ) return true;
    return false;
}

template <typename Real>
bool Vector2<Real>::operator != (const Vector2<Real>& v) const {
    return !(*this == vector);
}
	
template <typename Real>
bool Vector2<Real>::operator < (const Vector2<Real>& v) {
    if ( this->norm() < v.norm() ) return true;
    return false;
}

template <typename Real>
bool Vector2<Real>::operator <= (const Vector2<Real>& v) {
    if ( this->norm() <= v.norm() ) return true;
    return false;
}

template <typename Real>
bool Vector2<Real>::operator > (const Vector2<Real>& v) {
    if ( this->norm() > v.norm() ) return true;
    return false;
}

template <typename Real>
bool Vector2<Real>::operator >= (const Vector2<Real>& v) {
    if ( this->norm() >= v.norm() ) return true;
    return false;
}

template <typename Real>
Vector2<Real> Vector2<Real>::Add(const Vector2<Real>& u, const Vector2<Real>& v) {
    Vector2<Real> result;
    result.data[X] = u.data[X] + v.data[X];
    result.data[Y] = u.data[Y] + v.data[Y];
    return result;
}

template <typename Real>
Vector2<Real> Vector2<Real>::Subtract(const Vector2<Real>& u, const Vector2<Real>& v) {
    Vector2<Real> result;
    result.data[X] = u.data[X] - v.data[X];
    result.data[Y] = u.data[Y] - v.data[Y];
    return result;
}

template <typename Real>
Vector2<Real> Vector2<Real>::Multiply(Real scalar, const Vector2<Real>& v) {
    Vector2<Real> result;
    result.data[X] = scalar * v.data[X];
    result.data[Y] = scalar * v.data[Y];
    return result;
}

template <typename Real>
Vector2<Real> Vector2<Real>::Normalize(const Vector2<Real>& v) {
    Vector2<Real> result;
    double invLen = 1.0 / static_cast<double>(v.length());
    result.data[X] = v.data[X] * Real(invLen);
	result.data[Y] = v.data[Y] * Real(invLen);
    return result;
}

template <typename Real>
Vector2<Real> Vector2<Real>::LinearInterpolation(const Vector2<Real>& u, const Vector2<Real>& v, Real t) {
    return (a * t) + b * (Real(1) - t);
}

template <typename Real>
Vector2<Real> Vector2<Real>::Project(const Vector2<Real>& u, const Vector2<Real>& v) {
    Vector2<Real> uNormalized = u.normalized();
    Vector2<Real> vNormalized = v.normalized();
    Real dot = u.dot(v);
    Real mag = dot * v.norm();
    return (v * mag);
}

template <typename Real>
double Vector2<Real>::Angle(const Vector2<Real>& u, const Vector2<Real>& v) {
    return std::acos((this->data[X] * vector.data[X] + this->data[Y] * vector.data[Y]) / (this->norm() * vector.norm()));
}

template <typename Real>
double Vector2<Real>::Dot(const Vector2<Real>& u, const Vector2<Real>& v) {
    return u.data[X] * v.data[X] + u.data[Y] * v.data[Y];
}

template <typename Real>
double Vector2<Real>::Magnitude(const Vector2<Real>& v) {
    return std::sqrt(Vector2<Real>::NormSquared(v));
}

template <typename Real>
double Vector2<Real>::Norm(const Vector2<Real>& v) {
    return std::sqrt(Vector2<Real>::NormSquared(v));
}

template <typename Real>
double Vector2<Real>::NormSquared(const Vector2<Real>& v) {
    return std::pow(v.data[X], Real(2)) + std::pow(v.data[Y], Real(2));
}

template <typename Real>
double Vector2<Real>::Length(const Vector2<Real>& v) {
    return std::sqrt(Vector2<Real>::LengthSquared(v));
}

template <typename Real>
double Vector2<Real>::LengthSquared(const Vector2<Real>& v) {
    return std::pow(v.data[X], Real(2)) + std::pow(v.data[Y], Real(2));
}

template <typename Real>
double Vector2<Real>::Distance(const Vector2<Real>& u, const Vector2<Real>& v) {
    return std::sqrt(Vector2<Real>::DistanceSquared(u, v));
}

template <typename Real>
double Vector2<Real>::DistanceSquared(const Vector2<Real>& u, const Vector2<Real>& v) {
    return std::pow(u.data[X] - v.data[X], Real(2)) + std::pow(u.data[Y] - v.data[Y], Real(2));
}

template <typename Real>
Vector2<Real> Vector2<Real>::Zero() {
    return Vector2<Real>();
}

template <typename Real>
Vector2<Real> Vector2<Real>::UnitX() {
    return Vector2<Real>(Real(1), Real(0));
}

template <typename Real>
Vector2<Real> Vector2<Real>::UnitY() {
    return Vector2<Real>(Real(0), Real(1));
}

template <typename Real>
Vector2<Real> Vector2<Real>::UnitNX() {
    return Vector2<Real>(Real(-1), Real(0));
}

template <typename Real>
Vector2<Real> Vector2<Real>::UnitNY() {
    return Vector2<Real>(Real(0), Real(-1));
}

typedef Vector2<long double> Vector2ld;
typedef Vector2<double> Vector2d;
typedef Vector2<float> Vector2f;
typedef Vector2<long> Vector2l;
typedef Vector2<int> Vector2i;
typedef Vector2<short> Vector2s;
typedef Vector2<long double> Vec2ld;
typedef Vector2<double> Vec2d;
typedef Vector2<float> Vec2f;
typedef Vector2<long> Vec2l;
typedef Vector2<int> Vec2i;
typedef Vector2<short> Vec2s;

typedef Vector2<float> Vec2;

#endif
