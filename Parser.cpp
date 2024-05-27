//
// Created by janek on 5/27/2024.
//

#include "Parser.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>

Parser::Parser() {}

std::vector<Image *> *Parser::processFile(const char *imageFilepath, const char *labelFilepath) {
    std::vector<unsigned char>* raw = read(imageFilepath);
    std::vector<unsigned char>* labels = read(labelFilepath);
    if(raw == nullptr || labels == nullptr){
        perror("failed to read training data");
        std::exit(EXIT_FAILURE);
    }
    Flags flags = getFlags(raw);
    auto *images = createImages(raw, labels, flags);
    delete raw;
    delete labels;
    return images;
}

std::vector<unsigned char> *Parser::read(const char *path) {
    std::ifstream file(path, std::ios::binary);
    if (!file){
        file.close();
        perror("failed to open file");
        return nullptr;
    }
    auto * buffer = new std::vector<unsigned char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return buffer;
}

Parser::Flags Parser::getFlags(std::vector<unsigned char>* raw) {
    std::vector<unsigned char> rawBytes = *raw;
    int imageCount = rawBytes.at(4) * std::pow(256,3) + rawBytes.at(5) * std::pow(256,2) + rawBytes.at(6) * std::pow(256,1) + rawBytes.at(7);
    int dimX = rawBytes.at(8) * std::pow(256,3) + rawBytes.at(9) * std::pow(256,2) + rawBytes.at(10) * std::pow(256,1) + rawBytes.at(11);
    int dimY = rawBytes.at(12) * std::pow(256,3) + rawBytes.at(13) * std::pow(256,2) + rawBytes.at(14) * std::pow(256,1) + rawBytes.at(15);
    return {dimX, dimY, imageCount};
}

std::vector<Image*> *Parser::createImages(std::vector<unsigned char> *raw, std::vector<unsigned char> *labels, Parser::Flags flag) {
    std::vector<unsigned char> rawBytes = *raw;
    std::vector<unsigned char> labelVec = *labels;
    auto *images = new std::vector<Image*>(flag.count);
    int pixelCount = flag.dimX*flag.dimY;
    int insertIndex = 0;
    for (size_t i = 16; i < rawBytes.size(); i+=pixelCount) {
        images->at(insertIndex) =new Image(new std::vector<unsigned char >(rawBytes.begin() + i, rawBytes.begin() + i + pixelCount),labelVec.at(insertIndex));
        insertIndex++;
    }
    return images;
}
