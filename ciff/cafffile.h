#ifndef CIFF_CAFF_PARSER_CAFFFILE_H
#define CIFF_CAFF_PARSER_CAFFFILE_H

#include <fstream>
#include <vector>
#include "cifffile.h"

using namespace std;

class CaffBlock {
public:
    explicit CaffBlock(ifstream& file);

    uint8_t getId() const;
    uint64_t getLength() const;
    const vector<uint8_t>& getData() const;

private:
    uint8_t id;
    uint64_t length;
    vector<uint8_t> data;
};

class CaffHeader {
public:
    explicit CaffHeader(ifstream& file);

    const string getMagic() const;
    uint64_t getHeaderSize() const;
    uint64_t getNumAnim() const;

private:
    string magic;
    uint64_t headerSize;
    uint64_t numAnim;
};

class CaffCredits {
public:
    explicit CaffCredits(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint64_t creatorLen, const string& creator)
    : year(year), month(month), day(day), hour(hour), minute(minute), creatorLen(creatorLen), creator(creator) {}

    uint16_t getYear() const;
    uint8_t getMonth() const;
    uint8_t getDay() const;
    uint8_t getHour() const;
    uint8_t getMinute() const;
    uint64_t getCreatorLen() const;
    string getCreator() const;

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
    explicit CaffAnimation(uint64_t duration, CiffFile& ciff) : duration(duration), ciff(ciff) {}

    uint64_t getDuration() const;
    CiffFile getCiff() const;

private:
    uint64_t duration;
    CiffFile ciff;
};

class CaffFile {
public:
    CaffFile(ifstream& file);

    void toString();

private:
    vector<CaffBlock> blocks;
    CaffCredits credits;
    CaffAnimation animations;
};


#endif //CIFF_CAFF_PARSER_CAFFFILE_H
