#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;

int main() {
    int pipe1[2]; // Parent to Child
    int pipe2[2]; // Child to Parent

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        cerr << "Pipe creation failed" << endl;
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed" << endl;
        return 1;
    }

    if (pid == 0) {  // 👶 Child Process
        // Close unused ends
        close(pipe1[1]); // Close write end of pipe1 (parent → child)
        close(pipe2[0]); // Close read end of pipe2 (child → parent)

        // Read message from parent
        char buffer[100];
        read(pipe1[0], buffer, sizeof(buffer));
        cout << "Child received: " << buffer;

        // Send reply to parent
        const char* reply = "Hi Parent, I got your message!\n";
        write(pipe2[1], reply, strlen(reply) + 1);

        // Close used ends
        close(pipe1[0]);
        close(pipe2[1]);
    } else {  // 👨 Parent Process
        // Close unused ends
        close(pipe1[0]); // Close read end of pipe1
        close(pipe2[1]); // Close write end of pipe2

        // Send message to child
        const char* msg = "Hello from parent!\n";
        write(pipe1[1], msg, strlen(msg) + 1);

        // Read reply from child
        char buffer[100];
        read(pipe2[0], buffer, sizeof(buffer));
        cout << "Parent received: " << buffer;

        // Close used ends
        close(pipe1[1]);
        close(pipe2[0]);

        // Wait for child to finish
        wait(NULL);
    }

    return 0;
}
