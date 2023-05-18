#include <iostream>
#include "ciff/cifffile.h"
#include "ciff/cafffile.h"

int main() {
    string option = "caff";
    ifstream file("examples/bigger.ciff", ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return -1;
    }

    ofstream outfile("examples/exampleOut.webp", ios::binary);
    vector<::uint8_t> preview;

    try {
        if (option == "caff") {
            CaffFile caff(file);
            caff.toString();
            preview = caff.makePreview();

        } else if (option == "ciff") {
            CiffFile ciff(file);
            ciff.toString();
            preview = ciff.makePreview();
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }

    outfile.write(reinterpret_cast<char*>(preview.data()), preview.size());

    return 0;
}
