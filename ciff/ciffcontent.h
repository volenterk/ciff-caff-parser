#ifndef CIFF_CAFF_PARSER_CIFFCONTENT_H
#define CIFF_CAFF_PARSER_CIFFCONTENT_H

#include <vector>
#include <fstream>

using namespace std;

class CiffContent {
public:
    CiffContent();
    //~CiffContent();

    ::uint64_t getWidth() const;
    void setWidth(::uint64_t w);

    ::uint64_t getHeight() const;
    void setHeight(::uint64_t h);

    std::vector<::uint8_t> getPixels() const;
    void setPixels(std::vector<::uint8_t> ps);

    ::uint64_t getContentSize() const;
    void setContentSize(::uint64_t cs);

    void toString();
private:
    ::uint64_t width;
    ::uint64_t height;
    ::uint64_t contentSize;
    std::vector<::uint8_t> pixels;
};

CiffContent readCiffContent(std::ifstream& file, ::uint64_t cs, ::uint64_t h, ::uint64_t w);

#endif //CIFF_CAFF_PARSER_CIFFCONTENT_H
