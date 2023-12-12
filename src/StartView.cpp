#include <iostream>
#include "StartView.h"
/*include server & client later*/


StartView::StartView()
    : lblTitle("Cookie Clicker Game"),
    btnServer("Start Server"), btnClient("Connect as Client") {

    set_title("Cookie Clicker Game");
    set_default_size(550, 450);

    m_grid.set_margin(20);
    set_child(m_grid);

    m_grid.attach(lblTitle, 0, 0);
    m_grid.attach(btnServer, 0, 1);
    m_grid.attach(btnClient, 0, 2);

    btnServer.signal_clicked().connect(sigc::mem_fun(*this, &StartView::onServerButtonClicked));
    btnClient.signal_clicked().connect(sigc::mem_fun(*this, &StartView::onClientButtonClicked));

}


StartView::~StartView() {

}

void StartView::onServerButtonClicked() {
    // Create and run the server
    // CookieClicker serverWindow(true); // true indicates it's a server
    // serverWindow.show_all();
}

void StartView::onClientButtonClicked() {
    std::cout << "was pressed" << std::endl;
    // Create and run the client
    // CookieClicker clientWindow(false); // false indicates it's a client
    // clientWindow.show_all();
}
