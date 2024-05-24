//
// Created by janek on 5/22/2024.
//

#ifndef CNN_IMAGE_H
#define CNN_IMAGE_H

#include <vector>
class Image {
private:
    const std::vector<int>* pixelVector;
    const int label;
public:
    Image(const std::vector<int> *pixelVector, int label);
    int checkLabel(int value);

public:
    const std::vector<int> * getPixelVector() const;

    const int getLabel() const;
};


#endif //CNN_IMAGE_H
