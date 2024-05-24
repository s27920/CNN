//
// Created by janek on 5/22/2024.
//

#include "Image.h"

const std::vector<int> * Image::getPixelVector() const {
    return pixelVector;
}

const int Image::getLabel() const {
    return label;
}

Image::Image(const std::vector<int> *pixelVector, const int label) : pixelVector(pixelVector), label(label) {}

int Image::checkLabel(int value) {
    return value==label;
}
