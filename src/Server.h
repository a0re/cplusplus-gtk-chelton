#pragma once

class Server {
public:
    Server();   // Constructor for the Server class
    ~Server();  // Destructor for the Server class

    void startServer();          // Method to start the server
    void acceptConnections();    // Method to accept incoming connections

    int getClientSocket() const;  // Method to retrieve clientSocket
private:
    int serverSocket;  // Socket descriptor for the server
    int clientSocket;  // Socket descriptor for the connected client
};
