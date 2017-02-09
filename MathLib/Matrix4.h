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
#ifndef MATRIX_4_H
#define MATRIX_4_H

#include <iostream>
#include <cmath>
#include <type_traits>

#include "Matrix3.h"
#include "Vector3.h"
#include "Vector4.h"

template <typename Real>
class Matrix4;

template <typename Real>
std::ostream& operator << <> (std::ostream& out, const Matrix4<Real>& m);

/* 
 * Matrix4: Representation of any numerical 4x4 matrix.
 *
 * [a11 a12 a13 a14]
 * [a21 a22 a23 a24]
 * [a31 a32 a33 a34]
 * [a41 a42 a43 a44]
 * 
 * This implementation also foregoes vectorization (SSE).
 * This implementation is aimed at a flexibility while preserving 
 * understandability and complete modularity.
 */
template <typename Real>
class Matrix4 {
    static_assert(std::is_integral<Real>::value || std::is_floating_point<Real>::value, 
    "[Matrix4:Type] Error: Matrix4 Real type must be an integral or floating point numerical representation.");

    enum Element { A_11, A_21, A_31, A_41, 
                   A_12, A_22, A_32, A_42,
                   A_13, A_23, A_33, A_43,
                   A_14, A_24, A_34, A_44,
                   COMPONENT_COUNT };
public:
    Matrix4(bool identity = true);
    Matrix4(const Real* const data);
    Matrix4(const Matrix3<Real>& m, bool homogeneous = true);
    Matrix4(const Matrix4<Real>& m);
    Matrix4(Real a11, Real a12, Real a13, Real a14,
            Real a21, Real a22, Real a23, Real a24,
            Real a31, Real a32, Real a33, Real a34,
            Real a41, Real a42, Real a43, Real a44, bool colMajor = true);
    ~Matrix4();

    void set(const Matrix3<Real>& m, bool homogeneous = true);
    void set(const Matrix4<Real>& m);
    void set(const Real* const data);
    void set(std::size_t i, std::size_t j, Real value);
    void set(Real a11, Real a12, Real a13, Real a14,
             Real a21, Real a22, Real a23, Real a24,
             Real a31, Real a32, Real a33, Real a34,
             Real a41, Real a42, Real a43, Real a44, bool colMajor = true);

    void setRow(std::size_t i, Real w, Real x, Real y, Real z);
    void setRow(std::size_t i, const Vector4<Real>& row);
    void setColumn(std::size_t i, Real w, Real x, Real y, Real z);
    void setColumn(std::size_t i, const Vector4<Real>& column);

    bool isZero(Real epsilon);
    bool isIdentity(Real epsilon);
    bool isEquivalent(const Matrix4<Real>& m, Real epsilon);

    void zero();
    void transpose();
    void identity();

    void invert();

    void clear(bool identity = true);
    void toRawMatrix(Real* const matrix, bool colMajor = true) const;
    void getData(Real* const matrix, bool colMajor = true) const;

    Real determinant() const;
    Matrix4<Real> inverse() const;
    Matrix4<Real> inversed() const;
    Matrix4<Real> transposed() const;

    template <typename RealCastType>
    Matrix4<RealCastType> cast();

    Real& get(std::size_t i, std::size_t j);
    const Real& get(std::size_t i, std::size_t j) const;
    Vector4<Real> getRow(std::size_t i) const;
    Vector4<Real> getColumn(std::size_t i) const;

    Matrix4<Real> toTranspose() const;
    Matrix4<Real> toInverse() const;
    Matrix4<Real> apply(const Vector3<Real>& v, bool colMajor = true) const;
    Matrix4<Real> apply(const Vector4<Real>& v, bool colMajor = true) const;
    Vector3<Real> applyTo(const Vector3<Real>& v) const;
	Vector4<Real> applyTo(const Vector4<Real>& v) const;

    const Real* const constData() const;
    operator const Real* const () const;

    void set(unsigned int index, Real value) {
        this->data[index] = value;
    }

    Real get(unsigned int index) {
        return this->data[index];
    }

    Real& operator () (std::size_t i, std::size_t j);
    const Real& operator () (std::size_t i, std::size_t j) const;

    friend std::ostream& operator << <> (std::ostream& out, const Matrix4<Real>& m);

    bool operator == (const Matrix4<Real>& m);
	bool operator != (const Matrix4<Real>& m);

    Matrix4<Real>& operator = (const Matrix4<Real>& m);
	Matrix4<Real>& operator = (const Real* data);

    Vector3<Real> operator * (const Vector3<Real>& v);
	Matrix4<Real> operator * (const Matrix4<Real>& m);
    Matrix4<Real>& operator *= (const Matrix4<Real>& m);

    static void ToRawMatrix(const Matrix4<Real>& m, Real* const matrix, bool colMajor = true);
    static void Clear(Matrix4<Real>& m);
    static void Identity(Matrix4<Real>& m);
    static void Zero(Matrix4<Real>& m);
    static Real Determinant(const Matrix4<Real>& m);
    static Real Determinant(const Matrix4<Real>& matrix, Real* const adjoint);
    static Matrix4<Real> Multiply(const Matrix4<Real>& a, const Matrix4<Real>& b);
    static Matrix4<Real> Transpose(const Matrix4<Real>& m);
    static Matrix4<Real> Inverse(const Matrix4<Real>& m);
    static Matrix4<Real> LookAt(const Vector3<Real>& eye, const Vector3<Real>& lookat, const Vector3<Real>& up);
    static Matrix4<Real> LookAt(Real eyex, Real eyey, Real eyez, Real atx, Real aty, Real atz, Real upx, Real upy, Real upz);
    static Matrix3<Real> NormalMatrix(const Matrix4<Real>& modelViewMatrix);

    static Matrix4<Real> Zero();
    static Matrix4<Real> Identity();

protected:
	const static int ROW_COUNT = 4;
	const static int COL_COUNT = 4;

    Real data[COMPONENT_COUNT];
};

template <typename Real>
Matrix4<Real>::Matrix4(bool identity) {
    std::memset(this->data, 0, COMPONENT_COUNT * sizeof(Real));

    if ( identity ) {
        this->data[A_11] = Real(1);
        this->data[A_22] = Real(1);
        this->data[A_33] = Real(1);
        this->data[A_44] = Real(1);
    }
}

template <typename Real>
Matrix4<Real>::Matrix4(const Real* const data) {
    std::memcpy(this->data, data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
Matrix4<Real>::Matrix4(const Matrix3<Real>& m, bool homogeneous) {
    this->set(m, homogeneous);
}

template <typename Real>
Matrix4<Real>::Matrix4(const Matrix4<Real>& m) {
    std::memcpy(this->data, m.data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
Matrix4<Real>::Matrix4(Real a11, Real a12, Real a13, Real a14,
                       Real a21, Real a22, Real a23, Real a24,
                       Real a31, Real a32, Real a33, Real a34,
                       Real a41, Real a42, Real a43, Real a44, bool colMajor) {
    this->set(
        a11, a12, a13, a14, 
        a21, a22, a23, a24, 
        a31, a32, a33, a34, 
        a41, a42, a43, a44, 
        colMajor
    );
}

template <typename Real>
Matrix4<Real>::~Matrix4() {}

template <typename Real>
void Matrix4<Real>::set(const Matrix3<Real>& m, bool homogeneous) {
    std::memset(this->data, 0, COMPONENT_COUNT * sizeof(Real));

    if ( homogeneous ) this->data[A_44] = Real(1);

    (*this)(0, 0) = m(0, 0);
    (*this)(0, 1) = m(0, 1);
    (*this)(0, 2) = m(0, 2);

    (*this)(1, 0) = m(1, 0);
    (*this)(1, 1) = m(1, 1);
    (*this)(1, 2) = m(1, 2);

    (*this)(2, 0) = m(2, 0);
    (*this)(2, 1) = m(2, 1);
    (*this)(2, 2) = m(2, 2);
}

template <typename Real>
void Matrix4<Real>::set(const Matrix4<Real>& m) {
    std::memcpy(this->data, m.data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix4<Real>::set(const Real* const data) {
    std::memcpy(this->data, data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix4<Real>::set(std::size_t i, std::size_t j, Real value) {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix4:set] Index i out of bounds.");
	if ( j >= COL_COUNT ) throw std::exception("[Matrix4:set] Index j out of bounds.");

    this->data[i * ROW_COUNT + j] = value;
}

template <typename Real>
void Matrix4<Real>::set(Real a11, Real a12, Real a13, Real a14,
                        Real a21, Real a22, Real a23, Real a24,
                        Real a31, Real a32, Real a33, Real a34,
                        Real a41, Real a42, Real a43, Real a44, bool colMajor) {
    this->data[A_11] = a11;
    this->data[A_22] = a22;
    this->data[A_33] = a33;
    this->data[A_44] = a44;

    if ( colMajor == true ) {
        this->data[A_21] = a12;
        this->data[A_31] = a13;
        this->data[A_41] = a14;
        this->data[A_12] = a21;
        this->data[A_32] = a23;
        this->data[A_42] = a24;
        this->data[A_13] = a31;
        this->data[A_23] = a32;
        this->data[A_43] = a34;
        this->data[A_14] = a41;
        this->data[A_24] = a42;
        this->data[A_34] = a43;
    }
    else {
        this->data[A_12] = a12;
        this->data[A_13] = a13;
        this->data[A_14] = a14;
        this->data[A_21] = a21;
        this->data[A_23] = a23;
        this->data[A_24] = a24;
        this->data[A_31] = a31;
        this->data[A_32] = a32;
        this->data[A_34] = a34;
        this->data[A_41] = a41;
        this->data[A_42] = a42;
        this->data[A_43] = a43;
    }
}

template <typename Real>
void Matrix4<Real>::setRow(std::size_t i, Real w, Real x, Real y, Real z) {
    if ( i >= COL_COUNT ) throw std::exception("[Matrix4:getColumn] Error: Column index out of bounds.");

    if ( i == 0 ) {
        this->data[A_11] = w;
        this->data[A_21] = x;
        this->data[A_31] = y;
        this->data[A_41] = z;
    }

    if ( i == 1 ) {
        this->data[A_12] = w;
        this->data[A_22] = x;
        this->data[A_32] = y;
        this->data[A_42] = z;
    }

    if ( i == 2 ) {
        this->data[A_13] = w;
        this->data[A_23] = x;
        this->data[A_33] = y;
        this->data[A_43] = z;
    }

    if ( i == 3 ) {
        this->data[A_14] = w;
        this->data[A_24] = x;
        this->data[A_34] = y;
        this->data[A_44] = z;
    }
}

template <typename Real>
void Matrix4<Real>::setRow(std::size_t i, const Vector4<Real>& row) {
    this->setRow(i, row.w(), row.x(), row.y(), row.z());
}

template <typename Real>
void Matrix4<Real>::setColumn(std::size_t i, Real w, Real x, Real y, Real z) {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix4:setRow] Error: Row index out of bounds.");

    if ( i == 0 ) {
        this->data[A_11] = w;
        this->data[A_12] = x;
        this->data[A_13] = y;
        this->data[A_14] = z;
    }

    if ( i == 1 ) {
        this->data[A_21] = w;
        this->data[A_22] = x;
        this->data[A_23] = y;
        this->data[A_24] = z;
    }

    if ( i == 2 ) {
        this->data[A_31] = w;
        this->data[A_32] = x;
        this->data[A_33] = y;
        this->data[A_34] = z;
    }

    if ( i == 3 ) {
        this->data[A_41] = w;
        this->data[A_42] = x;
        this->data[A_43] = y;
        this->data[A_44] = z;
    }
}

template <typename Real>
void Matrix4<Real>::setColumn(std::size_t i, const Vector4<Real>& column) {
    this->setColumn(i, column.w(), column.x(), column.y(), column.z());
}

template <typename Real>
bool Matrix4<Real>::isZero(Real epsilon) {
    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ ) {
        Real value = this->data[i];

        if ( value < -epsilon || value > epsilon ) return false;
    }

    return true;
}

template <typename Real>
bool Matrix4<Real>::isIdentity(Real epsilon) {
    if ( this->data[A_11] < Real(1) - epsilon || this->data[A_11] > Real(1) + epsilon ) return false;
    if ( this->data[A_22] < Real(1) - epsilon || this->data[A_22] > Real(1) + epsilon ) return false;
    if ( this->data[A_33] < Real(1) - epsilon || this->data[A_33] > Real(1) + epsilon ) return false;
    if ( this->data[A_44] < Real(1) - epsilon || this->data[A_44] > Real(1) + epsilon ) return false;

    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ ) {
        if ( i == A_11 || i == A_22 || i == A_33 || i == A_44 ) continue;
        Real value = this->data[i];

        if ( value < -epsilon || value > epsilon ) return false;
    }

    return true;
}

/*
 * Will test the this matrix against the provided matrix to see if they are
 * numerically 'equivalent' based on the provided epsilon value. This function
 * will provide a notice if this matrix is not equivalent, but its transpose is.
 */
template <typename Real>
bool Matrix4<Real>::isEquivalent(const Matrix4<Real>& m, Real epsilon) {
    bool bCur = true;
    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ )
        if ( this->data[i] < (m.data[i] - epsilon) || this->data[i] > (m.data[i] + epsilon) ) bCur = false;

    if ( bCur == false ) {
        Matrix4<Real> transpos = m.toTranspose();
        bool bTrans = true;

        for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ )
            if ( this->data[i] < (transpos.data[i] - epsilon) || this->data[i] > (transpos.data[i] + epsilon) ) bTrans = false;

        if ( bTrans ) {
            std::cerr << "[Matrix4:isEquivalent] Notice: The provided matrix is not equivalent, but the transpose is equivalent to this matrix." << std::endl;
            return false;
        }

        return false;
    }

    return true;
}

template <typename Real>
void Matrix4<Real>::zero() {
    std::memset(this->data, 0, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix4<Real>::transpose() {
    std::swap(this->data[A_12], this->data[A_21]);
    std::swap(this->data[A_13], this->data[A_31]);
    std::swap(this->data[A_14], this->data[A_41]);
    std::swap(this->data[A_23], this->data[A_32]);
    std::swap(this->data[A_24], this->data[A_42]);
    std::swap(this->data[A_34], this->data[A_43]);
}

template <typename Real>
void Matrix4<Real>::identity() {
    std::memset(this->data, 0, COMPONENT_COUNT * sizeof(Real));
    this->data[A_11] = Real(1);
    this->data[A_22] = Real(1);
    this->data[A_33] = Real(1);
    this->data[A_44] = Real(1);
}

template <typename Real>
void Matrix4<Real>::invert() {
    Matrix4<Real> inverse = Matrix4<Real>::Inverse(*this);
    std::memcpy(this->data, inverse.data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix4<Real>::clear(bool identity) {
    std::memset(this->data, 0, COMPONENT_COUNT * sizeof(Real));

    if ( identity ) {
        this->data[A_11] = Real(1);
        this->data[A_22] = Real(1);
        this->data[A_33] = Real(1);
    }
}

template <typename Real>
void Matrix4<Real>::toRawMatrix(Real* const matrix, bool colMajor) const {
    if ( nullptr == matrix ) return;
    Matrix4<Real> result = (*this);
    if ( colMajor == false ) result.transpose();
    std::memcpy(matrix, result.data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix4<Real>::getData(Real* const matrix, bool colMajor) const {
    this->toRawMatrix(matrix, colMajor);
}

template <typename Real>
Real Matrix4<Real>::determinant() const {
    return Matrix4<Real>::Determinant(*this);
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::inverse() const {
    return Matrix4<Real>::Inverse(*this);
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::inversed() const {
    return Matrix4<Real>::Inverse(*this);
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::transposed() const {
    return Matrix4<Real>::Transpose(*this);
}

template <typename Real>
template <typename RealCastType>
Matrix4<RealCastType> Matrix4<Real>::cast() {
    Matrix4<RealCastType> result;
    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ )
        result.data[i] = static_cast<RealCastType>(this->data[i]);
    return result;
}


template <typename Real>
Real& Matrix4<Real>::get(std::size_t i, std::size_t j) {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix4:get] Index i out of bounds.");
	if ( j >= COL_COUNT ) throw std::exception("[Matrix4:get] Index j out of bounds.");

    return this->data[i * ROW_SIZE + j];
}

template <typename Real>
const Real& Matrix4<Real>::get(std::size_t i, std::size_t j) const {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix4:get] Index i out of bounds.");
	if ( j >= COL_COUNT ) throw std::exception("[Matrix4:get] Index j out of bounds.");

    return this->data[i * ROW_SIZE + j];
}

template <typename Real>
Vector4<Real> Matrix4<Real>::getColumn(std::size_t i) const {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix4:getRow] Error: Row index out of bounds.");
    if ( i == 0 ) return Vector4<Real>(this->data[A_14], this->data[A_11], this->data[A_12], this->data[A_13]);
    if ( i == 1 ) return Vector4<Real>(this->data[A_24], this->data[A_21], this->data[A_22], this->data[A_23]);
    if ( i == 2 ) return Vector4<Real>(this->data[A_34], this->data[A_31], this->data[A_32], this->data[A_33]);
    if ( i == 3 ) return Vector4<Real>(this->data[A_44], this->data[A_41], this->data[A_42], this->data[A_43]);
    return Vector4<Real>::Zero()
}

template <typename Real>
Vector4<Real> Matrix4<Real>::getRow(std::size_t i) const {
    if ( i >= COL_COUNT ) throw std::exception("[Matrix4:getColumn] Error: Column index out of bounds.");
    if ( i == 0 ) return Vector4<Real>(this->data[A_41], this->data[A_11], this->data[A_21], this->data[A_31]);
    if ( i == 1 ) return Vector4<Real>(this->data[A_42], this->data[A_12], this->data[A_22], this->data[A_32]);
    if ( i == 2 ) return Vector4<Real>(this->data[A_43], this->data[A_13], this->data[A_23], this->data[A_33]);
    if ( i == 3 ) return Vector4<Real>(this->data[A_44], this->data[A_14], this->data[A_24], this->data[A_34]);
    return Vector4<Real>::Zero();
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::toTranspose() const {
    Matrix4<Real> result = (*this);
    return Matrix4<Real>::Transpose(result);
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::toInverse() const {
    Matrix4<Real> result = (*this);
    return Matrix4<Real>::Inverse(result);
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::apply(const Vector3<Real>& v, bool colMajor) const {
    Matrix4<Real> m = (*this).transposed();
    m.setRow(0, m.data[A_11] * v.x(), m.data[A_12] * v.x(), m.data[A_13] * v.x(), m.data[A_14] * v.x());
    m.setRow(1, m.data[A_21] * v.y(), m.data[A_22] * v.y(), m.data[A_23] * v.y(), m.data[A_24] * v.y());
    m.setRow(2, m.data[A_31] * v.z(), m.data[A_32] * v.z(), m.data[A_33] * v.z(), m.data[A_34] * v.z());

    if ( colMajor ) m.transpose();
    return m;
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::apply(const Vector4<Real>& v, bool colMajor) const {
    Matrix4<Real> m = (*this).transposed();
    m.setRow(0, m.data[A_11] * v.w(), m.data[A_12] * v.w(), m.data[A_13] * v.w(), m.data[A_14] * v.w());
    m.setRow(1, m.data[A_21] * v.x(), m.data[A_22] * v.x(), m.data[A_23] * v.x(), m.data[A_24] * v.x());
    m.setRow(2, m.data[A_31] * v.y(), m.data[A_32] * v.y(), m.data[A_33] * v.y(), m.data[A_34] * v.y());
    m.setRow(3, m.data[A_41] * v.z(), m.data[A_42] * v.z(), m.data[A_43] * v.z(), m.data[A_44] * v.z());

    if ( colMajor ) m.transpose();
    return m;
}

template <typename Real>
Vector3<Real> Matrix4<Real>::applyTo(const Vector3<Real>& v) const {
    Vector4<Real> result;
    result.x() = this->data[A_21] * v.w() + this->data[A_22] * v.x() + this->data[A_23] * v.y() + this->data[A_24] * v.z();
    result.y() = this->data[A_31] * v.w() + this->data[A_32] * v.x() + this->data[A_33] * v.y() + this->data[A_34] * v.z();
    result.z() = this->data[A_41] * v.w() + this->data[A_42] * v.x() + this->data[A_43] * v.y() + this->data[A_44] * v.z();
    return Vector3<Real>(result.x(), result.y(), result.z());
}

template <typename Real>
Vector4<Real> Matrix4<Real>::applyTo(const Vector4<Real>& v) const {
    Vector4<Real> result;
    result.w() = this->data[A_11] * v.w() + this->data[A_12] * v.x() + this->data[A_13] * v.y() + this->data[A_14] * v.z();
    result.x() = this->data[A_21] * v.w() + this->data[A_22] * v.x() + this->data[A_23] * v.y() + this->data[A_24] * v.z();
    result.y() = this->data[A_31] * v.w() + this->data[A_32] * v.x() + this->data[A_33] * v.y() + this->data[A_34] * v.z();
    result.z() = this->data[A_41] * v.w() + this->data[A_42] * v.x() + this->data[A_43] * v.y() + this->data[A_44] * v.z();
    return result;
}

template <typename Real>
const Real* const Matrix4<Real>::constData() const {
    return this->data;
}

template <typename Real>
Matrix4<Real>::operator const Real* const () const {
    return this->data;
}

template <typename Real>
Real& Matrix4<Real>::operator () (std::size_t i, std::size_t j) {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix4:()] Index i out of bounds.");
	if ( j >= COL_COUNT ) throw std::exception("[Matrix4:()] Index j out of bounds.");

    return this->data[i * ROW_COUNT + j];
}

template <typename Real>
const Real& Matrix4<Real>::operator () (std::size_t i, std::size_t j) const {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix4:()] Index i out of bounds.");
	if ( j >= COL_COUNT ) throw std::exception("[Matrix4:()] Index j out of bounds.");

    return this->data[i * ROW_COUNT + j];
}

template <typename Real>
std::ostream& operator << (std::ostream& out, const Matrix4<Real>& m) {
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "[" << m(0, 0) << "\t" << m(0, 1) << "\t" << m(0, 2) << "\t" << m(0, 3) << "]" << std::endl;
    std::cout << "[" << m(1, 0) << "\t" << m(1, 1) << "\t" << m(1, 2) << "\t" << m(1, 3) << "]" << std::endl;
    std::cout << "[" << m(2, 0) << "\t" << m(2, 1) << "\t" << m(2, 2) << "\t" << m(2, 3) << "]" << std::endl;
    std::cout << "[" << m(3, 0) << "\t" << m(3, 1) << "\t" << m(3, 2) << "\t" << m(3, 3) << "]" << std::endl;
    return out;
}

template <typename Real>
bool Matrix4<Real>::operator == (const Matrix4<Real>& m) {
    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ )
        if ( this->data[i] != m.data[i] ) return false;
    return true;
}

template <typename Real>
bool Matrix4<Real>::operator != (const Matrix4<Real>& m) {
    return !(*this == m);
}

template <typename Real>
Matrix4<Real>& Matrix4<Real>::operator = (const Matrix4<Real>& m) {
    if ( this == &m ) return *this;
    std::memcpy(this->data, m.data, COMPONENT_COUNT * sizeof(Real));
    return *this;
}

template <typename Real>
Matrix4<Real>& Matrix4<Real>::operator = (const Real* data) {
    if ( nullptr == data ) return *this;
    std::memcpy(this->data, data, COMPONENT_COUNT * sizeof(Real));
    return *this;
}

template <typename Real>
Vector3<Real> Matrix4<Real>::operator * (const Vector3<Real>& v) {
    return this->applyTo(v);
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::operator * (const Matrix4<Real>& m) {
    Matrix4<Real> t = (*this);
    return Matrix4<Real>::Multiply(t, m);
}

template <typename Real>
Matrix4<Real>& Matrix4<Real>::operator *= (const Matrix4<Real>& m) {
    Matrix4<Real> result = Matrix4<Real>::Multiply(*this, m);
    std::memcpy(this->data, result.data, COMPONENT_COUNT * sizeof(Real));
    return *this;
}

template <typename Real>
void Matrix4<Real>::ToRawMatrix(const Matrix4<Real>& m, Real* const matrix, bool colMajor) {
    if ( nullptr == matrix ) {
        std::cerr << "[Matrix4:ToRawMatrix] Error: Nullptr matrix." << std::endl;
        return;
    }

    Matrix4<Real> result = m;
    if ( colMajor == false ) result.transpose();
    std::memcpy(matrix, result.data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix4<Real>::Clear(Matrix4<Real>& m) {
    std::memset(m.data, 0, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix4<Real>::Identity(Matrix4<Real>& m) {
    std::memset(m.data, 0, COMPONENT_COUNT * sizeof(Real));
    m.data[A_11] = Real(1);
    m.data[A_22] = Real(1);
    m.data[A_33] = Real(1);
    m.data[A_44] = Real(1);
}

template <typename Real>
void Matrix4<Real>::Zero(Matrix4<Real>& m) {
    std::memset(m.data, 0, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
Real Matrix4<Real>::Determinant(const Matrix4<Real>& matrix) {
    Real adjoint[COMPONENT_COUNT];
    return Matrix4<Real>::Determinant(matrix, adjoint);
}

/* Loop-unroll determinant */
template <typename Real>
Real Matrix4<Real>::Determinant(const Matrix4<Real>& matrix, Real* const adjoint) {
    Real m[COMPONENT_COUNT];
    std::memcpy(m, matrix.data, COMPONENT_COUNT * sizeof(Real));

    adjoint[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    adjoint[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    adjoint[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    adjoint[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    adjoint[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    adjoint[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    adjoint[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    adjoint[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    adjoint[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    adjoint[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    adjoint[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    adjoint[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    adjoint[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    adjoint[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    adjoint[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    adjoint[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    return m[0] * adjoint[0] + m[1] * adjoint[4] + m[2] * adjoint[8] + m[3] * adjoint[12];
}

/* Memory friendly matrix multiplication (Gita A., Lan V.) */
template <typename Real>
Matrix4<Real> Matrix4<Real>::Multiply(const Matrix4<Real>& a, const Matrix4<Real>& b) {
    Matrix4<Real> result(false);
    for ( unsigned int i = 0; i < ROW_COUNT; i++ )
		for ( unsigned int j = 0; j < ROW_COUNT; j++ )
			for ( unsigned int k = 0; k < ROW_COUNT; k++ )
				result(i, j) += a(i, k) * b(k, j);

    //for ( unsigned int i = 0; i < ROW_COUNT; i++ )
   //     for ( unsigned int k = 0; k < ROW_COUNT; k++ )
   //         for ( unsigned int j = 0; j < ROW_COUNT; j++ )
    //            result(i, j) += a(i, k) * b(k, j);

    return result;
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::Transpose(const Matrix4<Real>& m) {
    Matrix4<Real> result = m;
    std::swap(result.data[A_12], result.data[A_21]);
    std::swap(result.data[A_13], result.data[A_31]);
    std::swap(result.data[A_14], result.data[A_41]);
    std::swap(result.data[A_23], result.data[A_32]);
    std::swap(result.data[A_24], result.data[A_42]);
    std::swap(result.data[A_34], result.data[A_43]);
    return result;
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::Inverse(const Matrix4<Real>& matrix) {
    Real m[COMPONENT_COUNT];
    Real adjoint[COMPONENT_COUNT];

    std::memcpy(m, matrix.data, COMPONENT_COUNT * sizeof(Real));
    std::memset(adjoint, 0, COMPONENT_COUNT * sizeof(Real));
	
    Real det = Matrix4<Real>::Determinant(matrix, adjoint);
    if ( det == Real(0) ) return Matrix4<Real>(true);
    Real invDet = Real(1) / det;

    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ ) adjoint[i] = adjoint[i] * invDet;
    return Matrix4<Real>(adjoint);
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::LookAt(const Vector3<Real>& eye, const Vector3<Real>& lookAt, const Vector3<Real>& up) {
    return Matrix4<Real>::LookAt(eye.x(), eye.y(), eye.z(), lookAt.x(), lookAt.y(), lookAt.z(), up.x(), up.y(), up.z());
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::LookAt(Real eyex, Real eyey, Real eyez, Real atx, Real aty, Real atz, Real upx, Real upy, Real upz) {
    Vector3<Real> eye(eyex, eyey, eyez);
    Vector3<Real> lookAt(atx, aty, atz);
    Vector3<Real> up(upx, upy, upz);

    if ( lookAt - eye == Vector3<Real>::Zero() ) return Matrix4<Real>::Identity();
    if ( up - eye == Vector3<Real>::Zero() ) return Matrix4<Real>::Identity();

    Vector3<Real> zAxis = Vector3<Real>::Normalize(lookAt - eye);
    Vector3<Real> xAxis = Vector3<Real>::Normalize(Vector3<Real>::Cross(zAxis, up));
    Vector3<Real> yAxis = Vector3<Real>::Normalize(Vector3<Real>::Cross(xAxis, zAxis));
    Matrix4<Real> matrix;

    matrix(0, 0) = xAxis.x();
    matrix(1, 0) = xAxis.y();
    matrix(2, 0) = xAxis.z();
    matrix(3, 0) = static_cast<Real>(-Vector3<Real>::Dot(xAxis, eye));

    matrix(0, 1) = yAxis.x();
    matrix(1, 1) = yAxis.y();
    matrix(2, 1) = yAxis.z();
    matrix(3, 1) = static_cast<Real>(-Vector3<Real>::Dot(yAxis, eye));

    matrix(0, 2) = -zAxis.x();
    matrix(1, 2) = -zAxis.y();
    matrix(2, 2) = -zAxis.z();
    matrix(3, 2) = static_cast<Real>(Vector3<Real>::Dot(zAxis, eye));

    matrix(0, 3) = Real(0);
    matrix(1, 3) = Real(0);
    matrix(2, 3) = Real(0);
    matrix(3, 3) = Real(1);

    return matrix;
}

template <typename Real>
Matrix3<Real> Matrix4<Real>::NormalMatrix(const Matrix4<Real>& modelViewMatrix) {
    Matrix3f normalMatrix;

    Vector4f mvRow1 = modelViewMatrix.getRow(0);
    Vector4f mvRow2 = modelViewMatrix.getRow(1);
    Vector4f mvRow3 = modelViewMatrix.getRow(2);

    Vector3f normalMatrixRow1(mvRow1.x(), mvRow1.y(), mvRow1.z());
    Vector3f normalMatrixRow2(mvRow2.x(), mvRow2.y(), mvRow2.z());
    Vector3f normalMatrixRow3(mvRow3.x(), mvRow3.y(), mvRow3.z());
    
    normalMatrix.setRow(0, normalMatrixRow1);
    normalMatrix.setRow(1, normalMatrixRow2);
    normalMatrix.setRow(2, normalMatrixRow3);

    return normalMatrix;
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::Zero() {
    return Matrix4<Real>(false);
}

template <typename Real>
Matrix4<Real> Matrix4<Real>::Identity() {
    return Matrix4<Real>(true);
}

typedef Matrix4<float> Matrix4f;
typedef Matrix4<double> Matrix4d;
typedef Matrix4<long> Matrix4l;
typedef Matrix4<int> Matrix4i;
typedef Matrix4<short> Matrix4s;
typedef Matrix4<float> Mat4f;
typedef Matrix4<double> Mat4d;
typedef Matrix4<long> Mat4l;
typedef Matrix4<int> Mat4i;
typedef Matrix4<short> Mat4s;

typedef Matrix4<float> Mat4;

#endif
