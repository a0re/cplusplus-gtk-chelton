#include <iostream>
#include "StartView.h"
#include "Server.h"
#include "Client.h"


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
    std::cout << "Server Button Clicked" << std::endl;

    // Create an instance of the Server class
    // Server server;

    // Hide the StartView
    // hide();

    // Make the server view/window visible
    // server.set_visible(true);
}



void StartView::onClientButtonClicked() {
    std::cout << "Server Button Clicked" << std::endl;

    // Create an instance of the Server class
    // Client client;

    // Make the server view/window visible
    // client.set_visible(true);
}

