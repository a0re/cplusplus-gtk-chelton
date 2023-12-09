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

}

// Prints to console: 'Button was pressed'
 // [ For testing purposes only. Verifies Buttons are being called to functions ]
void MyWindow::on_button_numbered(const Glib::ustring& data)
{
    std::cout << data << " was pressed" << std::endl;
}

// Quick implementation of needed Function
// [ Will be removed as this is not OOP 'file wise' ]
void MyWindow::on_cookie_button_clicked() {
    m_cookie_count++;
        // [ Will not update the label without ]
    update_label_1();
}

// Quick implementation of needed Function
// [ Will be removed as this is not OOP 'file wise' ]
void MyWindow::on_cpc_button_clicked() {
    m_cpc_lvl_count++;
    m_cpc_cost_count++;
    // [ Will not update the label without ]
    update_label_3();
    update_label_4();
}

// Quick implementation of needed Function
// [ Will be removed as this is not OOP 'file wise' ]
void MyWindow::on_cps_button_clicked() {
    m_cps_count++;
    m_cps_lvl_count++;
    m_cps_cost_count++;
    // [ Will not update the label without ]
    update_label_2();
    update_label_5();
    update_label_6();
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

// the following is the code needed to run the Window
/*
int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.examples.base");

    return app->make_window_and_run<MyWindow>(argc, argv);
};
 */
