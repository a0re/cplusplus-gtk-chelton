#pragma once
#include <gtkmm.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Server.h"
#include "CookieClicker.h"

class Client : public Gtk::Window {
public:
    Client();

    virtual ~Client();

protected:
    CookieClicker cookieClicker;
    int clientSocket;
    int serverSocket;
    std::string ipAddress;
    int port = 5050;

    void pingServer(); //Test Function between Client and Server
    void ConnectToServer(const std::string &ipAddress, int port); // Connect to the server

    // Button Functionality
    void onConnectButtonClicked();
    void onBackButtonClicked();
    void receiveGameState();
    void sendGameStateToServer();

    // Layout of the Gtk::Client Window
    Gtk::Grid m_grid;
    // Label & Entry fields for IP and Port
    Gtk::Label lblIP, lblPort;
    Gtk::Entry txtIP, txtPort;
    Gtk::Label lblStatus;
    Gtk::Button btnConnect, btnBack;
};



