#ifndef CIFF_CAFF_PARSER_FINAL_CIFFFILE_H
#define CIFF_CAFF_PARSER_FINAL_CIFFFILE_H

#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class CiffHeader {
public:
    CiffHeader() : headerSize(0), contentSize(0), width(0), height(0), tags() {}
    explicit CiffHeader(ifstream& file);

    uint64_t getContentSize() const {
        return contentSize;
    }
    uint64_t getWidth() const {
        return width;
    }
    uint64_t getHeight() const {
        return height;
    }

    void toString() const {
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

private:
    string caption;
    string magic;
    uint64_t headerSize{};
    uint64_t contentSize{};
    uint64_t width{};
    uint64_t height{};
    vector<string> tags;
};

class CiffContent {
public:
    CiffContent() : width(0), height(0), contentSize(0), pixels() {}
    CiffContent(ifstream& file, const CiffHeader& header);

    vector<uint8_t> getPixels() const {
        return pixels;
    }
    uint64_t getContentSize() const {
        return contentSize;
    }

    void toString() const {
        cout << "\n###CONTENT###\n" << endl;
        cout << "Content size: " << contentSize << endl;
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
        cout << "Content: ";
        int counter = 0;
        for(const auto& px : pixels) {
            cout << setw(2) << setfill('0') << hex << static_cast<int>(px) << " ";
            counter++;
            if (counter >= 50) {
                break;
            }
        }
        cout << "..." << endl;
    }

private:
    uint64_t width;
    uint64_t height;
    uint64_t contentSize;
    vector<uint8_t> pixels;
};

class CiffFile {
public:
    CiffFile() : header(), content() {}
    explicit CiffFile(ifstream& file)  : header(file), content(file, header) {}

    vector<uint8_t> makePreview();
    void toString() const {
        header.toString();
        content.toString();
    }

private:
    CiffHeader header;
    CiffContent content;
};

#endif //CIFF_CAFF_PARSER_FINAL_CIFFFILE_H
