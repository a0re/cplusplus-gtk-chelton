#include "Client.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

Client::Client() {
    // Constructor: Creates a socket for the client
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    /* Checks*/
    if (clientSocket == -1) {
        std::cerr << "Error creating client socket\n";
        exit(EXIT_FAILURE);
    }
}

Client::~Client() {
    // Destructor: Closes the client socket
    close(clientSocket);
}


void Client::connectToServer(const char* serverIP, int serverPort) {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);
    serverAddr.sin_port = htons(serverPort);

    // Connects to the server using the created socket
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting to server\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected to server\n";
}
