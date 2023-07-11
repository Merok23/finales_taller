#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

bool checkFinish(char* buffer) {
    char string[4];
    memcpy(string, buffer, 3);
    string[3] = '\0';
    if (strcmp("FIN", string) == 0) return true;
    return false;
}

int main (int argc, char** argv) {
    if (argc != 3) return 1;
    char* ip = argv[1];
    char* port = argv[2];
    struct addrinfo hints;
    struct addrinfo* result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    int error = getaddrinfo(ip, port, &hints, &result);
    if (error == -1) return 1;
    int sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sfd == -1) {
        freeaddrinfo(result);
        return 1;
    }
    bool finished = false;
    size_t size_read = 0;
    size_t size_sent = 0;
    char buffer[3];
    while(!finished) {
        while (size_read < 3) {
            error = recv(sfd, buffer, 3, 0);
            if (error == -1) return 1; //and freeaddrinfo
            size_read += error;
        }
        size_read = 0;
        finished = checkFinish(buffer);
        if (finished) continue;
        while (size_sent < 3) {
            error = send(sfd, buffer, 3, 0);
            if (error == -1) return 1; //and freeaddrinfo
            size_sent += error;
        }
    }
    freeaddrinfo(result);
    shutdown(sfd, SHUT_RDWR);    
    close(sfd);
}