#pragma once
#include <gtkmm.h>
#include "Server.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


class Client : public Gtk::Window {
public:
    Client();
    virtual ~Client();

protected:
    int clientSocket;
    int serverSocket;
    std::string ipAddress;
    int port = 5050;

    void ConnectToServer(const std::string &ipAddress, int port);
    void PingServer(); //Test Function between Client and Server

    // Button Functionality
    void onConnectButtonClicked();
    void onBackButtonClicked();



    Gtk::Grid m_grid;
    // Label & Entry fields for IP and Port
    Gtk::Label lblIP, lblPort;
    Gtk::Entry txtIP, txtPort;
    Gtk::Label lblStatus;
    Gtk::Button btnConnect, btnBack;

    //Gtk::Label m_labelCookies, m_labelCPS, m_labelCPCLevel, m_labelCPCCost, m_labelCPSLevel, m_labelCPSCost;

    //void loadGame();


    //TODO: Implementation of all these functionality to load the game
    //void onBackButtonClicked();
    //void updateUI(int cookies, int cps, int cpc_lvl, int cpc_cost, int cps_lvl, int cps_cost);

};