#pragma once
#include <gtkmm.h>

/*#include <gtkmm/application.h> || I don't need this at the moment*/

class StartView : public Gtk::Window {
public:
    StartView();
    virtual ~StartView();

protected:
    Gtk::Grid m_grid;

    Gtk::Label lblTitle;
    Gtk::Button btnServer, btnClient;

    void onServerButtonClicked();
    void onClientButtonClicked();
};