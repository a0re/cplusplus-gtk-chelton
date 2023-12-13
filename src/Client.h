#pragma once
#include <gtkmm.h>

class Client : public Gtk::Window {
public:
    Client();
    virtual ~Client();

protected:
    void onConnectButtonClicked();
    void ConnectToServer();


    void PingServer(); //Test Function between Client and Server

    //TODO: Implementation of all these functionality to load the game
    //void onBackButtonClicked();
    //void updateUI(int cookies, int cps, int cpc_lvl, int cpc_cost, int cps_lvl, int cps_cost);
    //void loadGame();

    Gtk::Grid m_grid;

    // Label & Entry fields for IP and Port
    Gtk::Label lblIP, lblPort;

    Gtk::Entry txtIP, txtPort;

    Gtk::Label lblStatus;

    Gtk::Button btnConnect, btnBack;

    int clientSocket;



    //Gtk::Label m_labelCookies, m_labelCPS, m_labelCPCLevel, m_labelCPCCost, m_labelCPSLevel, m_labelCPSCost;
};