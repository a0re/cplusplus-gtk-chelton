#pragma once
#include <gtkmm.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

class Server : public Gtk::Window {
public:
    Server();   // Constructor for the Server class
    virtual ~Server();  // Destructor for the Server class

protected:
    int serverSocket;
    std::string ipAddress;

    void startServer();
    void onBackButtonClicked();



    /* Layout of Window */
    Gtk::Grid m_grid;
    Gtk::Label lblConnection, lblIP, lblPort;
    Gtk::Label lblClient;
    Gtk::Button btnBack;

};

