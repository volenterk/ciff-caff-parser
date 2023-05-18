#ifndef CIFF_CAFF_PARSER_CAFFFILE_H
#define CIFF_CAFF_PARSER_CAFFFILE_H

#include <fstream>
#include <vector>
#include <memory>
#include "cifffile.h"

using namespace std;

class CaffHeader {
public:
    CaffHeader() : magic("CAFF"), headerSize(0), numAnim(0) {}
    explicit CaffHeader(ifstream& file);

    //void toString();

private:
    string magic;
    uint64_t headerSize;
    uint64_t numAnim;
};

class CaffCredits {
public:
    CaffCredits() : year(0), month(0), day(0), hour(0), minute(0), creatorLen(0) {}
    explicit CaffCredits(ifstream& file);

    //void toString();

private:
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint64_t creatorLen;
    string creator;
};

class CaffAnimation {
public:
    CaffAnimation() : duration(0), ciff() {}
    explicit CaffAnimation(ifstream& file);

    CiffFile getCiff() {
        return ciff;
    }

    //void toString();

private:
    uint64_t duration;
    CiffFile ciff;
};

class CaffFile {
public:
    explicit CaffFile(ifstream& file) : file(file), header(), credits(), animations() {
        parseCaff();
    }

    void parseCaff();
    void parseAnimations();

    vector<uint8_t> makePreview();
    //void toString();

private:
    ifstream& file;
    CaffHeader header;
    CaffCredits credits;
    vector<CaffAnimation> animations;
};


#endif //CIFF_CAFF_PARSER_CAFFFILE_H
