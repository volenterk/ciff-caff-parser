#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ciffheader.h"
#include <endian.h>

using namespace std;

CiffHeader::CiffHeader(std::ifstream& file) {
    //Check for magic
    this->magic = "CIFF";
    char magicTmp[5];
    if(!file.read(magicTmp, 4) || std::string(magicTmp, 4) != this->magic) {
        throw std::runtime_error("Invalid CIFF magic number!");
    }
    this->magic = std::string(magicTmp, 4);

    //Check for header size
    ::uint64_t headerSizeTmp;
    if(!file.read(reinterpret_cast<char*>(&headerSizeTmp), sizeof(headerSizeTmp))) {
        throw std::runtime_error("Error reading header size!");
    }
    this->headerSize = headerSizeTmp;

    ::uint64_t contentSizeTmp;
    if(!file.read(reinterpret_cast<char*>(&contentSizeTmp), sizeof(contentSizeTmp))) {
        throw std::runtime_error("Error reading content size!");
    }
    if(this->headerSize > contentSizeTmp) {
        throw std::out_of_range("Header size is too big! Possible cause: your provided file has big-endian values.");
    }
    this->contentSize = contentSizeTmp;

    ::uint64_t widthTmp;
    if(!file.read(reinterpret_cast<char*>(&widthTmp), sizeof(widthTmp))) {
        throw std::runtime_error("Error reading width!");
    }
    this->width = widthTmp;

    ::uint64_t heightTmp;
    if(!file.read(reinterpret_cast<char*>(&heightTmp), sizeof(heightTmp))) {
        throw std::runtime_error("Error reading height!");
    }
    this->height = heightTmp;

    if(this->width * this->height * 3 != this->contentSize) {
        throw std::out_of_range("The relation between width, height and content size is not satisfied!");
    }

    std::string captionTmp;
    std::getline(file, captionTmp, '\n');
    if(captionTmp.back() == '\n') {
        captionTmp.pop_back();
    }
    if(captionTmp.find('\n') != std::string::npos) {
        throw std::runtime_error("Caption contains newline character!");
    }
    this->caption = captionTmp;
    std::size_t tagsSize = this->headerSize - 4 - 8 - 8 - 8 - 8 - this->caption.size() - 1;
    std::vector<char> buffer(tagsSize);
    if(!file.read(buffer.data(), tagsSize)) {
        throw std::runtime_error("Error reading tags!");
    }
    std::string tagsString(buffer.begin(), buffer.end());
    if(tagsString.back() != '\0') {
        throw std::runtime_error("Tags dont end with zero byte!");
    }
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
