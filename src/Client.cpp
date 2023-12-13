#include "Client.h"

Client::Client() : clientSocket(-1), serverSocket(-1) {
    set_title("Cookie Clicker: Client");
    set_default_size(550, 450);

    lblIP.set_text("Server IP:");
    lblPort.set_text("Port:");
    lblStatus.set_text("Status: Not Connected");
    btnConnect.set_label("Connect");
    btnBack.set_label("Back");

    m_grid.set_margin(20);
    set_child(m_grid);

    m_grid.attach(lblIP, 0, 0, 1, 1);
    m_grid.attach(txtIP, 1, 0, 1, 1);
    m_grid.attach(lblPort, 0, 1, 1, 1);
    m_grid.attach(txtPort, 1, 1, 1, 1);
    m_grid.attach(lblStatus, 0, 2, 2, 1);
    m_grid.attach(btnConnect, 0, 3, 1, 1);
    m_grid.attach(btnBack, 1, 3, 1, 1);

    // Connect signal handlers
    btnConnect.signal_clicked().connect(sigc::mem_fun(*this, &Client::onConnectButtonClicked));
    //btnBack.signal_clicked().connect(sigc::mem_fun(*this, &Client::onBackButtonClicked));
}

Client::~Client() {
    // Close the client socket if it's open
    if (clientSocket != -1) {
        ::close(clientSocket);
    }
}

void Client::onConnectButtonClicked() {
    // Get the IP address and port from the entry fields
    ipAddress = txtIP.get_text();
    std::string portStr = txtPort.get_text();
    int port = std::stoi(portStr);

    // Connect to the server
    ConnectToServer(ipAddress, port);
}

void Client::ConnectToServer(const std::string& ipAddress, int port) {
    // Create a socket for the client
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Check if the socket was created successfully. If not, display an error and exit
    if (clientSocket == -1) {
        perror("Error creating client socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddress{};
    std::memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET; // Set the address family to IPv4
    serverAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str()); // Set the server IP address
    serverAddress.sin_port = htons(port); // Set the server port

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error connecting to server");
        lblStatus.set_text("Status: Connection Failed");
        return;
    }

    // Connection successful
    lblStatus.set_text("Status: Connected to Server");

    // Ping the server
    PingServer();
}

void Client::PingServer() {
    const char* pingMessage = "PING";
    send(clientSocket, pingMessage, strlen(pingMessage), 0);

    // You can implement logic to wait for a response from the server if needed
    // For simplicity, the client assumes a response from the server after sending the "PING" message.
}

/*
void Client::onBackButtonClicked() {
    //TODO: Implement this method properly to go back to the StartView
    std::cout << "Back Button Clicked" << std::endl;
}
*/
