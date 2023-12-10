#pragma once

class Client {
public:
    Client();    // Constructor for the Client class
    ~Client();   // Destructor for the Client class

    void connectToServer(const char* serverIP, int serverPort);  // Method to connect to the server

private:
    int clientSocket;  // Socket descriptor for the client
};