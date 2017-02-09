
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>

class Texture {
public:
    Texture();
    ~Texture();

    bool load(const std::string& filename);

    void render() const;

protected:
    std::vector<unsigned char> image;
    unsigned int width;
    unsigned int height;

    unsigned int textureId;
};

#endif
