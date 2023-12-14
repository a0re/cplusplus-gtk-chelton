#include "Client.h"
#include "CookieClicker.h"

Client::Client() : clientSocket(-1), serverSocket(-1) {
    // Setting basic Titles and Dimension of Client Window
    set_title("Cookie Clicker: Client");
    set_default_size(550, 450);

    //
    lblIP.set_text("Server IP:");
    lblPort.set_text("Port:");
    lblStatus.set_text("Status: Not Connected");
    txtPort.set_text(std::to_string(port));

    btnConnect.set_label("Connect");
    btnBack.set_label("Back");

    m_grid.set_margin(20);
    set_child(m_grid);

    // Attaching the widgets to the grid
    m_grid.attach(lblIP, 0, 0, 1, 1);
    m_grid.attach(txtIP, 1, 0, 1, 1);
    m_grid.attach(lblPort, 0, 1, 1, 1);
    m_grid.attach(txtPort, 1, 1, 1, 1);
    m_grid.attach(lblStatus, 0, 2, 2, 1);
    m_grid.attach(btnConnect, 1, 3, 1, 1);
    m_grid.attach(btnBack, 0, 3, 1, 1);

    // Connect signal handlers
    btnConnect.signal_clicked().connect(sigc::mem_fun(*this, &Client::onConnectButtonClicked));
    btnBack.signal_clicked().connect(sigc::mem_fun(*this, &Client::onBackButtonClicked));

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
    pingServer();
    receiveGameState();

    std::thread sendDataThread(&Client::sendGameDataToServer, this);
    sendDataThread.detach();
    // Create and show the CookieClicker Window
    cookieClicker.show();
}


// receiveGameState() is a method that runs in a loop to receive the game state from the server
void Client::receiveGameState() {
    while (true) {
        GameData gameData{};
        recv(clientSocket, &gameData, sizeof(GameData), 0);
        // Update the game state in the CookieClicker window
        cookieClicker.deserializeGameData(gameData);
    }
}


// Method: pingServer
// Purpose: Send a PING_RESPONSE message to the Server socket & Sends only a simple string message
void Client::pingServer() {
    const char* pingMessage = "PING";
    send(clientSocket, pingMessage, strlen(pingMessage), 0);
    std:: cout << "Hello From Client: Ping Sent" << std::endl;

}

void Client::onBackButtonClicked() {
    //TODO: Implement this method properly to go back to the StartView and call the destructor of the Client Window & socket
    std::cout << "Back Button Clicked" << std::endl;
}

// Todo: sendGameStateToServer() is a method that runs in a loop to send the game state to the server
void Client::sendGameDataToServer() {
    while (true) {
        // Serialize game data
        GameData gameData = cookieClicker.serializeGameData();

        // Send serialized game data to the server
        send(clientSocket, &gameData, sizeof(GameData), 0);

        // Sleep for a certain interval (e.g., 1 second)
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

