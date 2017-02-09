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
#ifndef COLOR_3_H
#define COLOR_3_H

/* Iostream is only required for basic stream output. */
#include <iostream>

/*
 * Foreward declaration for the standard output stream << operator.
 */
template <typename Real> 
class Color3;

/*
 * Due to the templated nature of the Color3 class a foreward declaration of
 * the standard out stream operator must be defined.
 */
template <typename Real>
std::ostream& operator << (std::ostream& out, const Color3<Real>& color);

/*
 * The Color3 class represents a 3-data color value (r, g, b). The actual
 * representation of the internal numbers can be defined by the template type.
 * The most commonly used integer and float type color typedefs are defined
 * for simplicity at the end of this file.
 */
template <typename Real>
class Color3 {
    static_assert(std::is_integral<Real>::value || std::is_floating_point<Real>::value, 
    "[Color3:Type] Error: Color3 Real type must be an integral or floating point numerical representation.");

    enum Axis { R, G, B, COMPONENT_COUNT };

public:
	Color3(Real grayScale = 0);
	Color3(Real r, Real g, Real b);
	Color3(const Color3<Real>& color);
	~Color3();

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
	 * float/double: [0, 1.0]). This constraint must be inforced by the client.
	 */
	void setB(Real b);

	/*
	 * Adds the specified amount to the existing red value. The appropriate
	 * bounds of this value depends on the template type utilized:
	 * (integer: [0, 255] and for float/double: [0, 1.0]).
	 */
	void addR(Real r);

	/*
	 * Adds the specified amount to the existing green value.
	 */
	void addG(Real g);

	/*
	 * Adds the specified amount to the existing blue value.
	 */
	void addB(Real b);

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

    const Real& r() const;
    const Real& g() const;
    const Real& b() const;

	/*
	 * Returns a constant pointer to the raw data in this color.
	 */
	operator const Real*() const;

	/*
	 * Returns a pointer to the raw data in this color.
	 */
	operator Real*();

	/*
	 * Equality operators for colors.
	 */
	bool operator == (const Color3<Real>& color);
	bool operator != (const Color3<Real>& color);

	/*
	 * Provides a basic textual representation of this color in a standard
	 * output stream. A forward declaration of this friend operator is required
	 * before the declaration of the Color3 class.
	 */
	friend std::ostream& operator << <> (std::ostream& out, const Color3<Real>& color);

	static Color3<Real> FromHSV(float h, float s, float v);

	/*
	 * A Default set of basic colors are provided for quick access.
	 */
	static const Color3<Real> RED;
	static const Color3<Real> GREEN;
	static const Color3<Real> BLUE;
	static const Color3<Real> YELLOW;
	static const Color3<Real> WHITE;
	static const Color3<Real> GRAY;
	static const Color3<Real> BLACK;

private:
	Real data[COMPONENT_COUNT];
};

/*
 * The actual definition of each color value depends on the actual template
 * type used to define the color. These template specializations provide the
 * default color definitions for the intended color template types.
 */
template <> const Color3<float> Color3<float>::RED = Color3<float>(1.0f, 0.0f, 0.0f);
template <> const Color3<double> Color3<double>::RED = Color3<double>(1.0, 0.0, 0.0);
template <> const Color3<int> Color3<int>::RED = Color3<int>(255, 0, 0);

template <> const Color3<float> Color3<float>::GREEN = Color3<float>(0.0f, 1.0f, 0.0f);
template <> const Color3<double> Color3<double>::GREEN = Color3<double>(0.0, 1.0, 0.0);
template <> const Color3<int> Color3<int>::GREEN = Color3<int>(0, 255, 0);

template <> const Color3<float> Color3<float>::BLUE = Color3<float>(0.0f, 0.0f, 1.0f);
template <> const Color3<double> Color3<double>::BLUE = Color3<double>(0.0, 0.0, 1.0);
template <> const Color3<int> Color3<int>::BLUE = Color3<int>(0, 0, 255);

template <> const Color3<float> Color3<float>::YELLOW = Color3<float>(1.0f, 1.0f, 0.0f);
template <> const Color3<double> Color3<double>::YELLOW = Color3<double>(1.0, 1.0, 0.0);
template <> const Color3<int> Color3<int>::YELLOW = Color3<int>(255, 255, 0);

template <> const Color3<float> Color3<float>::WHITE = Color3<float>(1.0f, 1.0f, 1.0f);
template <> const Color3<double> Color3<double>::WHITE = Color3<double>(1.0, 1.0, 1.0);
template <> const Color3<int> Color3<int>::WHITE = Color3<int>(255, 255, 255);

template <> const Color3<float> Color3<float>::GRAY = Color3<float>(1.0f, 1.0f, 1.0f);
template <> const Color3<double> Color3<double>::GRAY = Color3<double>(1.0, 1.0, 1.0);
template <> const Color3<int> Color3<int>::GRAY = Color3<int>(127, 127, 127);

template <> const Color3<float> Color3<float>::BLACK = Color3<float>(0.0f, 0.0f, 0.0f);
template <> const Color3<double> Color3<double>::BLACK = Color3<double>(0.0, 0.0, 0.0);
template <> const Color3<int> Color3<int>::BLACK = Color3<int>(0, 0, 0);

template <typename Real>
Color3<Real>::Color3(Real grayScale) {
	this->data[R] = grayScale;
	this->data[G] = grayScale;
	this->data[B] = grayScale;
}

template <typename Real>
Color3<Real>::Color3(Real r, Real g, Real b) {
	this->data[R] = r;
	this->data[G] = g;
	this->data[B] = b;
}

template <typename Real>
Color3<Real>::Color3(const Color3<Real>& color) {
	this->data[R] = color.data[R];
	this->data[G] = color.data[G];
	this->data[B] = color.data[B];
}

template <typename Real>
Color3<Real>::~Color3() {}

template <typename Real>
void Color3<Real>::setR(Real r) {
	this->data[R] = r;
}

template <typename Real>
void Color3<Real>::setG(Real g) {
	this->data[G] = g;
}

template <typename Real>
void Color3<Real>::setB(Real b) {
	this->data[B] = b;
}

template <typename Real>
void Color3<Real>::addR(Real r) {
	this->data[R] += r;
}

template <typename Real>
void Color3<Real>::addG(Real g) {
	this->data[G] += g;
}

template <typename Real>
void Color3<Real>::addB(Real b) {
	this->data[B] += b;
}

template <typename Real>
Real Color3<Real>::getR() const {
	return this->data[R];
}

template <typename Real>
Real Color3<Real>::getG() const {
	return this->data[G];
}

template <typename Real>
Real Color3<Real>::getB() const {
	return this->data[B];
}

template <typename Real>
Real& Color3<Real>::r() {
	return this->data[R];
}

template <typename Real>
Real& Color3<Real>::g() {
	return this->data[G];
}

template <typename Real>
Real& Color3<Real>::b() {
	return this->data[B];
}

template <typename Real>
const Real& Color3<Real>::r() const {
    return this->data[R];
}

template <typename Real>
const Real& Color3<Real>::g() const {
    return this->data[G];
}

template <typename Real>
const Real& Color3<Real>::b() const {
    return this->data[B];
}

template <typename Real>
Color3<Real>::operator const Real*() const {
	return &this->data[0];
}

template <typename Real>
Color3<Real>::operator Real*() {
	return &this->data[0];
}

template <typename Real>
bool Color3<Real>::operator == (const Color3<Real>& color) {
	if ( this->data[R] != color.data[R] ) return false;
	if ( this->data[G] != color.data[G] ) return false;
	if ( this->data[B] != color.data[B] ) return false;
	return true;
}

template <typename Real>
bool Color3<Real>::operator != (const Color3<Real>& color) {
	if ( *this == color ) return false;
	else return true;
}

template <typename Real>
std::ostream& operator << <Real> (std::ostream& out, const Color3<Real>& color) {
	out << "[ " << color.data[Color3<Real>::R] << " " << color.data[Color3<Real>::G] << " " << color.data[Color3<Real>::B] << " ]";
	return out;
}

template <typename Real>
Color3<Real> Color3<Real>::FromHSV(float h, float s, float v) {
	unsigned int i = static_cast<unsigned int>(std::floor(h * 6));
    float f = h * 6 - static_cast<float>(i);
    float p = v * (1.0f - s);
    float q = v * (1.0f - f * s);
    float t = v * (1.0f - (1 - f) * s);
	float r, g, b;

    switch ( i % 6 ) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }

	Color3<Real> color;
	color.data[R] = static_cast<Real>(r * 255.0f);
	color.data[G] = static_cast<Real>(g * 255.0f);
	color.data[B] = static_cast<Real>(b * 255.0f);
	return color;
}

/*
 * Assumed color template types. These types are generally the only used
 * representations of a 3 value color. Additional types can be defined, however
 * the default colors for that type will have to be defined in the template
 * specialization section found above the implementation of this class.
 */
typedef Color3<float> Color3f;
typedef Color3<double> Color3d;
typedef Color3<int> Color3i;

#endif
