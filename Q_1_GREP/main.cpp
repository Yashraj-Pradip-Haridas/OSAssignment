#include <iostream>
#include <unistd.h> // for execvp
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <command> [args...]" << endl;
        return 1;
    }

    string command = argv[1];

    if (command == "copy") {
        // Expects: ./main copy source.txt dest.txt
        if (argc != 4) {
            cerr << "Usage: " << argv[0] << " copy <source> <destination>" << endl;
            return 1;
        }

        execlp("./copy", "copy",argv[2], argv[3], NULL );
    }
    else if (command == "grep") {
        // Expects: ./main grep "pattern" file.txt
        if (argc != 4) {
            cerr << "Usage: " << argv[0] << " grep <pattern> <file>" << endl;
            return 1;
        }


        execlp("./grep", "grep",argv[2], argv[3], NULL );
    }
    else {
        cerr << "Unknown command: " << command << endl;
        return 1;
    }

    // If execvp fails
    perror("execlp failed");
    return 1;
}
