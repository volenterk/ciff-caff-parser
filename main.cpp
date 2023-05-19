#include <iostream>
#include "cifffile.h"
#include "cafffile.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage ./parser [-caff/-ciff] [path-to-file].[caff/ciff]" << endl;
        return -1;
    }
    string option = argv[1];

    string path = argv[2];
    ifstream file(path, ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return -1;
    }

    ofstream outFile;
    string outPath;
    size_t extPos = path.find_last_of('.');
    string ext = path.substr(extPos + 1);

    if (ext == "caff") {
        if (option != "-caff") {
            cerr << "Invalid option for CAFF parsing!" << endl;
            return -1;
        }

        outPath = path.substr(0, extPos) + ".webp";
        outFile.open(outPath, ios::binary);
    } else if (ext == "ciff") {
        if (option != "-ciff") {
            cerr << "Invalid option for CIFF parsing!" << endl;
            return -1;
        }

        outPath = path.substr(0, extPos) + ".webp";
        outFile.open(outPath, ios::binary);
    } else {
        cerr << "Unsupported format! Exiting..." << endl;
        return -1;
    }

    vector<::uint8_t> preview;

    try {
        if (option == "-caff") {
            CaffFile caff(file);
            preview = caff.makePreview();
            caff.toString();
        } else if (option == "-ciff") {
            CiffFile ciff(file);
            preview = ciff.makePreview();
            ciff.toString();
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }

    outFile.write(reinterpret_cast<char*>(preview.data()), preview.size());

    return 0;
}
