#pragma once
#include <gtkmm.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

class Server : public Gtk::Window {
public:
    Server();   // Constructor for the Server class
    virtual ~Server();  // Destructor for the Server class

protected:
    int serverSocket;
    int clientSocket;
    std::string ipAddress;

    void startServer();
    void onBackButtonClicked();


    // Refer to the screenshots between Max & Dan
    // Sends Cookie Clicker data to the client for Client to load the game
    void PingClient(int clientSocket);


    //Test Function between Client and Server
    //TODO: listenForConnection, acceptClientConnection & updateConnectionLabel functions in theory can be combined into one function
    //void listenForConnections(); // Listens for connections from clients
    void acceptClientConnections(); // Accepts client connections

    //void updateConnectionLabel(); // Updates the connection label

    //void LoadGame(); // Load the game? I need to have the window shown in the Server window underneath the IP Address and Port labels

    //void sendGameDataToClient();
    /* Layout of Window */
    Gtk::Grid m_grid;
    Gtk::Label lblConnection, lblIP, lblPort;
    Gtk::Label lblClient;


    Gtk::Button btnBack;


};

