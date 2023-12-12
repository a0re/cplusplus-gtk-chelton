#pragma once
#include <gtkmm.h>

class Server : public Gtk::Window {
public:
    Server();   // Constructor for the Server class
    virtual ~Server();  // Destructor for the Server class

protected:
    void startGame();
    void listenForConnection();
    void handleClientConnection(int clientSocket);


    Gtk::Grid m_grid;
    // Show Connection Details
    Gtk::Label lblConnection, lblIP, lblPort, lblStatus;

    // Show Connected Clients
    Gtk::Label lblClient;
    Gtk::Button btnBack;

    int serverSocket;  // Socket descriptor for the server

    std::vector<int> connectedClients; // Vector to store connected clients
};



