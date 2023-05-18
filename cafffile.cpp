#include "cafffile.h"
#include <iostream>

using namespace std;

CaffHeader::CaffHeader(ifstream& file) {
    this->magic = "CAFF";
    char magicTmp[5];
    if (!file.read(magicTmp, 4) || string(magicTmp, 4) != this->magic) {
        throw runtime_error("Invalid CAFF header magic number!");
    }
    this->magic = string(magicTmp, 4);

    uint64_t headerSizeTmp;
    if (!file.read(reinterpret_cast<char*>(&headerSizeTmp), sizeof(headerSizeTmp))) {
        throw runtime_error("Error reading header size in CAFF header!");
    }
    if (headerSizeTmp != 4 + 8 + 8) {
        throw runtime_error("The header size should be 20 bytes for a CAFF file");
    }
    this->headerSize = headerSizeTmp;

    uint64_t numAnimTmp;
    if(!file.read(reinterpret_cast<char*>(&numAnimTmp), sizeof(numAnimTmp))) {
        throw runtime_error("Error reading number of animation blocks in CAFF header");
    }
    this->numAnim = numAnimTmp;
}

CaffCredits::CaffCredits(ifstream& file) {
    uint16_t yearTmp;
    if(!file.read(reinterpret_cast<char*>(&yearTmp), sizeof(yearTmp))) {
        throw runtime_error("Error reading year in CAFF credits block!");
    }
    this->year = yearTmp;

    uint8_t monthTmp;
    if(!file.read(reinterpret_cast<char*>(&monthTmp), sizeof(monthTmp))) {
        throw runtime_error("Error reading month in CAFF credits block!");
    }
    this->month = monthTmp;

    uint8_t dayTmp;
    if(!file.read(reinterpret_cast<char*>(&dayTmp), sizeof(dayTmp))) {
        throw runtime_error("Error reading day in CAFF credits block!");
    }
    this->day = dayTmp;

    uint8_t hourTmp;
    if(!file.read(reinterpret_cast<char*>(&hourTmp), sizeof(hourTmp))) {
        throw runtime_error("Error reading hour in CAFF credits block!");
    }
    this->hour = hourTmp;

    uint8_t minuteTmp;
    if(!file.read(reinterpret_cast<char*>(&minuteTmp), sizeof(minuteTmp))) {
        throw runtime_error("Error reading minute in CAFF credits block!");
    }
    this->minute = minuteTmp;

    uint64_t creatorLengthTmp;
    if(!file.read(reinterpret_cast<char*>(&creatorLengthTmp), sizeof(creatorLengthTmp))) {
        throw runtime_error("Error reading creator length in CAFF credits block!");
    }
    this->creatorLen = creatorLengthTmp;

    vector<char> buffer(this->creatorLen);
    if (!file.read(buffer.data(), this->creatorLen)) {
        throw runtime_error("Error reading creator in CAFF credits block!");
    }
    string creatorTmp(buffer.data(), this->creatorLen);
    this->creator = creatorTmp;
}

CaffAnimation::CaffAnimation(ifstream& file) {
    uint64_t durationTmp;
    if (!file.read(reinterpret_cast<char*>(&durationTmp), sizeof(durationTmp))) {
        throw runtime_error("Error while reading duration of the animation!");
    }
    this->duration = durationTmp;

    this->ciff = CiffFile(file);
}

void CaffFile::parseCaff() {
    uint8_t id;
    if (!file.read(reinterpret_cast<char*>(&id), sizeof(id))) {
        throw runtime_error("Invalid CAFF block id!");
    }

    uint64_t length;
    if (!file.read(reinterpret_cast<char*>(&length), sizeof(length))) {
        throw runtime_error("Invalid CAFF block length!");
    }

    if (id != 0x1) {
        throw runtime_error("The CAFF file should start with a header block");
    } else {
        this->header = CaffHeader(file);
    }

    if (!file.read(reinterpret_cast<char*>(&id), sizeof(id))) {
        throw runtime_error("Invalid CAFF block id!");
    }

    if (!file.read(reinterpret_cast<char*>(&length), sizeof(length))) {
        throw runtime_error("Invalid CAFF block length!");
    }

    if (id != 0x2) {
        throw runtime_error("The second block in a CAFF file should be credits");
    } else {
        this->credits = CaffCredits(file);
    }

    parseAnimations();
}

void CaffFile::parseAnimations() {
    while (true) {
        uint8_t id;
        if (!file.read(reinterpret_cast<char*>(&id), sizeof(id))) {
            if (file.eof()) {
                break;
            } else {
                throw runtime_error("Invalid CAFF block id");
            }
        }

        uint64_t length;
        if (!file.read(reinterpret_cast<char*>(&length), sizeof(length))) {
            throw runtime_error("Invalid CAFF block length!");
        }

        if (id != 0x3) {
            throw runtime_error("The CAFF file should contain only animation blocks after header and credits blocks!");
        } else {
            this->animations.push_back(CaffAnimation(file));
        }
    }
}

vector<uint8_t> CaffFile::makePreview() {
    return animations[0].getCiff().makePreview();
}