#include <iostream>
#include "ciff/ciffheader.cpp"
#include "ciff/ciffcontent.cpp"

int main() {
    std::ifstream file("examples/example.ciff", std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    CiffHeader header = readCiffHeader(file);
    header.toString();

    CiffContent content = readCiffContent(file, header.getContentSize(), header.getHeight(), header.getWidth());
    content.toString();

    std::ofstream outfile("examples/exampleOut.ciff", std::ios::binary);
    outfile.write(reinterpret_cast<char*>(content.getPixels().data()), content.getContentSize());
    return 0;
}


