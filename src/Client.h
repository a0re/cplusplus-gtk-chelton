#pragma once
#include <gtkmm.h>

class Client : public Gtk::Window {
public:
    Client();
    virtual ~Client();

protected:
    void ConnectToServer();
    void loadGame();
    void onConnectButtonClicked();
    void updateUI(int cookies, int cps, int cpc_lvl, int cpc_cost, int cps_lvl, int cps_cost);

    Gtk::Grid m_grid;

    // Label & Entry fields for IP and Port
    Gtk::Label lblIP, lblPort;

    Gtk::Entry txtIP, txtPort;

    Gtk::Label lblStatus;

    Gtk::Button btnConnect, btnBack;

    int clientSocket;

    Gtk::Label m_labelCookies, m_labelCPS, m_labelCPCLevel, m_labelCPCCost, m_labelCPSLevel, m_labelCPSCost;
};