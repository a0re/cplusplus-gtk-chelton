#pragma once
// gtkmm - a C++ wrapper for the Gtk toolkit
#include <gtkmm.h> //
#include <gtkmm/application.h> // Gtk::Application assist in running the program in main.cpp
#include <iostream>
#include <chrono>

// Struct GameData is used to serialize and deserialize the game data | These variables are to serialize and deserialize the game data between client and server
struct GameData {
    int cookieCount;    // Total cookie count
    int cpsCount;       // Cookies per second count
    int cpcLvlCount;    // Cookie per click level count
    int cpcCostCount;   // Cookie per click cost count
    int cpsLvlCount;    // Cookies per second level count
    int cpsCostCount;   // Cookies per second cost count
};

class CookieClicker : public Gtk::Window
{
public:
    // Game Window Rendering
    CookieClicker();

    // Serialize the game data & Deserialize the game data for both Client & Server
    GameData serializeGameData() const;
    void deserializeGameData(const GameData& gameData);

protected:
    //Variables: Stores Count Values
    int m_cookie_count;              // Total cookie count
    int m_cps_count;                 // Cookies per second count
    int m_cpc_lvl_count;             // Cookie per click level count
    int m_cpc_cost_count;            // Cookie per click cost count
    int m_cps_lvl_count;             // Cookies per second level count
    int m_cps_cost_count;            // Cookies per second cost count
    int intervalMilliseconds = 1000; // Interval for CPS

    // Signal Handlers:
        // Writes to screen when button (Gtk::Button (variable)) is pressed
    void on_button_numbered(const Glib::ustring& data);
        // [ Needs further Implementation ]
        // [ TODO: functions should be in other files ]
    void on_cookie_button_clicked();
    void on_cpc_button_clicked();
    void on_cps_button_clicked();
    bool update_cps_callback();

    // Updates view | This is to update the label text. In my opinion there should be a better way to do this then to have 6 different functions.
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

