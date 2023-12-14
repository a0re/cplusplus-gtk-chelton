#pragma once

#include <gtkmm.h>
#include "Client.h"
#include "Server.h"

class StartView : public Gtk::Window {
public:
    StartView();
    virtual ~StartView();

protected:
    // Layout of the Gtk::Window
    Gtk::Grid m_grid;
    Gtk::Label lblTitle;
    Gtk::Button btnServer, btnClient;

    // Methods for buttons
    void onServerButtonClicked();
    void onClientButtonClicked();


    Server* server;
    Client* client;
};
