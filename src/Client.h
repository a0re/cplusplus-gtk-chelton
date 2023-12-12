#pragma once
#include <gtkmm.h>

class Client : public Gtk::Window {
public:
    Client();
    virtual ~Client();

protected:
    void ConnectToServer();
    void loadGame();

    Gtk::Grid m_grid;

    // Label & Entry fields for IP and Port
    Gtk::Label lblIP, lblPort;
    Gtk::Entry txtIP, txtPort;

    Gtk::Label lblStatus;

    Gtk::Button btnConnect, btnBack;

    int clientSocket;

};