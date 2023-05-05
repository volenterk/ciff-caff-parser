#ifndef CIFF_CAFF_PARSER_CIFFCONTENT_H
#define CIFF_CAFF_PARSER_CIFFCONTENT_H

#include <vector>
#include <fstream>
#include "ciffheader.h"

using namespace std;

class CiffContent {
public:
    CiffContent(std::ifstream& file, CiffHeader header);

    std::vector<::uint8_t> getPixels() const;

    ::uint64_t getContentSize() const;

    void toString();
private:
    ::uint64_t width;
    ::uint64_t height;
    ::uint64_t contentSize;
    std::vector<::uint8_t> pixels;
};

#endif //CIFF_CAFF_PARSER_CIFFCONTENT_H
