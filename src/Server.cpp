#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <thread>
#include "Server.h"
#include "CookieClicker.h"


Server::Server() : serverSocket(-1){
    set_title("Cookie Clicker: Server");
    set_default_size(550, 450);

    lblConnection.set_text("Connection Details:");
    lblPort.set_text("Port: 5050");
    lblClient.set_text("Client: ");
    btnBack.set_label("Back");

    m_grid.set_margin(20);
    set_child(m_grid);

    m_grid.attach(lblConnection, 0, 0, 1, 1);
    m_grid.attach(lblIP, 0, 1, 1, 1);
    m_grid.attach(lblPort, 0, 2, 1, 1);
    m_grid.attach(lblClient, 0, 3, 1, 1);
    m_grid.attach(btnBack, 0, 4, 1, 1);

    // Connect signal handler for the Back button
    btnBack.signal_clicked().connect(sigc::mem_fun(*this, &Server::onBackButtonClicked));

    // Start the server
    startServer();
}

void Server::startServer() {
    // Create a socket for the server
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // Check if the socket was created successfully. If not, display an error and exit
    if (serverSocket == -1) {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddress{};
    std::memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET; // Set the address family to IPv4
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Setting the IP address to any interface
    serverAddress.sin_port = htons(5050); // Setting the port Number

    // Bind the newly created socket to the given IP address
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error binding server socket");
        exit(EXIT_FAILURE);
    }

    // Get the assigned port
    socklen_t addrLen = sizeof(serverAddress); // Length of the address
    getsockname(serverSocket, (struct sockaddr *) &serverAddress, &addrLen); // Get the port number

    // Get the IP address
    char hostname[256]; // Hostname of the computer we are running on
    gethostname(hostname, sizeof(hostname)); // Get the hostname of the server
    struct hostent *host = gethostbyname(hostname); // Get the IP address of the server from the hostname
    char *ip = inet_ntoa(*(struct in_addr *) host->h_addr); // Convert the IP address in a human readable form

    // Update the ipAddress member variable
    ipAddress = ip;

    // Print IP address and port & Update the label
    std::cout << "Server started. IP: " << ipAddress << ", Port: " << ntohs(serverAddress.sin_port) << std::endl;
    lblIP.set_text("IP Address: " + ipAddress);

    // Listen for connections from clients
    // Listen for connections from clients
    if (listen(serverSocket, 5) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    while (true) {
        // Accept a connection from a client
        struct sockaddr_in clientAddress{};
        socklen_t clientAddrLen = sizeof(clientAddress);
        clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddrLen);

        if (clientSocket == -1) {
            perror("Error accepting connection");
            continue;  // Continue listening for the next connection
        }

        // Display client information and ping the client
        char clientIp[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIp, INET_ADDRSTRLEN);
        std::cout << "Client connected. IP: " << clientIp << ", Port: " << ntohs(clientAddress.sin_port) << std::endl;
        lblClient.set_text("Client: " + std::string(clientIp) + ":" + std::to_string(ntohs(clientAddress.sin_port)));

        // Ping the connected client
        PingClient(clientSocket);

        // Close the client socket (you may want to keep it open for further communication)
        ::close(clientSocket);
    }

}

void Server::PingClient(int clientSocket) {
    const char* pingResponse = "PING_RESPONSE";
    send(clientSocket, pingResponse, strlen(pingResponse), 0);
}


// Destructor for the Server class
Server::~Server() {

}


// Method for Back button
void Server::onBackButtonClicked() {
    //TODO: Implement this method properly to go back to the StartView
    std::cout << "Back Button Clicked" << std::endl;
}



/*
void Server::acceptClientConnections() {
    while (true) {
        struct sockaddr_in clientAddress{};
        socklen_t clientAddrLen = sizeof(clientAddress);

        int newClientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddrLen);

        if (newClientSocket == -1) {
            perror("Error accepting client connection");
            // Continue to listen for the next connection
            continue;
        }

        // Display client information
        char clientIp[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIp, INET_ADDRSTRLEN);
        std::cout << "Accepted connection from " << clientIp << ":" << ntohs(clientAddress.sin_port) << std::endl;
        lblClient.set_text("Client: " + std::string(clientIp));

        // Create a new thread to handle communication with the client
        std::thread([this, newClientSocket]() {
            while (true) {
                char buffer[1024];
                ssize_t bytesRead = recv(newClientSocket, buffer, sizeof(buffer), 0);

                if (bytesRead > 0) {
                    buffer[bytesRead] = '\0';
                    std::string receivedMessage(buffer);

                    // Handle received message (if needed)
                    if (receivedMessage == "PING") {
                        std::cout << "Ping received from client.\n";
                        // Send a response back to the client
                        PingClient(newClientSocket);
                    } else {
                        std::cerr << "Invalid message received from client.\n";
                    }
                } else {
                    // Handle error or disconnection
                    std::cerr << "Error receiving data from client.\n";
                    break;
                }
            }

            // Close the client socket when done
            ::close(newClientSocket);
        }).detach();
    }
}*/

