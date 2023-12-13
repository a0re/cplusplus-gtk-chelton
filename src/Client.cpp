#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include "Client.h"
#include "CookieClicker.h"
#include "Server.h"

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
    m_grid.attach(btnConnect, 1, 3);
    m_grid.attach(btnBack, 0, 3);


    // Connect signal handler for the Connect button
    btnConnect.signal_clicked().connect(sigc::mem_fun(*this, &Client::onConnectButtonClicked));

    // Set up client socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating client socket\n";
        return;
    }


    // Load the game
    //loadGame();
}

Client::~Client() {
    if (clientSocket != -1) {
        ::close(clientSocket);
    }
}
void Client::onConnectButtonClicked() {
    ConnectToServer();
}

/*
 * ConnectToServer Function
 * Gets the IP and Port from the user input and connects to the server
 * Display
 * */

void Client::ConnectToServer() {
    // Get the server's IP and port from user input
    std::string serverIP = txtIP.get_text();
    std::string serverPort = txtPort.get_text();

    // Print the server's IP and port to the console
    std::cout << "Connecting to server at " << serverIP << ":" << serverPort << "\n";
    lblStatus.set_text("Status: Issue Server is not running or the IP and Port are incorrect. Please try again later");

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
    else {
        PingServer();
    }

}


void Client::PingServer() {
    const char* pingMessage = "PING";
    send(clientSocket, pingMessage, strlen(pingMessage), 0);
}
/*

void Client::updateUI(int cookies, int cps, int cpc_lvl, int cpc_cost, int cps_lvl, int cps_cost) {
    // Update the UI with the received game data
    // Update Cookies label
    m_labelCookies.set_text("Cookies: " + std::to_string(cookies));

    // Update CPS label
    m_labelCPS.set_text("CPS: " + std::to_string(cps));

    // Update CPC Level label
    m_labelCPCLevel.set_text("CPC Level: " + std::to_string(cpc_lvl));

    // Update CPC Cost label
    m_labelCPCCost.set_text("CPC Cost: " + std::to_string(cpc_cost));

    // Update CPS Level label
    m_labelCPSLevel.set_text("CPS Level: " + std::to_string(cps_lvl));

    // Update CPS Cost label
    m_labelCPSCost.set_text("CPS Cost: " + std::to_string(cps_cost));
}
void Client::loadGame() {
    // Example: Receive data from the server (you need to adapt this based on your networking code)
    char buffer[1024];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the received data
        std::string gameStateString(buffer);

        // Parse the message format
        std::istringstream stream(gameStateString);
        std::string line;

        // Variables to store game state
        int cookies = 0, cps = 0, cpc_lvl = 0, cpc_cost = 0, cps_lvl = 0, cps_cost = 0;

        while (std::getline(stream, line)) {
            std::istringstream lineStream(line);
            std::string key;
            int value;

            if (lineStream >> key >> value) {
                if (key == "cookies") {
                    cookies = value;
                } else if (key == "cps") {
                    cps = value;
                } else if (key == "cpc_lvl") {
                    cpc_lvl = value;
                } else if (key == "cpc_cost") {
                    cpc_cost = value;
                } else if (key == "cps_lvl") {
                    cps_lvl = value;
                } else if (key == "cps_cost") {
                    cps_cost = value;
                }
            }
        }

        // Update the UI with the received game state
        updateUI(cookies, cps, cpc_lvl, cpc_cost, cps_lvl, cps_cost);

    } else {
        // Handle error or disconnection
        std::cerr << "Error receiving game state from the server.\n";
    }
}


*/
