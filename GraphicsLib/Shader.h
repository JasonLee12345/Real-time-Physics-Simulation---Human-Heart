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
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <memory>
#include <Matrix4.h>
#include <gl/glew.h>
#include "Texture.h"

class Shader {
public:
    Shader();
    Shader(const Shader& shader);
    virtual ~Shader();

    virtual bool load(const std::string& vertexFilename, const std::string& fragmentFilename);
    virtual bool compile();
    virtual bool link();

    bool loadDiffuseTexture(const std::string& filename);
    bool loadNormalTexture(const std::string& filename);
    bool loadSpecularTexture(const std::string& filename);
    bool loadHeightmapTexture(const std::string& filename);

    bool enable();
    bool disable();

    operator unsigned int () const;
    unsigned int getProgramID() const;
    unsigned int id() const;

    void uniform1f(const std::string& name, float value) const;
	void uniform2f(const std::string& name, float value0, float value1) const;
	void uniform3f(const std::string& name, float value0, float value1, float value2) const;
	void uniform4f(const std::string& name, float value0, float value1, float value2, float value3) const;
	void uniform1i(const std::string& name, int value) const;
	void uniform2i(const std::string& name, int value0, int value1) const;
	void uniform3i(const std::string& name, int value0, int value1, int value2) const;
	void uniform4i(const std::string& name, int value0, int value1, int value2, int value3) const;
	void uniform4fv(const std::string& name, unsigned int count, const float* values) const;
    void uniformMatrix(const std::string& name, const Matrix4f& matrix) const;
    void uniformMatrix(const std::string& name, const Matrix3f& matrix) const;
    void uniformVector(const std::string& name, const Vector3f& vector) const;
    void uniformVector(const std::string& name, const Vector4f& vector) const;

protected:
    bool loadFile(const std::string& filename, std::string& content);
    bool compileStatus(unsigned int shaderId, const std::string& filename) const;
    bool linkStatus(unsigned int programId) const;

public:
    unsigned int programId;
    unsigned int vertexId;
    unsigned int fragmentId;

    /* 2D Texture data of this mesh */
    std::shared_ptr<Texture> diffuseTexture;
    std::shared_ptr<Texture> normalTexture;
    std::shared_ptr<Texture> specularTexture;
    std::shared_ptr<Texture> heightmapTexture;

    /* Shader File Info */
    std::string vertFilename;
    std::string fragFilename;
    std::string vertSource;
    std::string fragSource;
};

#endif
