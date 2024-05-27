//
// Created by janek on 5/27/2024.
//

#ifndef CNN_PARSER_H
#define CNN_PARSER_H
#include <vector>
#include "Image.h"

class Parser {
public:
    Parser();
    std::vector<Image*>* processFile(const char* filepath, const char *labelFilepath);

private:
    [[nodiscard]] std::vector<unsigned char>* read(const char* path);
    struct Flags{
        int dimX,dimY, count;
        Flags(int dimX, int dimY, int count) : dimX(dimX), dimY(dimY), count(count) {}
    };
    Flags getFlags(std::vector<unsigned char>* raw);
    std::vector<Image*>* createImages(std::vector<unsigned char>* raw, std::vector<unsigned char> *labels,  Flags flag);
};


#endif //CNN_PARSER_H
