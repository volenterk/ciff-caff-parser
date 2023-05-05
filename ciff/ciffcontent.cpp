#include <vector>
#include <fstream>
#include <iomanip>
#include "ciffcontent.h"

using namespace std;


CiffContent::CiffContent() = default;
//CiffContent::~CiffContent() {}

::uint64_t CiffContent::getWidth() const { return width; }
void CiffContent::setWidth(::uint64_t w) { width = w; }

::uint64_t CiffContent::getHeight() const { return height; }
void CiffContent::setHeight(::uint64_t h) { height = h; }

std::vector<::uint8_t> CiffContent::getPixels() const { return pixels; }
void CiffContent::setPixels(std::vector<::uint8_t> ps) { pixels = ps; }

::uint64_t CiffContent::getContentSize() const { return contentSize; }
void CiffContent::setContentSize(::uint64_t cs) { contentSize = cs; }

void CiffContent::toString() {
    std::cout << "\n###CONTENT###\n" << std::endl;
    std::cout << "Content size: " << getContentSize() << std::endl;
    std::cout << "Width: " << getWidth() << std::endl;
    std::cout << "Height: " << getHeight() << std::endl;
    std::cout << "Content: ";
    for(const auto& px : getPixels()) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(px) << " ";
    }
    std::cout << std::endl;
}

CiffContent readCiffContent(std::ifstream& file, ::uint64_t cs, ::uint64_t h, ::uint64_t w) {
    CiffContent content;
    content.setHeight(h);
    content.setWidth(w);
    content.setContentSize(cs);
    content.setPixels(std::vector<std::uint8_t>(content.getContentSize()));

    std::vector<::uint8_t> tmpPixels;
    tmpPixels.resize(content.getContentSize());
    if(file.is_open()) {
        if(!file.read(reinterpret_cast<char*>(tmpPixels.data()), content.getContentSize())) {
            //TODO: error handling
            std::cout << "Error" << std::endl;
        }
    } else {
        //TODO: error handling
        std::cout << "File not open" << std::endl;
    }
    content.setPixels(tmpPixels);
    return content;
}