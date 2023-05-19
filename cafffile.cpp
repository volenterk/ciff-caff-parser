#include "cafffile.h"
#include <iostream>

using namespace std;

CaffHeader::CaffHeader(ifstream& file) {
    char magicTmp[5];
    if (!file.read(magicTmp, 4) || string(magicTmp, 4) != "CAFF") {
        throw runtime_error("Invalid CAFF header magic number!");
    }
    magic = string(magicTmp, 4);

    if (!file.read(reinterpret_cast<char*>(&headerSize), sizeof(headerSize))) {
        throw runtime_error("Error reading header size in CAFF header!");
    }
    if (headerSize != 4 + 8 + 8) {
        throw runtime_error("The header size should be 20 bytes for a CAFF file");
    }

    if(!file.read(reinterpret_cast<char*>(&numAnim), sizeof(numAnim))) {
        throw runtime_error("Error reading number of animation blocks in CAFF header");
    }
}

CaffCredits::CaffCredits(ifstream& file) {
    if (!file.read(reinterpret_cast<char*>(&year), sizeof(year))) {
        throw runtime_error("Error reading year in CAFF credits block!");
    }

    if (!file.read(reinterpret_cast<char*>(&month), sizeof(month))) {
        throw runtime_error("Error reading month in CAFF credits block!");
    }

    if (!file.read(reinterpret_cast<char*>(&day), sizeof(day))) {
        throw runtime_error("Error reading day in CAFF credits block!");
    }

    if (!file.read(reinterpret_cast<char*>(&hour), sizeof(hour))) {
        throw runtime_error("Error reading hour in CAFF credits block!");
    }

    if (!file.read(reinterpret_cast<char*>(&minute), sizeof(minute))) {
        throw runtime_error("Error reading minute in CAFF credits block!");
    }

    if (!file.read(reinterpret_cast<char*>(&creatorLen), sizeof(creatorLen))) {
        throw runtime_error("Error reading creator length in CAFF credits block!");
    }

    vector<char> buffer(this->creatorLen);
    if (!file.read(buffer.data(), this->creatorLen)) {
        throw runtime_error("Error reading creator in CAFF credits block!");
    }
    creator = string(buffer.data(), this->creatorLen);
}

CaffAnimation::CaffAnimation(ifstream& file) {
    if (!file.read(reinterpret_cast<char*>(&duration), sizeof(duration))) {
        throw runtime_error("Error while reading duration of the animation!");
    }
    ciff = CiffFile(file);
}

void CaffFile::parseCaff() {
    uint8_t id;
    uint64_t length;

    if (!file.read(reinterpret_cast<char*>(&id), sizeof(id))) {
        throw runtime_error("Invalid CAFF block id!");
    }
    if (id != 0x1) {
        throw runtime_error("The CAFF file should start with a header block");
    }
    if (!file.read(reinterpret_cast<char*>(&length), sizeof(length))) {
        throw runtime_error("Invalid CAFF block length!");
    }

    header = CaffHeader(file);

    if (!file.read(reinterpret_cast<char*>(&id), sizeof(id))) {
        throw runtime_error("Invalid CAFF block id!");
    }
    if (id != 0x2) {
        throw runtime_error("The second block in a CAFF file should be credits");
    }
    if (!file.read(reinterpret_cast<char*>(&length), sizeof(length))) {
        throw runtime_error("Invalid CAFF block length!");
    }

    credits = CaffCredits(file);

    parseAnimations();
}

void CaffFile::parseAnimations() {
    while (true) {
        uint8_t id;
        uint64_t length;
        if (!file.read(reinterpret_cast<char*>(&id), sizeof(id))) {
            if (file.eof()) {
                break;
            } else {
                throw runtime_error("Invalid CAFF block id");
            }
        }
        if (id != 0x3) {
            throw runtime_error("The CAFF file should contain only animation blocks after header and credits blocks!");
        }
        if (!file.read(reinterpret_cast<char*>(&length), sizeof(length))) {
            throw runtime_error("Invalid CAFF block length!");
        }

        animations.emplace_back(file);//push_back(CaffAnimation(file));
    }
}

vector<uint8_t> CaffFile::makePreview() {
    if (animations.empty()) {
        throw runtime_error("No animations found in the CAFF file!");
    }

    return animations[0].getCiff().makePreview();
}