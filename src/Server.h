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
    Server();   // Constructor for the Server class
    virtual ~Server();  // Destructor for the Server class

protected:
    CookieClicker cookieClicker;
    int serverSocket;
    int clientSocket;
    std::string ipAddress;

    void startServer();
    void onBackButtonClicked();
    void pingClient(int clientSocket);
    void listeningForClientConnection();
    void sendGameState();
    void handleClientUpdates(int clientSocket);

    // Layout of the Gtk::Server Window
    Gtk::Grid m_grid;
    Gtk::Label lblConnection, lblIP, lblPort;
    Gtk::Label lblClient;
    Gtk::Button btnBack;

};

    // Refer to the screenshots between Max & Dan
    // Sends Cookie Clicker data to the client for Client to load the game
    //void LoadGame(); // Load the game? I need to have the window shown in the Server window underneath the IP Address and Port labels



