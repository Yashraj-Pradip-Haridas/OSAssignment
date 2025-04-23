#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    // Check if correct arguments are provided
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <search_string> <filename>" << endl;
        return 1;
    }

    string searchTerm = argv[1];
    string fileName = argv[2];

    ifstream inFile(fileName);

    if (!inFile.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return 1;
    }

    string line;
    int lineNumber = 0;
    while (getline(inFile, line)) {
        lineNumber++;
        if (line.find(searchTerm) != string::npos) {
            cout << lineNumber << ": " << line << endl;
        }
    }

    inFile.close();
    return 0;
}
