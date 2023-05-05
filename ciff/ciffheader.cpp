#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ciffheader.h"

using namespace std;

CiffHeader::CiffHeader() = default;

std::string CiffHeader::getMagic() const { return magic; }
void CiffHeader::setMagic(std::string s) { magic = s; }

::uint64_t CiffHeader::getHeaderSize() const { return header_size; }
void CiffHeader::setHeaderSize(::uint64_t s) { header_size = s; }

::uint64_t CiffHeader::getContentSize() const { return content_size; }
void CiffHeader::setContentSize(::uint64_t s) { content_size = s; }

::uint64_t CiffHeader::getWidth() const { return width; }
void CiffHeader::setWidth(::uint64_t s) { width = s; }

::uint64_t CiffHeader::getHeight() const { return height; }
void CiffHeader::setHeight(::uint64_t s) { height = s; }

std::string CiffHeader::getCaption() const { return caption; }
void CiffHeader::setCaption(std::string s) { caption = s; }

std::vector<std::string> CiffHeader::getTags() const { return tags; }
void CiffHeader::setTags(std::vector<std::string> v) { tags = v; }

void CiffHeader::toString() {
    std::cout << "\n###HEADER###\n" << std::endl;
    std::cout << "Magic: " << getMagic() << std::endl;
    std::cout << "Header size: " << getHeaderSize() << std::endl;
    std::cout << "Content size: " << getContentSize() << std::endl;
    std::cout << "Width: " << getWidth() << std::endl;
    std::cout << "Height: " << getHeight() << std::endl;
    std::cout << "Caption: " << getCaption() << std::endl;
    std::cout << "Tags: ";
    for(const auto& tag : getTags()) {
        std::cout << tag << " ";
    }
    std::cout << std::endl;
}

CiffHeader readCiffHeader(std::ifstream& file) {
    CiffHeader header;
    char magic[5];
    if (!file.read(magic, 4) || std::string(magic, 4) != "CIFF") {
        //TODO: error handling
    }
    header.setMagic(std::string(magic, 4));
    ::uint64_t header_size;
    if (!file.read(reinterpret_cast<char*>(&header_size), sizeof(header_size))) {
        //TODO: error handling
    }
    header.setHeaderSize(header_size);
    ::uint64_t content_size;
    if (!file.read(reinterpret_cast<char*>(&content_size), sizeof(content_size))) {
        //TODO: error handling
    }
    header.setContentSize(content_size);
    ::uint64_t width;
    if (!file.read(reinterpret_cast<char*>(&width), sizeof(width))) {
        //TODO: error handling
    }
    header.setWidth(width);
    ::uint64_t height;
    if (!file.read(reinterpret_cast<char*>(&height), sizeof(height))) {
        //TODO: error handling
    }
    header.setHeight(height);
    std::string captionTmp = header.getCaption();
    std::getline(file, captionTmp, '\n');
    if (captionTmp.back() == '\n') {
        captionTmp.pop_back();
    }
    header.setCaption(captionTmp);

    std::size_t tagsSize = header.getHeaderSize() - 4 - 8 - 8 - 8 - 8 - header.getCaption().size() - 1;
    std::vector<char> buffer(tagsSize);
    file.read(buffer.data(), tagsSize);
    std::string tagsString(buffer.begin(), buffer.end());
    std::stringstream tagsStream(tagsString);
    std::string tag;
    std::vector<std::string> tags;
    while (std::getline(tagsStream, tag, '\0')) {
        tags.push_back(tag);
    }
    header.setTags(tags);
    return header;
}
