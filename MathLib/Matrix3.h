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
#ifndef MATRIX_3_H
#define MATRIX_3_H

#include <iostream>
#include <cmath>
#include <cstring>
#include <type_traits>
#include <iomanip>

#include "Vector3.h"
#include "Vector4.h"

template <typename Real>
class Matrix3;

template <typename Real>
std::ostream& operator << <> (std::ostream& out, const Matrix3<Real>& m);

/* 
 * Matrix3: Representation of any numerical 3x3 matrix.
 *
 * [a11 a12 a13]
 * [a21 a22 a23]
 * [a31 a32 a33]
 * 
 * This implementation also foregoes vectorization (SSE).
 * This implementation is aimed at a flexibility while preserving 
 * understandability and complete modularity.
 */
template <typename Real>
class Matrix3 {
    static_assert(std::is_integral<Real>::value || std::is_floating_point<Real>::value, 
    "[Matrix3:Type] Error: Matrix3 Real type must be an integral or floating point numerical representation.");

    /* 
     * The implementation is written for a row-major matrix, however the
     * memory mapping provided by this enum transposes the matrix to a
     * column major matrix representation in memory.
     */
    enum Element { A_11, A_21, A_31,
                   A_12, A_22, A_32,
                   A_13, A_23, A_33,
                   COMPONENT_COUNT };
public:
    Matrix3(bool identity = true);
    Matrix3(const Real* const data);
    Matrix3(const Matrix3<Real>& m);
    Matrix3(Real a11, Real a12, Real a13, 
            Real a21, Real a22, Real a23, 
            Real a31, Real a32, Real a33, bool colMajor = true);
    ~Matrix3();

    void set(const Matrix3<Real>& m);
    void set(const Real* const data);
    void set(std::size_t i, std::size_t j, Real value);
    void set(Real a11, Real a12, Real a13, 
             Real a21, Real a22, Real a23, 
             Real a31, Real a32, Real a33, bool colMajor = true);

    void setRow(std::size_t i, Real x, Real y, Real z);
    void setRow(std::size_t i, const Vector3<Real>& row);
    void setColumn(std::size_t i, Real x, Real y, Real z);
    void setColumn(std::size_t i, const Vector3<Real>& column);

    bool isZero(Real epsilon);
    bool isIdentity(Real epsilon);
    bool isEquivalent(const Matrix3<Real>& m, Real epsilon);

    void zero();
    void transpose();
    void identity();

    virtual void invert();

    void clear(bool identity = true);
    void toRawMatrix(Real* const matrix, bool colMajor = true) const;
    void getData(Real* const matrix, bool colMajor = true) const;
    
    Real determinant() const;
    Matrix3<Real> inverse() const;
    Matrix3<Real> inversed() const;
    Matrix3<Real> transposed() const;

    template <typename RealCastType>
    Matrix3<RealCastType> cast();

    Real& get(std::size_t i, std::size_t j);
    const Real& get(std::size_t i, std::size_t j) const;
    Vector3<Real> getRow(std::size_t i) const;
    Vector3<Real> getColumn(std::size_t i) const;

    Matrix3<Real> toTranspose() const;
    Matrix3<Real> toInverse() const;
    Matrix3<Real> apply(const Vector3<Real>& v, bool colMajor = true) const;
    Vector3<Real> applyTo(const Vector3<Real>& v) const;
	Vector4<Real> applyTo(const Vector4<Real>& v) const;

    const Real* const constData() const;
    operator const Real* const () const;

    Real& operator () (std::size_t i, std::size_t j);
    const Real& operator () (std::size_t i, std::size_t j) const;

    void set(unsigned int index, Real value);
    Real get(unsigned int index);

    friend std::ostream& operator << <> (std::ostream& out, const Matrix3<Real>& m);

    bool operator == (const Matrix3<Real>& m);
	bool operator != (const Matrix3<Real>& m);

    Matrix3<Real>& operator = (const Matrix3<Real>& m);
	Matrix3<Real>& operator = (const Real* data);

    Vector3<Real> operator * (const Vector3<Real>& v);
	Matrix3<Real> operator * (const Matrix3<Real>& m);
    Matrix3<Real>& operator *= (const Matrix3<Real>& m);

    static void ToRawMatrix(const Matrix3<Real>& m, Real* const matrix, bool colMajor = true);
    static void Clear(Matrix3<Real>& m);
    static void Identity(Matrix3<Real>& m);
    static void Zero(Matrix3<Real>& m);
    static Real Determinant(const Matrix3<Real>& m);
    static Matrix3<Real> Multiply(const Matrix3<Real>& a, const Matrix3<Real>& b);
    static Matrix3<Real> Transpose(const Matrix3<Real>& m);
    static Matrix3<Real> Inverse(const Matrix3<Real>& m);

    static Matrix3<Real> Zero();
    static Matrix3<Real> Identity();

protected:
	const static int ROW_COUNT = 3;
	const static int COL_COUNT = 3;

    Real data[COMPONENT_COUNT];
};

template <typename Real>
Matrix3<Real>::Matrix3(bool identity) {
    std::memset(this->data, 0, COMPONENT_COUNT * sizeof(Real));

    if ( identity ) {
        this->data[A_11] = Real(1);
        this->data[A_22] = Real(1);
        this->data[A_33] = Real(1);
    }
}

template <typename Real>
Matrix3<Real>::Matrix3(const Real* const data) {
    std::memcpy(this->data, data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
Matrix3<Real>::Matrix3(const Matrix3<Real>& m) {
    std::memcpy(this->data, m.data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
Matrix3<Real>::Matrix3(Real a11, Real a12, Real a13, Real a21, Real a22, Real a23, Real a31, Real a32, Real a33, bool colMajor) {
    this->set(a11, a12, a13, a21, a22, a23, a31, a32, a33, colMajor);
}

template <typename Real>
Matrix3<Real>::~Matrix3() {}

template <typename Real>
void Matrix3<Real>::set(const Matrix3<Real>& m) {
    std::memcpy(this->data, m.data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix3<Real>::set(const Real* const data) {
    std::memcpy(this->data, data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix3<Real>::set(std::size_t i, std::size_t j, Real value) {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix3:set] Index i out of bounds.");
	if ( j >= COL_COUNT ) throw std::exception("[Matrix3:set] Index j out of bounds.");

    this->data[i * ROW_COUNT + j] = value;
}

template <typename Real>
void Matrix3<Real>::set(Real a11, Real a12, Real a13, Real a21, Real a22, Real a23, Real a31, Real a32, Real a33, bool colMajor) {
    this->data[A_11] = a11;
    this->data[A_22] = a22;
    this->data[A_33] = a33;

    if ( colMajor == true ) {
        this->data[A_21] = a12;
        this->data[A_31] = a13;
        this->data[A_12] = a21;
        this->data[A_32] = a23;
        this->data[A_13] = a31;
        this->data[A_23] = a32;
    }
    else {
        this->data[A_12] = a12;
        this->data[A_13] = a13;
        this->data[A_21] = a21;
        this->data[A_23] = a23;
        this->data[A_31] = a31;
        this->data[A_32] = a32;
    }
}

template <typename Real>
void Matrix3<Real>::setColumn(std::size_t i, Real x, Real y, Real z) {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix3:setRow] Error: Row index out of bounds.");

    if ( i == 0 ) {
        this->data[A_11] = x;
        this->data[A_12] = y;
        this->data[A_13] = z;
    }

    if ( i == 1 ) {
        this->data[A_21] = x;
        this->data[A_22] = y;
        this->data[A_23] = z;
    }

    if ( i == 2 ) {
        this->data[A_31] = x;
        this->data[A_32] = y;
        this->data[A_33] = z;
    }
}

template <typename Real>
void Matrix3<Real>::setRow(std::size_t i, const Vector3<Real>& row) {
    this->setRow(i, row.x(), row.y(), row.z());
}

template <typename Real>
void Matrix3<Real>::setRow(std::size_t i, Real x, Real y, Real z) {
    if ( i >= COL_COUNT ) throw std::exception("[Matrix3:getColumn] Error: Column index out of bounds.");

    if ( i == 0 ) {
        this->data[A_11] = x;
        this->data[A_21] = y;
        this->data[A_31] = z;
    }

    if ( i == 1 ) {
        this->data[A_12] = x;
        this->data[A_22] = y;
        this->data[A_32] = z;
    }

    if ( i == 2 ) {
        this->data[A_13] = x;
        this->data[A_23] = y;
        this->data[A_33] = z;
    }
}

template <typename Real>
void Matrix3<Real>::setColumn(std::size_t i, const Vector3<Real>& column) {
    this->setColumn(i, column.x(), column.y(), column.z());
}

template <typename Real>
bool Matrix3<Real>::isZero(Real epsilon) {
    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ ) {
        Real value = this->data[i];

        if ( value < -epsilon || value > epsilon ) return false;
    }

    return true;
}

template <typename Real>
bool Matrix3<Real>::isIdentity(Real epsilon) {
    if ( this->data[A_11] < Real(1) - epsilon || this->data[A_11] > Real(1) + epsilon ) return false;
    if ( this->data[A_22] < Real(1) - epsilon || this->data[A_22] > Real(1) + epsilon ) return false;
    if ( this->data[A_33] < Real(1) - epsilon || this->data[A_33] > Real(1) + epsilon ) return false;

    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ ) {
        if ( i == A_11 || i == A_22 || i == A_33 ) continue;
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
bool Matrix3<Real>::isEquivalent(const Matrix3<Real>& m, Real epsilon) {
    bool bCur = true;
    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ )
        if ( this->data[i] < (m.data[i] - epsilon) || this->data[i] > (m.data[i] + epsilon) ) bCur = false;

    if ( bCur == false ) {
        Matrix3<Real> transpos = m.toTranspose();
        bool bTrans = true;

        for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ )
            if ( this->data[i] < (transpos.data[i] - epsilon) || this->data[i] > (transpos.data[i] + epsilon) ) bTrans = false;

        if ( bTrans ) {
            std::cerr << "[Matrix3:isEquivalent] Notice: The provided matrix is not equivalent, but the transpose is equivalent to this matrix." << std::endl;
            return false;
        }

        return false;
    }

    return true;
}

template <typename Real>
void Matrix3<Real>::zero() {
    std::memset(this->data, 0, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix3<Real>::transpose() {
    std::swap(this->data[A_12], this->data[A_21]);
    std::swap(this->data[A_13], this->data[A_31]);
    std::swap(this->data[A_23], this->data[A_32]);
}

template <typename Real>
void Matrix3<Real>::identity() {
    std::memset(this->data, 0, COMPONENT_COUNT * sizeof(Real));
    this->data[A_11] = Real(1);
    this->data[A_22] = Real(1);
    this->data[A_33] = Real(1);
}

template <typename Real>
void Matrix3<Real>::invert() {
    Matrix3<Real> inverse = Matrix3<Real>::Inverse(*this);
    std::memcpy(this->data, inverse.data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix3<Real>::clear(bool identity) {
    std::memset(this->data, 0, COMPONENT_COUNT * sizeof(Real));

    if ( identity ) {
        this->data[A_11] = Real(1);
        this->data[A_22] = Real(1);
        this->data[A_33] = Real(1);
    }
}

template <typename Real>
void Matrix3<Real>::toRawMatrix(Real* const matrix, bool colMajor) const {
    if ( nullptr == matrix ) return;
    Matrix3<Real> result = (*this);
    if ( colMajor == false ) result.transpose();
    std::memcpy(matrix, result.data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix3<Real>::getData(Real* const matrix, bool colMajor) const {
    this->toRawMatrix(matrix, colMajor);
}

template <typename Real>
Real Matrix3<Real>::determinant() const {
    return Matrix3<Real>::Determinant(*this);
}

template <typename Real>
Matrix3<Real> Matrix3<Real>::inverse() const {
    return Matrix3<Real>::Inverse(*this);
}

template <typename Real>
Matrix3<Real> Matrix3<Real>::inversed() const {
    return Matrix3<Real>::Inverse(*this);
}

template <typename Real>
Matrix3<Real> Matrix3<Real>::transposed() const {
    return Matrix3<Real>::Transpose(*this);
}

template <typename Real>
template <typename RealCastType>
Matrix3<RealCastType> Matrix3<Real>::cast() {
    Matrix3<RealCastType> result;
    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ )
        result.data[i] = static_cast<RealCastType>(this->data[i]);
    return result;
}

template <typename Real>
Real& Matrix3<Real>::get(std::size_t i, std::size_t j) {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix3:get] Index i out of bounds.");
	if ( j >= COL_COUNT ) throw std::exception("[Matrix3:get] Index j out of bounds.");

    return this->data[i * ROW_SIZE + j];
}

template <typename Real>
const Real& Matrix3<Real>::get(std::size_t i, std::size_t j) const {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix3:get] Index i out of bounds.");
	if ( j >= COL_COUNT ) throw std::exception("[Matrix3:get] Index j out of bounds.");

    return this->data[i * ROW_SIZE + j];
}

template <typename Real>
Vector3<Real> Matrix3<Real>::getRow(std::size_t i) const {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix3:getRow] Error: Row index out of bounds.");
    if ( i == 0 ) return Vector3<Real>(this->data[A_11], this->data[A_12], this->data[A_13]);
    if ( i == 1 ) return Vector3<Real>(this->data[A_21], this->data[A_22], this->data[A_23]);
    if ( i == 2 ) return Vector3<Real>(this->data[A_31], this->data[A_32], this->data[A_33]);
}

template <typename Real>
Vector3<Real> Matrix3<Real>::getColumn(std::size_t i) const {
    if ( i >= COL_COUNT ) throw std::exception("[Matrix3:getColumn] Error: Column index out of bounds.");
    if ( i == 0 ) return Vector3<Real>(this->data[A_11], this->data[A_21], this->data[A_31]);
    if ( i == 1 ) return Vector3<Real>(this->data[A_12], this->data[A_22], this->data[A_32]);
    if ( i == 2 ) return Vector3<Real>(this->data[A_13], this->data[A_23], this->data[A_33]);
}

template <typename Real>
Matrix3<Real> Matrix3<Real>::toTranspose() const {
    Matrix3<Real> result = (*this);
    return Matrix3<Real>::Transpose(result);
}

template <typename Real>
Matrix3<Real> Matrix3<Real>::toInverse() const {
    Matrix3<Real> result = (*this);
    return Matrix3<Real>::Inverse(result);
}

template <typename Real>
Matrix3<Real> Matrix3<Real>::apply(const Vector3<Real>& v, bool colMajor) const {
    Matrix3<Real> m = (*this).transposed();
    m.setRow(0, m.data[A_11] * v.x(), m.data[A_12] * v.x(), m.data[A_13] * v.x());
    m.setRow(1, m.data[A_21] * v.y(), m.data[A_22] * v.y(), m.data[A_23] * v.y());
    m.setRow(2, m.data[A_31] * v.z(), m.data[A_32] * v.z(), m.data[A_33] * v.z());

    if ( colMajor ) m.transpose();
    return m;
}

template <typename Real>
Vector3<Real> Matrix3<Real>::applyTo(const Vector3<Real>& v) const {
    Vector3<Real> result;
    result.x() = this->data[A_11] * v.x() + this->data[A_12] * v.y() + this->data[A_13] * v.z();
    result.y() = this->data[A_21] * v.x() + this->data[A_22] * v.y() + this->data[A_23] * v.z();
    result.z() = this->data[A_31] * v.x() + this->data[A_32] * v.y() + this->data[A_33] * v.z();
    return result;
}

template <typename Real>
Vector4<Real> Matrix3<Real>::applyTo(const Vector4<Real>& v) const {
    Vector4<Real> result;
    result.x() = this->data[A_11] * v.x() + this->data[A_12] * v.y() + this->data[A_13] * v.z();
    result.y() = this->data[A_21] * v.x() + this->data[A_22] * v.y() + this->data[A_23] * v.z();
    result.z() = this->data[A_31] * v.x() + this->data[A_32] * v.y() + this->data[A_33] * v.z();
    result.w() = v.w();
    return result;
}

template <typename Real>
const Real* const Matrix3<Real>::constData() const {
    return this->data;
}

template <typename Real>
Matrix3<Real>::operator const Real* const () const {
    return this->data;
}

template <typename Real>
Real& Matrix3<Real>::operator () (std::size_t i, std::size_t j) {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix3:()] Index i out of bounds.");
	if ( j >= COL_COUNT ) throw std::exception("[Matrix3:()] Index j out of bounds.");

    return this->data[i * ROW_COUNT + j];
}

template <typename Real>
const Real& Matrix3<Real>::operator () (std::size_t i, std::size_t j) const {
    if ( i >= ROW_COUNT ) throw std::exception("[Matrix3:()] Index i out of bounds.");
	if ( j >= COL_COUNT ) throw std::exception("[Matrix3:()] Index j out of bounds.");

    return this->data[i * ROW_COUNT + j];
}

template <typename Real>
void Matrix3<Real>::set(unsigned int index, Real value) {
    if ( index >= COMPONENT_COUNT ) throw std::exception("[Matrix3:set] Index out of bounds.");
    this->data[index] = value;
}

template <typename Real>
Real Matrix3<Real>::get(unsigned int index) {
    if ( index >= COMPONENT_COUNT ) throw std::exception("[Matrix3:get] Index out of bounds.");
    return this->data[index];
}

template <typename Real>
std::ostream& operator << (std::ostream& out, const Matrix3<Real>& m) {
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "[" << m(0, 0) << "\t" << m(0, 1) << "\t" << m(0, 2) << "]" << std::endl;
    std::cout << "[" << m(1, 0) << "\t" << m(1, 1) << "\t" << m(1, 2) << "]" << std::endl;
    std::cout << "[" << m(2, 0) << "\t" << m(2, 1) << "\t" << m(2, 2) << "]" << std::endl;
    return out;
}

template <typename Real>
bool Matrix3<Real>::operator == (const Matrix3<Real>& m) {
    for ( unsigned int i = 0; i < COMPONENT_COUNT; i++ )
        if ( this->data[i] != m.data[i] ) return false;
    return true;
}

template <typename Real>
bool Matrix3<Real>::operator != (const Matrix3<Real>& m) {
    return !(*this == m);
}

template <typename Real>
Matrix3<Real>& Matrix3<Real>::operator = (const Matrix3<Real>& m) {
    if ( this == &m ) return *this;
    std::memcpy(this->data, m.data, COMPONENT_COUNT * sizeof(Real));
    return *this;
}

template <typename Real>
Matrix3<Real>& Matrix3<Real>::operator = (const Real* data) {
    if ( nullptr == data ) return *this;
    std::memcpy(this->data, data, COMPONENT_COUNT * sizeof(Real));
    return *this;
}

template <typename Real>
Vector3<Real> Matrix3<Real>::operator * (const Vector3<Real>& v) {
    return this->applyTo(v);
}

template <typename Real>
Matrix3<Real> Matrix3<Real>::operator * (const Matrix3<Real>& m) {
    return Matrix3<Real>::Multiply(*this, m);
}

template <typename Real>
Matrix3<Real>& Matrix3<Real>::operator *= (const Matrix3<Real>& m) {
    Matrix3<Real> result = Matrix3<Real>::Multiply(*this, m);
    std::memcpy(this->data, result.data, COMPONENT_COUNT * sizeof(Real));
    return *this;
}

template <typename Real>
void Matrix3<Real>::ToRawMatrix(const Matrix3<Real>& m, Real* const matrix, bool colMajor) {
    if ( nullptr == matrix ) {
        std::cerr << "[Matrix3:ToRawMatrix] Error: Nullptr matrix." << std::endl;
        return;
    }

    Matrix3<Real> result = m;
    if ( colMajor == false ) result.transpose();
    std::memcpy(matrix, result.data, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix3<Real>::Clear(Matrix3<Real>& m) {
    std::memset(m.data, 0, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix3<Real>::Identity(Matrix3<Real>& m) {
    std::memset(m.data, 0, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
void Matrix3<Real>::Zero(Matrix3<Real>& m) {
    std::memset(this->data, 0, COMPONENT_COUNT * sizeof(Real));
}

template <typename Real>
Real Matrix3<Real>::Determinant(const Matrix3<Real>& m) {
    Real d = 0.0;
    for ( unsigned int i = 0; i < ROW_COUNT; i++ ) {
        d += (m(0, i) * (m(1, (i+1)%3) * m(2, (i+2)%3) - m(1, (i+2)%3) * m(2, (i+1)%3)));
    }

    return d;
}

/* Memory friendly matrix multiplication (Gita A., Lan V.) */
template <typename Real>
Matrix3<Real> Matrix3<Real>::Multiply(const Matrix3<Real>& a, const Matrix3<Real>& b) {
    Matrix3<Real> result(false);

    for ( unsigned int i = 0; i < ROW_COUNT; i++ )
        for ( unsigned int k = 0; k < ROW_COUNT; k++ )
            for ( unsigned int j = 0; j < ROW_COUNT; j++ )
                result(i, j) += a(i, k) * b(k, j);
    return result;
}

template <typename Real>
Matrix3<Real> Matrix3<Real>::Transpose(const Matrix3<Real>& m) {
    Matrix3<Real> result = m;
    std::swap(result.data[A_12], result.data[A_21]);
    std::swap(result.data[A_13], result.data[A_31]);
    std::swap(result.data[A_23], result.data[A_32]);
    return result;
}

template <typename Real>
Matrix3<Real> Matrix3<Real>::Inverse(const Matrix3<Real>& m) {
    Matrix3<Real> result;
    Real d = Matrix3<Real>::Determinant(m);

    for ( unsigned int i = 0; i < ROW_COUNT; i++ ) {
        for ( unsigned int j = 0; j < COL_COUNT; j++ ) {
            result(i, j) = ((m((i+1) % 3, (j+1) % 3) * m((i+2) % 3, (j+2) % 3)) - 
                            (m((i+1) % 3, (j+2) % 3) * m((i+2) % 3, (j+1) % 3))) / d;
        }
    }

    return result;
}

template <typename Real>
Matrix3<Real> Matrix3<Real>::Zero() {
    return Matrix3<Real>(false);
}

template <typename Real>
Matrix3<Real> Matrix3<Real>::Identity() {
    return Matrix3<Real>(true);
}

typedef Matrix3<float> Matrix3f;
typedef Matrix3<double> Matrix3d;
typedef Matrix3<long> Matrix3l;
typedef Matrix3<int> Matrix3i;
typedef Matrix3<short> Matrix3s;

typedef Matrix3<float> Mat3f;
typedef Matrix3<double> Mat3d;
typedef Matrix3<long> Mat3l;
typedef Matrix3<int> Mat3i;
typedef Matrix3<short> Mat3s;

typedef Matrix3<float> Mat3;

#endif
