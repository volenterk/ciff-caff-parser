#ifndef CIFF_CAFF_PARSER_CIFFHEADER_H
#define CIFF_CAFF_PARSER_CIFFHEADER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class CiffHeader {
public:
    CiffHeader();

    std::string getMagic() const;
    void setMagic(std::string s);

    ::uint64_t getHeaderSize() const;
    void setHeaderSize(::uint64_t s);

    ::uint64_t getContentSize() const;
    void setContentSize(::uint64_t s);

    ::uint64_t getWidth() const;
    void setWidth(::uint64_t s);

    ::uint64_t getHeight() const;
    void setHeight(::uint64_t s);

    std::string getCaption() const;
    void setCaption(std::string s);

    std::vector<std::string> getTags() const;
    void setTags(std::vector<std::string> v);

    void toString();
private:
    std::string caption;
    std::string magic;
    ::uint64_t header_size{};
    ::uint64_t content_size{};
    ::uint64_t width{};
    ::uint64_t height{};
    std::vector<std::string> tags;
};

CiffHeader readCiffHeader(std::ifstream& file);

#endif //CIFF_CAFF_PARSER_CIFFHEADER_H
