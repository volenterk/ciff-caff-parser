#ifndef CIFF_CAFF_PARSER_FINAL_CIFFFILE_H
#define CIFF_CAFF_PARSER_FINAL_CIFFFILE_H

#include <fstream>
#include <vector>

using namespace std;

class CiffHeader {
public:
    CiffHeader(ifstream& file);

    uint64_t getContentSize() const;
    uint64_t getWidth() const;
    uint64_t getHeight() const;
    string getCaption() const;
    vector<string> getTags() const;

    void toString();

private:
    string caption;
    string magic;
    uint64_t headerSize;
    uint64_t contentSize;
    uint64_t width;
    uint64_t height;
    vector<string> tags;
};

class CiffContent {
public:
    CiffContent(ifstream& file, const CiffHeader& header);

    vector<uint8_t> getPixels() const;
    uint64_t getContentSize() const;

    void toString();

private:
    uint64_t width;
    uint64_t height;
    uint64_t contentSize;
    vector<uint8_t> pixels;
};

class CiffFile {
public:
    explicit CiffFile(ifstream& file)  : header(file), content(file, header) {}

    CiffHeader& getHeader();
    CiffContent& getContent();

    vector<uint8_t> makePreview();
    void toString();

private:
    CiffHeader header;
    CiffContent content;
};

#endif //CIFF_CAFF_PARSER_FINAL_CIFFFILE_H
