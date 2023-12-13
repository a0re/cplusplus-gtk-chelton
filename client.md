class Client {
public:
Client();    // Constructor for the Client class
virtual ~Client();   // Destructor for the Client class

    void connectToServer(const char* serverIP, int serverPort);  // Method to connect to the server

private:
int clientSocket;  // Socket descriptor for the client
};

#include "Client.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>



Client::Client() {
// Constructor: Creates a socket for the client
clientSocket = socket(AF_INET, SOCK_STREAM, 0);

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

/*#include <cassert>
#include <thread>
#include <chrono>

void testServer() {
Server server;

    // Start the server
    server.startServer();

    // Attempt to accept a connection (you may want to run this in a separate thread or process)
    std::thread clientThread([&]() {
        Client client;
        client.connectToServer("127.0.0.1", 5050);
        // Add any client-server interaction testing here
    });

    // Allow some time for the server to start and accept connections
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Try to accept connections
    server.acceptConnections();

    // Assert that the client connected successfully
    assert(server.getClientSocket() != -1);

    // Clean up
    clientThread.join();  // Wait for the client thread to finish
}*/
