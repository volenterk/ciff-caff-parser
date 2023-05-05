#include <iostream>
#include "ciff/cifffile.h"
#include "ciff/ciffcontent.h"
#include "ciff/ciffheader.h"

int main() {
    std::ifstream file("examples/example.ciff", std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    CiffFile ciff(file);
    ciff.toString();

    std::ofstream outfile("examples/exampleOut.ciff", std::ios::binary);
    outfile.write(reinterpret_cast<char*>(ciff.getContent().getPixels().data()), ciff.getHeader().getContentSize());
    return 0;
}
