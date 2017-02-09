#include "Texture.h"
#include "PNG.h"
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>

Texture::Texture() {
    this->width = 0;
    this->height = 0;
    this->textureId = 0;
}

Texture::~Texture() {

}

bool Texture::load(const std::string& filename) {
    if ( filename.length() == 0 ) return false;

    unsigned int error = lodepng::decode(this->image, this->width, this->height, filename, LCT_RGBA);

    if ( error ) {
        std::cerr << "[Texture:load] Error: Could not load PNG image: " << filename << std::endl;
        return false;
    }
  
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &this->image[0]);

    return true;
}

void Texture::render() const {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
}
