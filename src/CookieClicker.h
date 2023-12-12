#pragma once
// gtkmm - a C++ wrapper for the Gtk toolkit
#include <gtkmm.h> //
#include <gtkmm/application.h> // Gtk::Application assist in running the program in main.cpp
#include <iostream>
#include <chrono>


class CookieClicker : public Gtk::Window
{
public:
    // Game Window Rendering
    CookieClicker();

    // [ TODO: Socket Connect Window ]
protected:
    //Variables:
    // Stores Count Values
    int m_cookie_count;
    int m_cps_count;
    int m_cpc_lvl_count;
    int m_cpc_cost_count;
    int m_cps_lvl_count;
    int m_cps_cost_count;
    int intervalMilliseconds = 1000;

    // Signal Handlers:
        // Writes to screen when button (Gtk::Button (variable)) is pressed
    void on_button_numbered(const Glib::ustring& data);
        // [ Needs further Implementation ]
        // [ TODO: functions should be in other files ]
    void on_cookie_button_clicked();
    void on_cpc_button_clicked();
    void on_cps_button_clicked();
    bool update_cps_callback();

        // Updates view
    void update_label_1();
    void update_label_2();
    void update_label_3();
    void update_label_4();
    void update_label_5();
    void update_label_6();

    // Layout Formatting:
    Gtk::Grid m_grid;

    // Labels:
    Gtk::Label m_label_1,
               m_label_2,
               m_label_3,
               m_label_4,
               m_label_5,
               m_label_6;

    // Label*
    Gtk::Label* m_label_7;

    // Buttons:
    Gtk::Button m_button_1,
                m_button_2,
                m_button_3;
};



