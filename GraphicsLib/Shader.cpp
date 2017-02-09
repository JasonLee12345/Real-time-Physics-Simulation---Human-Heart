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
#include "Shader.h"
#include <fstream>
#include <iostream>

const static std::string DIFFUSE_TEXTURE = "diffuseTexture";
const static std::string NORMAL_TEXTURE = "normalTexture";
const static std::string SPECULAR_TEXTURE = "specularTexture";
const static std::string HEIGHTMAP_TEXTURE = "heightmapTexture";

Shader::Shader() {
    this->programId = 0;
    this->vertexId = 0;
    this->fragmentId = 0;
    this->vertFilename = std::string();
    this->fragFilename = std::string();
    this->diffuseTexture = nullptr;
    this->normalTexture = nullptr;
    this->specularTexture = nullptr;
}

Shader::Shader(const Shader& shader) {
    this->programId = shader.programId;
    this->vertexId = shader.vertexId;
    this->fragmentId = shader.fragmentId;
    this->vertFilename = shader.vertFilename;
    this->fragFilename = shader.fragFilename;
    this->diffuseTexture = shader.diffuseTexture;
    this->normalTexture = shader.normalTexture;
    this->specularTexture = shader.specularTexture;
}

Shader::~Shader() {
    glDeleteProgram(this->programId);
    glDeleteShader(this->vertexId);
    glDeleteShader(this->fragmentId);
}

bool Shader::load(const std::string& vertexFilename, const std::string& fragmentFilename) {
    if ( !this->loadFile(vertexFilename, this->vertSource) ) return false;
    if ( !this->loadFile(fragmentFilename, this->fragSource) ) return false;

    this->vertFilename = vertexFilename;
    this->fragFilename = fragmentFilename;

    this->vertexId = glCreateShader(GL_VERTEX_SHADER);
    this->fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vsource_cstr = this->vertSource.c_str();
    const char* fsource_cstr = this->fragSource.c_str();

    glShaderSource(this->vertexId, 1, &vsource_cstr, 0);
    glShaderSource(this->fragmentId, 1, &fsource_cstr, 0);

    return true;
}

bool Shader::compile() {
    glCompileShader(this->vertexId);
    if ( !this->compileStatus(this->vertexId, this->vertFilename) ) return false;

    glCompileShader(this->fragmentId);
    if ( !this->compileStatus(this->fragmentId, this->fragFilename) ) return false;

    return true;
}

bool Shader::link() {
    this->programId = glCreateProgram();
    glAttachShader(this->programId, this->vertexId);
    glAttachShader(this->programId, this->fragmentId);
    glLinkProgram(this->programId);
    
    if ( !this->linkStatus(this->programId) ) return false;
    return true;
}

bool Shader::loadDiffuseTexture(const std::string& filename) {
    if ( filename.length() == 0 ) return false;
    this->diffuseTexture = std::make_shared<Texture>();
    this->diffuseTexture->load(filename);
    return true;
}

bool Shader::loadNormalTexture(const std::string& filename) {
    if ( filename.length() == 0 ) return false;
    this->normalTexture = std::make_shared<Texture>();
    this->normalTexture->load(filename);
    return true;
}

bool Shader::loadSpecularTexture(const std::string& filename) {
    if ( filename.length() == 0 ) return false;
    this->specularTexture = std::make_shared<Texture>();
    this->specularTexture->load(filename);
    return true;
}

bool Shader::loadHeightmapTexture(const std::string& filename) {
    if ( filename.length() == 0 ) return false;
    this->heightmapTexture = std::make_shared<Texture>();
    this->heightmapTexture->load(filename);
    return true;
}

bool Shader::enable() {
    glUseProgram(this->programId);
    
    if ( this->diffuseTexture != nullptr ) {
        glActiveTextureARB(GL_TEXTURE0);
        this->diffuseTexture->render();
        this->uniform1i(DIFFUSE_TEXTURE, 0);
    }

    if ( this->normalTexture != nullptr ) {
        glActiveTextureARB(GL_TEXTURE1);
        this->normalTexture->render();
        this->uniform1i(NORMAL_TEXTURE, 1);
    }

    if ( this->specularTexture != nullptr ) {
        glActiveTextureARB(GL_TEXTURE2);
        this->specularTexture->render();
        this->uniform1i(SPECULAR_TEXTURE, 2);
    }

    if ( this->heightmapTexture != nullptr ) {
        glActiveTextureARB(GL_TEXTURE3);
        this->heightmapTexture->render();
        this->uniform1i(HEIGHTMAP_TEXTURE, 3);
    }

    return true;
}

bool Shader::disable() {
    glUseProgram(0);
    return false;
}

Shader::operator unsigned int () const {
    return this->programId;
}

unsigned int Shader::getProgramID() const {
   return this->programId;
}

unsigned int Shader::id() const {
   return this->programId;
}

void Shader::uniform1f(const std::string& name, float value) const {
    int paramLocation = glGetUniformLocation(this->programId, name.c_str());
	glUniform1f(paramLocation, value);
}

void Shader::uniform2f(const std::string& name, float value0, float value1) const {
    int paramLocation = glGetUniformLocation(this->programId, name.c_str());
	glUniform2f(paramLocation, value0, value1);
}

void Shader::uniform3f(const std::string& name, float value0, float value1, float value2) const {
    int paramLocation = glGetUniformLocation(this->programId, name.c_str());
	glUniform3f(paramLocation, value0, value1, value2);
}

void Shader::uniform4f(const std::string& name, float value0, float value1, float value2, float value3) const {
    int paramLocation = glGetUniformLocation(this->programId, name.c_str());
	glUniform4f(paramLocation, value0, value1, value2, value3);
}

void Shader::uniform1i(const std::string& name, int value) const {
    int paramLocation = glGetUniformLocation(this->programId, name.c_str());
	glUniform1i(paramLocation, value);
}

void Shader::uniform2i(const std::string& name, int value0, int value1) const {
    int paramLocation = glGetUniformLocation(this->programId, name.c_str());
	glUniform2i(paramLocation, value0, value1);
}

void Shader::uniform3i(const std::string& name, int value0, int value1, int value2) const {
    int paramLocation = glGetUniformLocation(this->programId, name.c_str());
	glUniform3i(paramLocation, value0, value1, value2);
}

void Shader::uniform4i(const std::string& name, int value0, int value1, int value2, int value3) const {
    int paramLocation = glGetUniformLocation(this->programId, name.c_str());
	glUniform4i(paramLocation, value0, value1, value2, value3);
}

void Shader::uniform4fv(const std::string& name, unsigned int count, const float* values) const {
    int paramLocation = glGetUniformLocation(this->programId, name.c_str());
	glUniform4fv(paramLocation, count, values);
}

void Shader::uniformMatrix(const std::string& name, const Matrix4f& matrix) const {
    int paramLocation = glGetUniformLocation(this->programId, name.c_str());
	glUniformMatrix4fv(paramLocation, 1, false, matrix.constData());
}

void Shader::uniformMatrix(const std::string& name, const Matrix3f& matrix) const {
    int paramLocation = glGetUniformLocation(this->programId, name.c_str());
	glUniformMatrix3fv(paramLocation, 1, false, matrix.constData());
}

void Shader::uniformVector(const std::string& name, const Vector3f& vector) const {
    int paramLocation = glGetUniformLocation(this->programId, name.c_str());
	glUniform3f(paramLocation, vector[0], vector[1], vector[2]);
}

void Shader::uniformVector(const std::string& name, const Vector4f& vector) const {
    int paramLocation = glGetUniformLocation(this->programId, name.c_str());
	glUniform4f(paramLocation, vector[0], vector[1], vector[2], vector[3]);
}

bool Shader::loadFile(const std::string& filename, std::string& content) {
    if ( filename.length() == 0 ) {
        std::cerr << "[Shader:loadFile] Error: Cannot read filename: \"\"" << std::endl;
        return false;
    }

    std::ifstream file;
	file.open(filename.c_str());

	if ( (file.rdstate() & std::ifstream::failbit) != 0 ) {
		std::cout << "[Shader:loadFile] Error: Cannot open shader file: " + filename << std::endl;
		return false;
	}

	file.seekg(0, std::ios_base::end);
	content.reserve(static_cast<unsigned int>(file.tellg()));
	file.seekg(0, std::ios_base::beg);
	content.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

    return true;
}

bool Shader::compileStatus(unsigned int shaderId, const std::string& filename) const {
    GLint compile_status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compile_status);

	if ( compile_status == GL_FALSE ) {
		std::string error = "[Shader:compileStatus] Error: Compile shader error in: " + filename + "\n";
		GLint log_size = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &log_size);
		char* log_message = new char[log_size];
		glGetShaderInfoLog(shaderId, log_size, 0, log_message);
		error += "[Shader:OpenGLError] ";
		error += log_message;
		std::cerr << error;
		delete [] log_message;
		return false;
	}

	return true;
}

bool Shader::linkStatus(unsigned int programId) const {
    GLint link_status;
	glGetProgramiv(programId, GL_LINK_STATUS, &link_status);

	if ( link_status == GL_FALSE ) {
		std::string error = "[Shader:linkStatus] Error: Cannot link link program.";
		GLint log_size = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &log_size);
		char* log_message = new char[log_size];
		glGetProgramInfoLog(programId, log_size, 0, log_message);
		error += "[Shader:OpenGLError] ";
		error += log_message;
		std::cerr << error;
		delete [] log_message;
		std::cin.get();
		std::exit(EXIT_FAILURE);
	}
	return true;
}
