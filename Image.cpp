//
// Created by janek on 5/22/2024.
//

#include "Image.h"

const std::vector<unsigned char> * Image::getPixelVector() const {
    return pixelVector;
}

const unsigned char Image::getLabel() const {
    return label;
}

Image::Image(const std::vector<unsigned char> *pixelVector, const unsigned char label) : pixelVector(pixelVector), label(label) {}

int Image::checkLabel(int value) {
    return value==label;
}
