#include <gtkmm.h>
#include "CookieClicker.h"
#include "Server.h"
#include "Client.h"
#include "StartView.h"

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.examples.base");

    return app->make_window_and_run<Client>(argc, argv);
};

// TODO: Max: Format the GAME, Add Error Handling, Functions moved to files, Clean Up your Code you messy fuck!

// If Time Allows Possibly add Live CPS
// James: Self Reminder - Testing can only be done the same ethernet connection or hotspot same network Wifi didn't work for some reason