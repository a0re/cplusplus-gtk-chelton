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
    CookieClicker cookieClicker;
    int serverSocket;
    int clientSocket;
    std::string ipAddress;

    //
    void startServer();
    void pingClient(int clientSocket);
    void listeningForClientConnection(); // Listen to incoming Client
    void sendGameState(); // Sending Binary Serialization to the Client
    void onBackButtonClicked(); //
    void updateGameState(const GameData& gameData);

    // Layout of the Gtk::Server Window
    Gtk::Grid m_grid;
    Gtk::Label lblConnection, lblIP, lblPort;
    Gtk::Label lblClient;
    Gtk::Button btnBack;

};

// Todo: updateGameState from Client


