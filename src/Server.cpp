#include "Server.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>

Server::Server() : serverSocket(-1) {
    set_title("Cookie Clicker: Server");
    set_default_size(550, 450);

    lblStatus.set_text("Server Started");
    lblConnection.set_text("Connection Details:");
    lblIP.set_text("IP Address: "); /*+ getIP());*/
    lblPort.set_text("Port: 5050");
    lblStatus.set_text("Status: Listening for connections...");

    // Create the server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating server socket\n";
        return;
    }

    // Configure the server socket address structure
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(5050);

    // Binds the server socket to a specific address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding server socket\n";
        ::close(serverSocket);
        return;
    }

    // Start listening for incoming connections
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening for connections.\n";
        ::close(serverSocket);
        return;
    }

    m_grid.set_margin(20);
    set_child(m_grid);

    m_grid.attach(lblConnection, 0, 0);
    m_grid.attach(lblIP, 0, 1);
    m_grid.attach(lblPort, 0, 2);
    m_grid.attach(lblStatus, 0, 3);

    /* TODO: Start the game and listen for connections | Add functions Underneath */
}


// Destructor for the Server class
Server::~Server() {
    // Close the server socket
    ::close(serverSocket);
}

void Server::startGame() {
    //TODO: Implement this method
}


// Listen for incoming connections
void Server::listenForConnection() {
    while (true) {
        // Accepts incoming connections from clients
        sockaddr_in clientAddr{};
        socklen_t clientAddrLen = sizeof(clientAddr);

        //Accept incoming Connections
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            std::cerr << "Error accepting client connection.\n";
            continue;
        }

        // Handle the client connection in a separate thread or process
        std::thread([this, clientSocket]() {
            handleClientConnection(clientSocket);
        }).detach();
    }
}

void Server::handleClientConnection(int clientSocket) {
    // Add the client socket to the vector of connected clients
    connectedClients.push_back(clientSocket);

    // Get the client's IP address & Update the UI to show connected clients
    Glib::ustring clientsText = "Connected Clients:\n";
    for (const auto& client : connectedClients) {
        clientsText += std::to_string(client) + "\n";
    }
    lblClient.set_text(clientsText);

    // Implement logic to handle communication with the connected client
    // You may want to create a separate class or function for this
    // For simplicity, we'll just close the connection for now
    //::close(clientSocket);
}

