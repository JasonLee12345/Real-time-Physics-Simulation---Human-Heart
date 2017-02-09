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
#ifndef COLOR_4_H
#define COLOR_4_H

/* Iostream is only required for basic stream output. */
#include <iostream>

/*
 * Foreward declaration for the standard output stream << operator.
 */
template <typename Real> 
class Color4;

/*
 * Due to the templated nature of the Color4 class a foreward declaration of
 * the standard out stream operator must be defined.
 */
template <typename Real>
std::ostream& operator << (std::ostream& out, const Color4<Real>& color);

/*
 * The Color4 class represents a 4-data color value (r, g, b, a). The actual
 * representation of the internal numbers can be defined by the template type.
 * The most commonly used integer and float type color typedefs are defined
 * for simplicity at the end of this file.
 */
template <typename Real>
class Color4 {
    static_assert(std::is_integral<Real>::value || std::is_floating_point<Real>::value, 
    "[Color4:Type] Error: Color4 Real type must be an integral or floating point numerical representation.");

    enum Axis { R, G, B, A, COMPONENT_COUNT };

public:
	Color4(Real grayScale = 0);
	Color4(Real r, Real g, Real b, Real a);
	Color4(const Color4<Real>& color);
	~Color4();

	/*
	 * Sets the red value of this color. Depending on the template type of this
	 * color the bounds of the value may differ (integer: [0, 255] and for
	 * float/double: [0,1.0]). This constraint must be inforced by the client.
	 */
	void setR(Real r);

	/*
	 * Sets the green value of this color. Depending on the template type of this
	 * color the bounds of the value may differ (integer: [0, 255] and for
	 * float/double: [0,1.0]). This constraint must be inforced by the client.
	 */
	void setG(Real g);

	/*
	 * Sets the blue value of this color. Depending on the template type of this
	 * color the bounds of the value may differ (integer: [0, 255] and for
	 * float/double: [0,1.0]). This constraint must be inforced by the client.
	 */
	void setB(Real b);

	/*
	 * Sets the alpha value of this color. Depending on the template type of this
	 * color the bounds of the value may differ (integer: [0, 255] and for
	 * float/double: [0,1.0]). This constraint must be inforced by the client.
	 */
	void setA(Real a);

	/*
	 * Adds the specified amount to the existing red value. The appropriate
	 * bounds of this value depends on the template type utilized:
	 * (integer: [0, 255] and for float/double: [0, 1.0]).
	 */
	void addR(Real r);

	/*
	 * Adds the specified amount to the existing green value. The appropriate
	 * bounds of this value depends on the template type utilized:
	 * (integer: [0, 255] and for float/double: [0, 1.0]).
	 */
	void addG(Real g);

	/*
	 * Adds the specified amount to the existing blue value. The appropriate
	 * bounds of this value depends on the template type utilized:
	 * (integer: [0, 255] and for float/double: [0, 1.0]).
	 */
	void addB(Real b);

	/*
	 * Adds the specified amount to the existing alpha value. The appropriate
	 * bounds of this value depends on the template type utilized:
	 * (integer: [0, 255] and for float/double: [0, 1.0]).
	 */
	void addA(Real a);

	/*
	 * Returns the red component of this color.
	 */
	Real getR() const;

	/*
	 * Returns the green component of this color.
	 */
	Real getG() const;

	/*
	 * Returns the blue component of this color.
	 */
	Real getB() const;

	/*
	 * Returns the alpha component of this color.
	 */
	Real getA() const;

	/*
	 * Returns a modifable reference to the red value in this color.
	 */
	Real& r();

	/*
	 * Returns a modifable reference to the green value in this color.
	 */
	Real& g();

	/*
	 * Returns a modifable reference to the blue value in this color.
	 */
	Real& b();

	/*
	 * Returns a modifable reference to the alpha value in this color.
	 */
	Real& a();

    const Real& r() const;
    const Real& g() const;
    const Real& b() const;
    const Real& a() const;

	/*
	 * Returns a constant pointer to the raw data in this color.
	 */
	operator const Real*() const;

	/*
	 * Returns a pointer to the raw data in this color.
	 */
	operator Real* ();

	/*
	 * Equality operators for colors.
	 */
	bool operator == (const Color4<Real>& color);
	bool operator != (const Color4<Real>& color);

	/*
	 * Provides a basic textual representation of this color in a standard
	 * output stream. A foreward declaration of this friend operator is required
	 * before the declaration of the Color3 class.
	 */
	friend std::ostream& operator << <Real> (std::ostream& out, const Color4<Real>& color);

	/*
	 * A Default set of basic colors are provided for quick access.
	 */
	static const Color4<Real> RED;
	static const Color4<Real> GREEN;
	static const Color4<Real> BLUE;
	static const Color4<Real> YELLOW;
	static const Color4<Real> WHITE;
	static const Color4<Real> GRAY;
	static const Color4<Real> BLACK;

private:
	Real data[COMPONENT_COUNT];
};

/*
 * The actual definition of each color value depends on the actual template
 * type used to define the color. These template specializations provide the
 * default color definitions for the intended color template types.
 */
template <> const Color4<float> Color4<float>::RED = Color4<float>(1.0f, 0.0f, 0.0f, 1.0f);
template <> const Color4<double> Color4<double>::RED = Color4<double>(1.0, 0.0, 0.0, 1.0);
template <> const Color4<int> Color4<int>::RED = Color4<int>(255, 0, 0, 255);

template <> const Color4<float> Color4<float>::GREEN = Color4<float>(0.0f, 1.0f, 0.0f, 1.0f);
template <> const Color4<double> Color4<double>::GREEN = Color4<double>(0.0, 1.0, 0.0, 1.0);
template <> const Color4<int> Color4<int>::GREEN = Color4<int>(0, 255, 0, 255);

template <> const Color4<float> Color4<float>::BLUE = Color4<float>(0.0f, 0.0f, 1.0f, 1.0f);
template <> const Color4<double> Color4<double>::BLUE = Color4<double>(0.0, 0.0, 1.0, 1.0);
template <> const Color4<int> Color4<int>::BLUE = Color4<int>(0, 0, 255, 255);

template <> const Color4<float> Color4<float>::YELLOW = Color4<float>(1.0f, 1.0f, 0.0f, 1.0f);
template <> const Color4<double> Color4<double>::YELLOW = Color4<double>(1.0, 1.0, 0.0, 1.0);
template <> const Color4<int> Color4<int>::YELLOW = Color4<int>(255, 255, 0, 255);

template <> const Color4<float> Color4<float>::WHITE = Color4<float>(1.0f, 1.0f, 1.0f, 1.0f);
template <> const Color4<double> Color4<double>::WHITE = Color4<double>(1.0, 1.0, 1.0, 1.0);
template <> const Color4<int> Color4<int>::WHITE = Color4<int>(255, 255, 255, 255);

template <> const Color4<float> Color4<float>::GRAY = Color4<float>(1.0f, 1.0f, 1.0f, 1.0f);
template <> const Color4<double> Color4<double>::GRAY = Color4<double>(1.0, 1.0, 1.0, 1.0);
template <> const Color4<int> Color4<int>::GRAY = Color4<int>(127, 127, 127, 255);

template <> const Color4<float> Color4<float>::BLACK = Color4<float>(0.0f, 0.0f, 0.0f, 1.0f);
template <> const Color4<double> Color4<double>::BLACK = Color4<double>(0.0, 0.0, 0.0, 1.0);
template <> const Color4<int> Color4<int>::BLACK = Color4<int>(0, 0, 0, 255);

template <typename Real>
Color4<Real>::Color4(Real grayScale) {
	this->data[R] = grayScale;
	this->data[G] = grayScale;
	this->data[B] = grayScale;
	this->data[A] = grayScale;
}

template <typename Real>
Color4<Real>::Color4(Real r, Real g, Real b, Real a) {
	this->data[R] = r;
	this->data[G] = g;
	this->data[B] = b;
	this->data[A] = a;
}

template <typename Real>
Color4<Real>::Color4(const Color4<Real>& color) {
	this->data[R] = color.data[R];
	this->data[G] = color.data[G];
	this->data[B] = color.data[B];
	this->data[A] = color.data[A];
}

template <typename Real>
Color4<Real>::~Color4() {}

template <typename Real>
void Color4<Real>::setR(Real r) {
	this->data[R] = r;
}

template <typename Real>
void Color4<Real>::setG(Real g) {
	this->data[G] = g;
}

template <typename Real>
void Color4<Real>::setB(Real b) {
	this->data[B] = b;
}

template <typename Real>
void Color4<Real>::setA(Real a) {
	this->data[A] = a;
}

template <typename Real>
void Color4<Real>::addR(Real r) {
	this->data[R] += r;
}

template <typename Real>
void Color4<Real>::addG(Real g) {
	this->data[G] += g;
}

template <typename Real>
void Color4<Real>::addB(Real b) {
	this->data[B] += b;
}

template <typename Real>
void Color4<Real>::addA(Real a) {
	this->data[A] += a;
}

template <typename Real>
Real Color4<Real>::getR() const {
	return this->data[R];
}

template <typename Real>
Real Color4<Real>::getG() const {
	return this->data[G];
}

template <typename Real>
Real Color4<Real>::getB() const {
	return this->data[B];
}

template <typename Real>
Real Color4<Real>::getA() const {
	return this->data[A];
}

template <typename Real>
Real& Color4<Real>::r() {
	return this->data[R];
}

template <typename Real>
Real& Color4<Real>::g() {
	return this->data[G];
}

template <typename Real>
Real& Color4<Real>::b() {
	return this->data[B];
}

template <typename Real>
Real& Color4<Real>::a() {
	return this->data[A];
}

template <typename Real>
const Real& Color4<Real>::r() const {
    return this->data[R];
}

template <typename Real>
const Real& Color4<Real>::g() const {
    return this->data[G];
}

template <typename Real>
const Real& Color4<Real>::b() const {
    return this->data[B];
}

template <typename Real>
const Real& Color4<Real>::a() const {
    return this->data[A];
}

template <typename Real>
Color4<Real>::operator const Real*() const {
	return &this->data[0];
}

template <typename Real>
Color4<Real>::operator Real* () {
	return &this->data[0];
}

template <typename Real>
bool Color4<Real>::operator == (const Color4<Real>& color) {
	if ( this->data[R] != color.data[R] ) return false;
	if ( this->data[G] != color.data[G] ) return false;
	if ( this->data[B] != color.data[B] ) return false;
	if ( this->data[A] != color.data[A] ) return false;
	return true;
}

template <typename Real>
bool Color4<Real>::operator != (const Color4<Real>& color) {
	if ( *this == color ) return false;
	else return true;
}

template <typename Real>
std::ostream& operator << <Real> (std::ostream& out, const Color4<Real>& color) {
	out << "[ " << color.data[Color4<Real>::R] << " " << color.data[Color4<Real>::G] << " " << color.data[Color4<Real>::B] << " " << color.data[Color4<Real>::A] << " ]";
	return out;
}

/*
 * Assumed color template types. These types are generally the only used
 * representations of a 3 value color. Additional types can be defined, however
 * the default colors for that type will have to be defined in the template
 * specialization section found above the implementation of this class.
 */
typedef Color4<float> Color4f;
typedef Color4<double> Color4d;
typedef Color4<int> Color4i;

#endif
