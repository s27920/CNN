//
// Created by janek on 5/22/2024.
//

#ifndef CNN_IMAGE_H
#define CNN_IMAGE_H

#include <vector>
class Image {
private:
    const std::vector<unsigned char>* pixelVector;
    const unsigned char label;
public:
    Image(const std::vector<unsigned char> *pixelVector, unsigned char label);
    int checkLabel(int value);

public:
    [[nodiscard]] const std::vector<unsigned char> * getPixelVector() const;
    [[nodiscard]] unsigned char getLabel() const;
};


#endif //CNN_IMAGE_H
