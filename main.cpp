#include <iostream>
#include "ciff/cifffile.h"
#include "ciff/ciffheader.h"

int main() {
    std::ifstream file("examples/bigger.ciff", std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }
    try {
        CiffFile ciff(file);
        ciff.toString();
        std::ofstream outfile("examples/exampleOut.webp", std::ios::binary);
        std::vector<::uint8_t> preview = ciff.makePreview();
        outfile.write(reinterpret_cast<char*>(preview.data()), preview.size());
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
