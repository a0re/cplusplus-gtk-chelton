#include <iostream>
#include "Server.h"
#include "CookieClicker.h"
Server::Server() : serverSocket(-1), cookieClicker() {
    // Setting basic Titles and Dimension of Window
    set_title("Cookie Clicker: Server");
    set_default_size(550, 450);

    // Set Label Information for Clients to join | IP + Port
    lblConnection.set_text("Connection Details:");
    lblPort.set_text("Port: 5050");
    lblClient.set_text("Client: ");
    btnBack.set_label("Back");

    m_grid.set_margin(20);
    set_child(m_grid);

    // Attach all labels + buttons into the Grid
    m_grid.attach(lblConnection, 0, 1, 1, 1);
    m_grid.attach(lblIP, 0, 2, 1, 1);
    m_grid.attach(lblPort, 0, 3, 1, 1);
    m_grid.attach(lblClient, 0, 4, 1, 1);
    m_grid.attach(btnBack, 0, 5, 1, 1);

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

// Method to create a Socket and Create the server
void Server::startServer() {
    // Create a socket for the server
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // Check if the socket was created successfully. If not, display an error and exit
    if (serverSocket == -1) {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }

    /////////////////////////////////////////////////////////////////////////////
    // Overview:
    // Set the Address Family to IPv4
    // Setting the IP Address to any interface
    // Set the Port Number to 5050
    /////////////////////////////////////////////////////////////////////////////
    struct sockaddr_in serverAddress{};
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(5050);

    // Bind the newly created socket to the given IP address
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error binding server socket");
        exit(EXIT_FAILURE);
    }

    // Get the assigned port
    // Length of the Address and PortNumber
    socklen_t addrLen = sizeof(serverAddress);
    getsockname(serverSocket, (struct sockaddr *) &serverAddress, &addrLen);


    /////////////////////////////////////////////////////////////////////////////
    // Get the hostname of the Server
    // Get the IP Address of the Server from the hostname
    // Convert the IP Address to a human readable form
    // Update the ipAddress member variable
    /////////////////////////////////////////////////////////////////////////////
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    struct hostent *host = gethostbyname(hostname);
    char *ip = inet_ntoa(*(struct in_addr *) host->h_addr);
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
        /////////////////////////////////////////////////////////////////////////////
        // Client Address Information
        // Get the Client Address Length
        // Accept the connection from the Client
        /////////////////////////////////////////////////////////////////////////////
        std:: cout << "Listening for connections..." << std::endl;
        struct sockaddr_in clientAddress{}; // Client address information
        socklen_t clientAddrLen = sizeof(clientAddress); // Length of the client address
        clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddrLen); // Accept a new connection

        if (clientSocket == -1) {
            perror("Error accepting connection");
            continue;  // Continue listening for the next connection
        }

        /////////////////////////////////////////////////////////////////////////////
        // Store the Client IP Address
        // Convert the Client IP Address to a readable form
        // Print Client IP Address & Port in the Terminal & Update the lblClient Label to connected.
        // Use the pingClient Method to confirm Connection has been made & Send Server's CookieClicker Game State through sendGameState method.
        /////////////////////////////////////////////////////////////////////////////
        char clientIp[INET_ADDRSTRLEN]; // Buffer to store the client IP address
        inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIp, INET_ADDRSTRLEN);
        std::cout << "Client connected. IP: " << clientIp << ", Port: " << ntohs(clientAddress.sin_port) << std::endl;
        lblClient.set_text("Client: " + std::string(clientIp) + ":" + std::to_string(ntohs(clientAddress.sin_port)));

        pingClient(clientSocket);
        sendGameState();

        //ignore this for the moment
        //std::thread clientUpdateThread(&Server::handleClientUpdates, this, clientSocket);
        //clientUpdateThread.detach();
    }
}

// Method to ping the client
void Server::pingClient(int clientSocket) {
    const char* pingResponse = "PING_RESPONSE"; // Response to send to the client
    send(clientSocket, pingResponse, strlen(pingResponse), 0); // Send the response to the client
}

// Method for Back button
void Server::onBackButtonClicked() {
    //TODO: Max - Implement this method properly to go back to the StartView
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
// Calling the CookieClicker Serialization method to send to the client
void Server::sendGameState() {
    GameData gameData = cookieClicker.serializeGameData();
    send(clientSocket, &gameData, sizeof(GameData), 0);
}

void Server::updateGameState(const GameData &gameData) {

}

