#include <iostream>
#include "Server.h"
#include "CookieClicker.h"
Server::Server() : serverSocket(-1), cookieClicker() {
    set_title("Cookie Clicker: Server");
    set_default_size(550, 450);

    lblConnection.set_text("Connection Details:");
    lblPort.set_text("Port: 5050");
    lblClient.set_text("Client: ");
    btnBack.set_label("Back");

    m_grid.set_margin(20);
    set_child(m_grid);

    m_grid.attach(btnBack, 0, 0, 1, 1);
    m_grid.attach(lblConnection, 0, 1, 1, 1);
    m_grid.attach(lblIP, 0, 2, 1, 1);
    m_grid.attach(lblPort, 0, 3, 1, 1);
    m_grid.attach(lblClient, 0, 4, 1, 1);

    // Connect signal handler for the Back button
    btnBack.signal_clicked().connect(sigc::mem_fun(*this, &Server::onBackButtonClicked));

    // Listen for Connections from Clients | This is being run on separate thread since the server will be running in an infinite loop
    // This is done so no issues occur with the Rendering the Gtkmm::Window
    startServer();
    std::thread serverThread(&Server::listeningForClientConnection, this);
    serverThread.detach();

    // Create and show the CookieClicker Window | This is separate windows because I'm lazy at the moment.
    cookieClicker.show();
}

void Server::runServer() {
    listeningForClientConnection();
}

// Method to create a Socket and Create the server
void Server::startServer() {
    // Create a socket for the server
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // Check if the socket was created successfully. If not, display an error and exit
    if (serverSocket == -1) {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddress{};
    memset(&serverAddress, 0, sizeof(serverAddress));
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

    // Print IP address and port & Update the label to Connect
    std::cout << "Server started. IP: " << ipAddress << ", Port: " << ntohs(serverAddress.sin_port) << std::endl;
    lblIP.set_text("IP Address: " + ipAddress);
}
// Method to listen for client connections and accept them | This method will run in a separate thread since it will be running in an infinite loop
void Server::listeningForClientConnection() {
    // Listen for connections from clients
    if (listen(serverSocket, 5) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    while (true) {
        std:: cout << "Listening for connections..." << std::endl;
        struct sockaddr_in clientAddress{}; // Client address information
        socklen_t clientAddrLen = sizeof(clientAddress); // Length of the client address
        clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddrLen); // Accept a new connection

        if (clientSocket == -1) {
            perror("Error accepting connection");
            continue;  // Continue listening for the next connection
        }

        // Display client information and ping the client
        char clientIp[INET_ADDRSTRLEN]; // Buffer to store the client IP address
        inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIp, INET_ADDRSTRLEN); // Convert the client IP address to a human readable form
        std::cout << "Client connected. IP: " << clientIp << ", Port: " << ntohs(clientAddress.sin_port) << std::endl; // Print the client IP address and port
        lblClient.set_text("Client: " + std::string(clientIp) + ":" + std::to_string(ntohs(clientAddress.sin_port))); // Update the label to show the client IP address and port

        // Ping the connected client and send the game state
        pingClient(clientSocket);
        sendGameState();
    }
}

// Method to ping the client
void Server::pingClient(int clientSocket) {
    const char* pingResponse = "PING_RESPONSE"; // Response to send to the client
    send(clientSocket, pingResponse, strlen(pingResponse), 0); // Send the response to the client
}

// Method for Back button
void Server::onBackButtonClicked() {
    //TODO: Implement this method properly to go back to the StartView
    //Also Call the Destructor for the Server Class to close the server socket
    std::cout << "Back Button Clicked" << std::endl;
}

// Destructor for the Server class
Server::~Server() {
    // Close the server socket if it's open
    if (serverSocket != -1) {
        ::close(serverSocket);
    }
}

// Method to send the game state to the client when connected
void Server::sendGameState() {
    GameData gameData = cookieClicker.serializeGameData();
    send(clientSocket, &gameData, sizeof(GameData), 0);
}





