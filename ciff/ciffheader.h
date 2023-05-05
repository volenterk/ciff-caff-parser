#ifndef CIFF_CAFF_PARSER_CIFFHEADER_H
#define CIFF_CAFF_PARSER_CIFFHEADER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class CiffHeader {
public:
    CiffHeader(std::ifstream& file);

    ::uint64_t getContentSize() const;

    ::uint64_t getWidth() const;

    ::uint64_t getHeight() const;

    std::string getCaption() const;

    std::vector<std::string> getTags() const;

    void toString();
private:
    std::string caption;
    std::string magic;
    ::uint64_t headerSize;
    ::uint64_t contentSize;
    ::uint64_t width;
    ::uint64_t height;
    std::vector<std::string> tags;
};

#endif //CIFF_CAFF_PARSER_CIFFHEADER_H
