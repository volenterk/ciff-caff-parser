#ifndef CIFF_CAFF_PARSER_FINAL_CIFFFILE_H
#define CIFF_CAFF_PARSER_FINAL_CIFFFILE_H

#include "ciffheader.h"
#include "ciffcontent.h"

using namespace std;

class CiffFile {
public:
    explicit CiffFile(std::ifstream& file)  : header(file), content(file, header) {}

    CiffHeader& getHeader();

    CiffContent& getContent();

    std::vector<::uint8_t> makePreview();

    void toString();
private:
    CiffHeader header;
    CiffContent content;
};

#endif //CIFF_CAFF_PARSER_FINAL_CIFFFILE_H
