#pragma once
#include <gtkmm.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <thread>
#include "CookieClicker.h"

class Server : public Gtk::Window {
public:
    Server();           // Constructor for the Server class
    virtual ~Server();  // Destructor for the Server class

protected:
    // Variables
    CookieClicker cookieClicker;
    int serverSocket;
    int clientSocket;
    std::string ipAddress;

    // Methods Used
    void startServer(); // Method to create the socket and acts as the server
    void pingClient(int clientSocket); // Simple Method to ping the client connected
    void listeningForClientConnection(); // Listen to incoming Client, This is done in a separate thread
    void sendGameState(); // Sending Binary Serialization to the Client
    void onBackButtonClicked(); // Back button to StartView Window

    // Layout of the Gtk::Server Window
    Gtk::Grid m_grid;
    Gtk::Label lblConnection, lblIP, lblPort;
    Gtk::Label lblClient;
    Gtk::Button btnBack;


};

// Todo: updateGameState from Client


