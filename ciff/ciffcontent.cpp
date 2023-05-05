#include <vector>
#include <fstream>
#include <iomanip>
#include "ciffcontent.h"
#include "ciffheader.h"
#include <iostream>

using namespace std;

CiffContent::CiffContent(std::ifstream& file, CiffHeader header) {
    height = header.getHeight();
    width = header.getWidth();
    contentSize = header.getContentSize();
    pixels = std::vector<std::uint8_t>(contentSize);

    std::vector<::uint8_t> tmpPixels;
    tmpPixels.resize(getContentSize());
    if(file.is_open()) {
        if(!file.read(reinterpret_cast<char*>(tmpPixels.data()), contentSize)) {
            //TODO: error handling
            std::cout << "Error" << std::endl;
        }
    } else {
        //TODO: error handling
        std::cout << "File not open" << std::endl;
    }
    pixels = tmpPixels;
}

std::vector<::uint8_t> CiffContent::getPixels() const { return pixels; }

::uint64_t CiffContent::getContentSize() const { return contentSize; }

void CiffContent::toString() {
    std::cout << "\n###CONTENT###\n" << std::endl;
    std::cout << "Content size: " << contentSize << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Content: ";
    for(const auto& px : pixels) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(px) << " ";
    }
    std::cout << std::endl;
}