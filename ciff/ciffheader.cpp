#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ciffheader.h"

using namespace std;

CiffHeader::CiffHeader(std::ifstream& file) {
    char magicTmp[5];
    if(!file.read(magicTmp, 4) || std::string(magic, 4) != "CIFF") {
        //TODO: error handling
    }
    this->magic = std::string(magicTmp, 4);

    ::uint64_t headerSizeTmp;
    if(!file.read(reinterpret_cast<char*>(&headerSizeTmp), sizeof(headerSizeTmp))) {
        //TODO: error handling
    }
    this->headerSize = headerSizeTmp;

    ::uint64_t contentSizeTmp;
    if(!file.read(reinterpret_cast<char*>(&contentSizeTmp), sizeof(contentSizeTmp))) {
        //TODO: error handling
    }
    this->contentSize = contentSizeTmp;

    ::uint64_t widthTmp;
    if(!file.read(reinterpret_cast<char*>(&widthTmp), sizeof(widthTmp))) {
        //TODO: error handling
    }
    this->width = widthTmp;

    ::uint64_t heightTmp;
    if(!file.read(reinterpret_cast<char*>(&heightTmp), sizeof(heightTmp))) {
        //TODO: error handling
    }
    this->height = heightTmp;

    std::string captionTmp;
    std::getline(file, captionTmp, '\n');
    if(captionTmp.back() == '\n') {
        captionTmp.pop_back();
    }
    this->caption = captionTmp;

    std::size_t tagsSize = this->headerSize - 4 - 8 - 8 - 8 - 8 - this->caption.size() - 1;
    std::vector<char> buffer(tagsSize);
    file.read(buffer.data(), tagsSize);
    std::string tagsString(buffer.begin(), buffer.end());

    std::stringstream tagsStream(tagsString);
    std::string tag;
    std::vector<std::string> tagsTmp;
    while(std::getline(tagsStream, tag, '\0')) {
        tagsTmp.push_back(tag);
    }
    this->tags = tagsTmp;
};

::uint64_t CiffHeader::getContentSize() const { return contentSize; }
::uint64_t CiffHeader::getWidth() const { return width; }
::uint64_t CiffHeader::getHeight() const { return height; }
std::string CiffHeader::getCaption() const { return caption; }
std::vector<std::string> CiffHeader::getTags() const { return tags; }

void CiffHeader::toString() {
    std::cout << "\n###HEADER###\n" << std::endl;
    std::cout << "Magic: " << magic << std::endl;
    std::cout << "Header size: " << headerSize << std::endl;
    std::cout << "Content size: " << contentSize << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Caption: " << caption << std::endl;
    std::cout << "Tags: ";
    for(const auto& tag : tags) {
        std::cout << tag << " ";
    }
    std::cout << std::endl;
}
