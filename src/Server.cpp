#include "Server.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

Server::Server() {
    // Constructor: Creates a socket for the server
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating server socket\n";
        exit(EXIT_FAILURE);
    }
}

Server::~Server() {
    // Destructor: Closes the server socket
    close(serverSocket);
}

void Server::startServer() {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(5050);

    // Binds the server socket to a specific address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding server socket\n";
        exit(EXIT_FAILURE);
    }

    // Listens for incoming connections on the server socket
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening on server socket\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "Server started. Waiting for connections...\n";
}

void Server::acceptConnections() {
    sockaddr_in clientAddr{};
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Accepts incoming connections from clients
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);

    if (clientSocket == -1) {
        std::cerr << "Error accepting client connection\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "Client connected\n";
}

int Server::getClientSocket() const {
    return clientSocket;
}