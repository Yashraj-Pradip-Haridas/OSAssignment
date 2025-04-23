#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    // Check if two filenames are passed
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <source_file> <destination_file>" << endl;
        return 1;
    }

    // Get file names from command line
    string sourceFile = argv[1];
    string destFile = argv[2];

    // Open files
    ifstream inFile(sourceFile);
    ofstream outFile(destFile);

    if (inFile.is_open() && outFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            outFile << line << endl;
        }

        cout << "File copied from '" << sourceFile << "' to '" << destFile << "' successfully!" << endl;

        inFile.close();
        outFile.close();
    } else {
        cerr << "Error opening files. Please check file paths." << endl;
        return 1;
    }

    return 0;
}
