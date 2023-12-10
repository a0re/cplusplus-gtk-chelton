#include "MyWindow.h"

// Window Rendering
MyWindow::MyWindow()
: m_label_1("Cookies: 0"),
  m_cookie_count(0),
  m_label_2("CPS: 0"),
  m_cps_count(0),
  m_button_1("Click The Cookie!"),
  m_button_2("Upgrade CPC"),
  m_label_3("LVL: 1"),
  m_cpc_lvl_count(1),
  m_label_4("Cost: 0"),
  m_cpc_cost_count(0),
  m_button_3("Upgrade CPS"),
  m_label_5("LVL: 1"),
  m_cps_lvl_count(1),
  m_label_6("Cost: 0"),
  m_cps_cost_count(0)
{

    // Window Title
    set_title("Game: Cookie Clicker");

    // Window Size ( width x height )
    set_default_size(550, 450);

    //Layout Formatting
        // [ TODO: Better Layout, refer to documents ]
    m_grid.set_margin(12);

    // Places Grid within Window Frame
    // [ Buttons and Labels will not show without this ]
    set_child(m_grid);

    // Attaches Labels to Grid ( column = x-axis, row = (inverted) y-axis )
    m_grid.attach(m_label_1, 0, 0);
    m_grid.attach(m_label_2, 0, 1);
    m_grid.attach(m_label_3, 0,4);
    m_grid.attach(m_label_4, 1,4);
    m_grid.attach(m_label_5, 0,6);
    m_grid.attach(m_label_6, 1,6);

    // Attaches Buttons to Grid ( column = x-axis, row = (inverted) y-axis )
    m_grid.attach(m_button_1, 0, 2);
    m_grid.attach(m_button_2, 0, 3);
    m_grid.attach(m_button_3, 0, 5);

    // Connects Signal handler to the 'clicked' signal of Buttons ( m_button_(int))
    // [ when Buttons are clicked allocated functions (on_button_numbered()) are triggered ]
    m_button_1.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_cookie_button_clicked));
    m_button_1.signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &MyWindow::on_button_numbered), "Cookie") );

    m_button_2.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_cpc_button_clicked));
    m_button_2.signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &MyWindow::on_button_numbered), "Upgrade CPC") );

    m_button_3.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_cps_button_clicked));
    m_button_3.signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &MyWindow::on_button_numbered), "Upgrade CPS") );

    // Calls to Function every Second [ Gtkmm Library Signal ]
    //  https://gnome.pages.gitlab.gnome.org/glibmm/classGlib_1_1SignalTimeout.html#a26c6d456b606758e819d3db69ae17d56
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &MyWindow::update_cps_callback), intervalMilliseconds);
}

// Prints to console: 'Button was pressed'
 // [ For testing purposes only. Verifies Buttons are being called to functions ]
void MyWindow::on_button_numbered(const Glib::ustring& data)
{
    std::cout << data << " was pressed" << std::endl;
}

// [ Functions are in this file for testing currently ]
// [ TODO: Move Functions to other files ]
    // Increments Cookies
void MyWindow::on_cookie_button_clicked() {
    // Increments Cookies by CPC LVL
    m_cookie_count += m_cpc_lvl_count;
    update_label_1();
}

// Purchase System for CPC
void MyWindow::on_cpc_button_clicked() {
    // Authenticates Transaction
    if (m_cpc_cost_count > m_cookie_count) {
        // [ TODO: Error Handling ]
    } else {
        // Subtracts Cookies based upon CPC Cost
        m_cookie_count -= m_cpc_cost_count;
        // Increments CPC LVL
        m_cpc_lvl_count++;
        // Increments Cost Total by [ 20 ]
        m_cpc_cost_count += 20;
        update_label_1();
        update_label_3();
        update_label_4();
    }
}

// Purchase System for CPS
void MyWindow::on_cps_button_clicked() {
    // Authenticates Transaction
    if (m_cps_cost_count >= m_cookie_count) {
        // [ TODO: Error Handling ]
    } else {
        // Subtracts Cookies based upon CPS Cost
        m_cookie_count -= m_cps_cost_count;
        // Increments CPS LVL
        m_cps_lvl_count++;
        // Increments CPS Count
        m_cps_count++;
        // Increments Cost Total by [ 50 ]
        m_cps_cost_count += 50;
        update_label_1();
        update_label_2();
        update_label_5();
        update_label_6();
    }
}

// Updates the View each time corresponding function is called to
 // [ TODO: Verification ]
void MyWindow::update_label_1() {
    m_label_1.set_text("Cookies: " + std::to_string(m_cookie_count));
}
void MyWindow::update_label_2() {
    m_label_2.set_text("CPS: " + std::to_string(m_cps_count));
}
void MyWindow::update_label_3() {
    m_label_3.set_text("LVL: " + std::to_string(m_cpc_lvl_count));
}
void MyWindow::update_label_4() {
    m_label_4.set_text("Cost: " + std::to_string(m_cpc_cost_count));
}
void MyWindow::update_label_5() {
    m_label_5.set_text("LVL: " + std::to_string(m_cps_lvl_count));
}
void MyWindow::update_label_6() {
    m_label_6.set_text("Cost: " + std::to_string(m_cps_cost_count));
}

// Increments Cookie Total automatically by the CPS
bool MyWindow::update_cps_callback() {
    // Use std::chrono to calculate the time elapsed since the last update
    static auto last_time = std::chrono::high_resolution_clock::now();
    auto current_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_time).count();

    // Increment the number of cookies per second based on elapsed time
    m_cookie_count += m_cps_count * elapsed_time;

    // Update the label text
    update_label_1();

    // Update the last_time variable for the next iteration
    last_time = current_time;

    // Returning true ensures the timer continues to run
    return true;
}


// the following is the code needed to run the Window
/*
int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.examples.base");

    return app->make_window_and_run<MyWindow>(argc, argv);
};
 */
