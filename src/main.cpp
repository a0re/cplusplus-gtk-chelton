#include <gtkmm.h>
#include "CookieClicker.h"
#include "Server.h"
#include "Client.h"
#include "StartView.h"


int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    StartView startView;
    return app->make_window_and_run<StartView>(argc, argv);
};

// TODO: Max: Format the GAME, Add Error Handling, Functions moved to files, Clean Up your Code you messy fuck!

// If Time Allows Possibly add Live CPS