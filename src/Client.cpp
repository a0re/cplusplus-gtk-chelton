#include "Client.h"
#include "CookieClicker.h"

Client::Client() : clientSocket(-1), serverSocket(-1) {
    // Setting basic Titles and Dimension of Client Window
    set_title("Cookie Clicker: Client");
    set_default_size(550, 450);

    // Set the labels and buttons for the Client Window
    lblIP.set_text("Server IP:");
    lblPort.set_text("Port:");
    lblStatus.set_text("Status: Not Connected");
    txtPort.set_text(std::to_string(port)); // Set the default port number to 5050
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

// Destructor for the Client class
Client::~Client() {
    // Close the client socket if it's open
    if (clientSocket != -1) {
        ::close(clientSocket);
    }
}


// Method: onConnectButtonClicked
// Purpose: Connect to the server when the Connect button is clicked
void Client::onConnectButtonClicked() {
    // Retrieve the IP address and port number from the entry boxes then initialize the client socket
    ipAddress = txtIP.get_text();
    std::string portStr = txtPort.get_text();
    int port = std::stoi(portStr);

    // Connect to the server
    ConnectToServer(ipAddress, port);
}

/////////////////////////////////////////////////////////////////////////////
// Overview:
// Create a socket for the client, initializes the server address structure similar to the Server.cpp.
// If Connection to the server is successful, Updates the UI status label accordingly, Additionally
// A new thread is created to receive the game state from the server through the receiveGameState() method.
/////////////////////////////////////////////////////////////////////////////
void Client::ConnectToServer(const std::string& ipAddress, int port) {
    // Create a socket for the client
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Check if the socket was created successfully. If not, display an error and exit
    if (clientSocket == -1) {
        perror("Error creating client socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddress{};
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    serverAddress.sin_port = htons(port);

    // Attempt to connect to the server using the clientSocket and serverAddress.
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        // If the connection fails, display an error message & update the UI status label
        // and exit the method.
        perror("Error connecting to server");
        lblStatus.set_text("Status: Connection Failed");
        return;
    }
    // Connection successful: Update the UI status label to indicate a successful connection.
    lblStatus.set_text("Status: Connected to Server");

    // Create a new thread to receive the game state from the server
    std::thread clientThread(&Client::receiveGameState, this);
    clientThread.detach();

    cookieClicker.show();
}


// receiveGameState() is a method that runs in a loop to receive the game state from the server
void Client::receiveGameState() {
    // This while loop is required otherwise the Cookies and CPS Becomes a really large number
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
}

void Client::onBackButtonClicked() {
    //TODO: Implement this method properly to go back to the StartView and call the destructor of the Client Window & socket
    std::cout << "Back Button Clicked" << std::endl;
}

// Todo: sendGameStateToServer() is a method that runs in a loop to send the game state to the server
/*void Client::sendGameDataToServer() {
    while (true) {
        // Serialize game data
        GameData gameData = cookieClicker.serializeGameData();

        // Send serialized game data to the server
        send(clientSocket, &gameData, sizeof(GameData), 0);

        // Sleep for a certain interval (e.g., 1 second)
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}*/

