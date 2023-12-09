#include <gtkmm/application.h>
#include <gtk/gtk.h>
/* TODO: Have something that works with Cookies / Per Second with Chrono or Normal Timer */

/* TODO: Max: The Program at the very moment has every object in main.cpp | This needs to be changed and has be to Object Oriented*/


static int cookies = 0; // Global variable to store the number of cookies
static GtkWidget *lab;   // Global label variable

static int cps = 1; // Store the number of cookies per second
static int cpc = 1; // Store the number of cookies per click

static int cpc_cost = 10; // Global variable to store the cost of the next upgrade
static int cps_cost = 10; // Global variable to store the cost of the next upgrade

// Function to update the number of cookies per second
static gboolean update_cps_callback(gpointer user_data) {
    // Increment the number of cookies per second
    cookies += cps * 1; // Multiply by the number of seconds

    // Update the label text
    gtk_label_set_text(GTK_LABEL(lab), g_strdup_printf("Number Of Cookies: %d", cookies));

    // Returning TRUE ensures the timer continues to run
    return TRUE;
}

static void upgrade_cps(GtkWidget *widget, gpointer data) {

    // Check if the player has enough cookies to buy the upgrade
    if (cps_cost >= cookies) {
        g_print("You don't have enough cookies. Upgrade CPS: %d. Cost: %d, Cookies: %d\n", cps, cps_cost, cookies);

    }
    else {
        // Subtract the cost of the upgrade from the number of cookies
        cookies -= cps_cost;
        // Increment the number of cookies per second
        cps++;
        // Increment the cost of the next upgrade
        cps_cost += 10;
        // Update the label text
        gtk_label_set_text(GTK_LABEL(lab), g_strdup_printf("Number Of Cookies: %d", cookies));
    }
}

static void upgrade_cpc(GtkWidget *widget, gpointer data) {
    if (cpc_cost > cookies) {
        // Print a message if the player doesn't have enough cookies for the upgrade
        g_print("You don't have enough cookies. Cost: %d, Cookies: %d\n", cpc_cost, cookies);
    } else {
        // Subtract the cost of the upgrade from the number of cookies
        cookies -= cpc_cost;
        // Increment the number of cookies per click
        cpc++;
        // Increment the cost of the next upgrade
        cpc_cost += 10;
        // Print a message indicating the upgrade
        g_print("Upgrade CPC: %d. Cost: %d, Cookies: %d\n", cpc, cpc_cost, cookies);
        // Update the label text
        gtk_label_set_text(GTK_LABEL(lab), g_strdup_printf("Number Of Cookies: %d", cookies));
    }
}
static void update_cookie(GtkWidget *widget, gpointer data) {
    // Increment the number of cookies
    cookies += cpc;

    // Print the number of cookies to the console
    g_print("Updating cookie: %d\n", cookies);

    // Update the label text
    gtk_label_set_text(GTK_LABEL(lab), g_strdup_printf("Number Of Cookies: %d", cookies));
}

static void app_activate(GApplication *app) {
    GtkWidget *win;
    GtkWidget *box;
    GtkWidget *btnCps;
    GtkWidget *btnCpc;

    // Create a timer to update the CPS
    g_timeout_add_seconds(1, update_cps_callback, NULL);

    // Rendering the window
    win = gtk_application_window_new(GTK_APPLICATION(app));
    // Set the title of the window
    gtk_window_set_title(GTK_WINDOW(win), "Game: Cookie Clicker");
    // Set the default window size to be 400x450
    gtk_window_set_default_size(GTK_WINDOW(win), 550, 450);

    // Create a vertical box to hold the buttons and label
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(win), box);

    // Button for upgrading CPS
    btnCps = gtk_button_new_with_label("Upgrade CPS");
    g_signal_connect(btnCps, "clicked", G_CALLBACK(upgrade_cps), NULL);
    gtk_box_append(GTK_BOX(box), btnCps);

    // Button for upgrading CPC
    btnCpc = gtk_button_new_with_label("Upgrade CPC");
    g_signal_connect(btnCpc, "clicked", G_CALLBACK(upgrade_cpc), NULL);
    gtk_box_append(GTK_BOX(box), btnCpc);

    // Button for clicking the cookie
    GtkWidget *btn = gtk_button_new_with_label("Click the Cookie!");
    g_signal_connect(btn, "clicked", G_CALLBACK(update_cookie), NULL);
    gtk_box_append(GTK_BOX(box), btn);

    // Label
    lab = gtk_label_new(g_strdup_printf("Number Of Cookies: %d", cookies));
    gtk_box_append(GTK_BOX(box), lab);

    // Present the window
    gtk_window_present(GTK_WINDOW(win));
}

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int stat;

    app = gtk_application_new("com.github.ToshioCP.lb1", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    stat = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return stat;
}

// Left this here tho obsolete af, refer to MyWindow.h for int main() function
/*auto app = Gtk::Application::create("org.gtkmm.example");

//Shows the window and returns when it is closed.
return app->make_window_and_run<HelloWorld>(argc, argv);*/

