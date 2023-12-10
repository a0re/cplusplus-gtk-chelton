#include "MyWindow.h"
#include "Server.h"
#include "Client.h"
#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>

void testServer() {
    Server server;

    // Start the server
    server.startServer();

    // Attempt to accept a connection (you may want to run this in a separate thread or process)
    std::thread clientThread([&]() {
        Client client;
        client.connectToServer("127.0.0.1", 5050);
        // Add any client-server interaction testing here
    });

    // Allow some time for the server to start and accept connections
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Try to accept connections
    server.acceptConnections();

    // Assert that the client connected successfully
    assert(server.getClientSocket() != -1);

    // Optionally add more assertions or testing logic based on your application

    // Clean up
    clientThread.join();  // Wait for the client thread to finish
}


int main(int argc, char *argv[])
{
    testServer();

    std::cout << "All tests passed!\n";

    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    return app->make_window_and_run<MyWindow>(argc, argv);

};

// TODO: Max: Format the GAME, Add Error Handling, Functions moved to files, Clean Up your Code you messy fuck!

// If Time Allows Possibly add Live CPS