#include "cafffile.h"

using namespace std;

CaffBlock::CaffBlock(ifstream& file) {
    uint8_t idTmp;
    if (!file.read(reinterpret_cast<char*>(&idTmp), sizeof(idTmp))) {
        throw runtime_error("Invalid CAFF block id!");
    }
    this->id = idTmp;

    uint64_t lengthTmp;
    if (!file.read(reinterpret_cast<char*>(&lengthTmp), sizeof(lengthTmp))) {
        throw runtime_error("Invalid CAFF block length!");
    }
    this->length = lengthTmp;

    vector<uint8_t> dataTmp;
    if (!file.read(reinterpret_cast<char*>(&dataTmp), sizeof(dataTmp))) {
        throw runtime_error("Invalid CAFF data length!");
    }
    this->data = dataTmp;
}

uint8_t CaffBlock::getId() const {
    return id;
}
uint64_t CaffBlock::getLength() const {
    return length;
}
const vector<uint8_t>& CaffBlock::getData() const {
    return data;
}

CaffHeader::CaffHeader(ifstream& file) {
    this->magic = "CAFF";
    char magicTmp[5];
    if(!file.read(magicTmp, 4) || string(magicTmp, 4) != this->magic) {
        throw runtime_error("Invalid CIFF magic number!");
    }
    this->magic = string(magicTmp, 4);
}

const string CaffHeader::getMagic() const {
    return magic;
}
uint64_t CaffHeader::getHeaderSize() const {
    return headerSize;
}
uint64_t CaffHeader::getNumAnim() const {
    return numAnim;
}

uint16_t CaffCredits::getYear() const {
    return year;
}
uint8_t CaffCredits::getMonth() const {
    return month;
}
uint8_t CaffCredits::getDay() const {
    return day;
}
uint8_t CaffCredits::getHour() const {
    return hour;
}
uint8_t CaffCredits::getMinute() const {
    return minute;
}
uint64_t CaffCredits::getCreatorLen() const {
    return creatorLen;
}
string CaffCredits::getCreator() const {
    return creator;
}


uint64_t CaffAnimation::getDuration() const {
    return duration;
}
CiffFile CaffAnimation::getCiff() const {
    return ciff;
}

CaffFile::CaffFile(ifstream& file) {
    while (!file.eof()) {
        CaffBlock block = CaffBlock(file);
        this->blocks.push_back(block);
    }

    for (const CaffBlock& block: this->blocks) {
        switch (block.getId()) {
            case 0x1:
                CaffHeader(block);
                break;
            case 0x2:
                CaffCredits(block);
                break;
            case 0x3:
                CaffAnimation(block);
                break;
            default:
                break;
        }
    }
}

void CaffFile::toString() {

}