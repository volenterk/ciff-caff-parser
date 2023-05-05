#include "cifffile.h"
#include "ciffheader.h"
#include "ciffcontent.h"
#include <webp/encode.h>
#include <webp/mux.h>

using namespace std;

CiffHeader& CiffFile::getHeader() { return header; }

CiffContent& CiffFile::getContent() { return content; }

std::vector<::uint8_t> CiffFile::makePreview() {
    std::vector<::uint8_t> output;
    ::uint8_t* webpData = nullptr;
    size_t webpSize = WebPEncodeLosslessRGB(content.getPixels().data(), (int)header.getWidth(), (int)header.getHeight(), (int)header.getWidth() * 3, &webpData);
    if(webpSize) {
        output.assign(webpData, webpData + webpSize);
        free(webpData);
    }
    return output;
}

void CiffFile::toString() {
    header.toString();
    content.toString();
}

