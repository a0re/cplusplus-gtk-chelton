#include "Client.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>


Client::Client() : clientSocket(-1) {
    set_title("Cookie Clicker: Client");
    set_default_size(550, 450);


    lblIP.set_text("IP Address: ");
    txtIP.set_text(" ");

    lblPort.set_text("Port: ");
    txtPort.set_text("5050");

    lblStatus.set_text("Status: ");

    m_grid.set_margin(20);
    set_child(m_grid);

    btnConnect.set_label("Connect");
    btnBack.set_label("Back");

    m_grid.attach(lblIP, 0, 0);
    m_grid.attach(txtIP, 1, 0);
    m_grid.attach(lblPort, 0, 1);
    m_grid.attach(txtPort, 1, 1);

    m_grid.attach(lblStatus, 0, 2);



    // Set up client socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating client socket\n";
        return;
    }

    // Connect to server
    //ConnectToServer();

    // Load the game
    //loadGame();
}

Client::~Client() {
    // Destructor: Closes the client socket
    ::close(clientSocket);
}

void Client::ConnectToServer() {
    // Get the server's IP and port from user input
    std::string serverIP = txtIP.get_text();
    std::string serverPort = txtPort.get_text();

    // Configure server address
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, serverIP.c_str(), &(serverAddr.sin_addr));
    serverAddr.sin_port = htons(std::stoi(serverPort));

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting to the server.\n";
        ::close(clientSocket);
        return;
    }
}
