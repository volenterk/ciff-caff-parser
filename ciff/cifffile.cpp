#include "cifffile.h"
#include "ciffheader.h"
#include "ciffcontent.h"

using namespace std;

CiffHeader& CiffFile::getHeader() { return header; }

CiffContent& CiffFile::getContent() { return content; }

void CiffFile::toString() {
    header.toString();
    content.toString();
}

