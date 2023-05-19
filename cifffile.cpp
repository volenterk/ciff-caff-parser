#include "cifffile.h"
#include <webp/encode.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

vector<uint8_t> CiffFile::makePreview() {
    vector<uint8_t> output;
    uint8_t* webpData = nullptr;
    size_t webpSize = WebPEncodeLosslessRGB(
            content.getPixels().data(),
            (int)header.getWidth(),
            (int)header.getHeight(),
            (int)header.getWidth() * 3,
            &webpData
    );
    if (webpData != nullptr && webpSize != 0) {
        output.assign(webpData, webpData + webpSize);
        WebPFree(webpData);
    }
    return output;
}

CiffHeader::CiffHeader(ifstream& file) {
    char magicTmp[5];
    if (!file.read(magicTmp, 4) || string(magicTmp, 4) != "CIFF") {
        throw runtime_error("Invalid CIFF magic number!");
    }
    magic = string(magicTmp, 4);

    if (!file.read(reinterpret_cast<char*>(&headerSize), sizeof(headerSize))) {
        throw runtime_error("Error reading header size!");
    }

    if (!file.read(reinterpret_cast<char*>(&contentSize), sizeof(contentSize))) {
        throw runtime_error("Error reading content size!");
    }
    if (headerSize > contentSize) {
        throw out_of_range("Header size is too big! Possible cause: your provided file has big-endian values.");
    }

    if (!file.read(reinterpret_cast<char*>(&width), sizeof(width))) {
        throw runtime_error("Error reading width!");
    }

    if (!file.read(reinterpret_cast<char*>(&height), sizeof(height))) {
        throw runtime_error("Error reading height!");
    }

    if (width * height * 3 != contentSize) {
        throw out_of_range("The relation between width, height and content size is not satisfied!");
    }

    string captionTmp;
    getline(file, captionTmp, '\n');
    if (captionTmp.back() == '\n') {
        captionTmp.pop_back();
    }
    if (captionTmp.find('\n') != string::npos) {
        throw runtime_error("Caption contains newline character!");
    }
    caption = captionTmp;
    size_t tagsSize = headerSize - 4 - 8 - 8 - 8 - 8 - caption.size() - 1;
    vector<char> buffer(tagsSize);
    if (!file.read(buffer.data(), tagsSize)) {
        throw runtime_error("Error reading tags!");
    }
    string tagsString(buffer.begin(), buffer.end());
    if (tagsString.back() != '\0') {
        throw runtime_error("Tags dont end with zero byte!");
    }
    stringstream tagsStream(tagsString);
    string tag;
    vector<string> tagsTmp;
    while (getline(tagsStream, tag, '\0')) {
        tagsTmp.push_back(tag);
    }
    tags = tagsTmp;
};

CiffContent::CiffContent(ifstream& file, const CiffHeader& header) {
    height = header.getHeight();
    width = header.getWidth();
    contentSize = header.getContentSize();
    pixels = vector<uint8_t>(contentSize);

    vector<uint8_t> tmpPixels;
    tmpPixels.resize(getContentSize());
    if(!file.read(reinterpret_cast<char*>(tmpPixels.data()), contentSize)) {
        throw runtime_error("Error reading content from the file!");
    }

    pixels = tmpPixels;
}