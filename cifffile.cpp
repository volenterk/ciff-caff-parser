#include "cifffile.h"
#include <webp/encode.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

CiffHeader& CiffFile::getHeader() { return header; }

CiffContent& CiffFile::getContent() { return content; }

vector<uint8_t> CiffFile::makePreview() {
    vector<uint8_t> output;
    uint8_t* webpData = nullptr;
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

CiffHeader::CiffHeader(ifstream& file) {
    //Check for magic
    this->magic = "CIFF";
    char magicTmp[5];
    if(!file.read(magicTmp, 4) || string(magicTmp, 4) != this->magic) {
        throw runtime_error("Invalid CIFF magic number!");
    }
    this->magic = string(magicTmp, 4);

    //Check for header size
    uint64_t headerSizeTmp;
    if(!file.read(reinterpret_cast<char*>(&headerSizeTmp), sizeof(headerSizeTmp))) {
        throw runtime_error("Error reading header size!");
    }
    this->headerSize = headerSizeTmp;

    uint64_t contentSizeTmp;
    if(!file.read(reinterpret_cast<char*>(&contentSizeTmp), sizeof(contentSizeTmp))) {
        throw runtime_error("Error reading content size!");
    }
    if(this->headerSize > contentSizeTmp) {
        throw out_of_range("Header size is too big! Possible cause: your provided file has big-endian values.");
    }
    this->contentSize = contentSizeTmp;

    uint64_t widthTmp;
    if(!file.read(reinterpret_cast<char*>(&widthTmp), sizeof(widthTmp))) {
        throw runtime_error("Error reading width!");
    }
    this->width = widthTmp;

    uint64_t heightTmp;
    if(!file.read(reinterpret_cast<char*>(&heightTmp), sizeof(heightTmp))) {
        throw runtime_error("Error reading height!");
    }
    this->height = heightTmp;

    if(this->width * this->height * 3 != this->contentSize) {
        throw out_of_range("The relation between width, height and content size is not satisfied!");
    }

    string captionTmp;
    getline(file, captionTmp, '\n');
    if(captionTmp.back() == '\n') {
        captionTmp.pop_back();
    }
    if(captionTmp.find('\n') != string::npos) {
        throw runtime_error("Caption contains newline character!");
    }
    this->caption = captionTmp;
    size_t tagsSize = this->headerSize - 4 - 8 - 8 - 8 - 8 - this->caption.size() - 1;
    vector<char> buffer(tagsSize);
    if(!file.read(buffer.data(), tagsSize)) {
        throw runtime_error("Error reading tags!");
    }
    string tagsString(buffer.begin(), buffer.end());
    if(tagsString.back() != '\0') {
        throw runtime_error("Tags dont end with zero byte!");
    }
    stringstream tagsStream(tagsString);
    string tag;
    vector<string> tagsTmp;
    while(getline(tagsStream, tag, '\0')) {
        tagsTmp.push_back(tag);
    }
    this->tags = tagsTmp;
};

uint64_t CiffHeader::getContentSize() const { return contentSize; }
uint64_t CiffHeader::getWidth() const { return width; }
uint64_t CiffHeader::getHeight() const { return height; }
string CiffHeader::getCaption() const { return caption; }
vector<string> CiffHeader::getTags() const { return tags; }

void CiffHeader::toString() {
    cout << "\n###HEADER###\n" << endl;
    cout << "Magic: " << magic << endl;
    cout << "Header size: " << headerSize << endl;
    cout << "Content size: " << contentSize << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << "Caption: " << caption << endl;
    cout << "Tags: ";
    for(const auto& tag : tags) {
        cout << tag << " ";
    }
    cout << endl;
}

CiffContent::CiffContent(ifstream& file, const CiffHeader& header) {
    height = header.getHeight();
    width = header.getWidth();
    contentSize = header.getContentSize();
    pixels = vector<uint8_t>(contentSize);

    vector<uint8_t> tmpPixels;
    tmpPixels.resize(getContentSize());
    if(file.is_open()) {
        if(!file.read(reinterpret_cast<char*>(tmpPixels.data()), contentSize)) {
            //TODO: error handling
            cout << "Error" << endl;
        }
    } else {
        //TODO: error handling
        cout << "File not open" << endl;
    }
    pixels = tmpPixels;
}

vector<uint8_t> CiffContent::getPixels() const { return pixels; }

uint64_t CiffContent::getContentSize() const { return contentSize; }

void CiffContent::toString() {
    cout << "\n###CONTENT###\n" << endl;
    cout << "Content size: " << contentSize << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << "Content: ";
    for(const auto& px : pixels) {
        cout << setw(2) << setfill('0') << hex << static_cast<int>(px) << " ";
    }
    cout << endl;
}