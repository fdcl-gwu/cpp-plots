#include "gtkmm-plplot.h"
#include <gtkmm/application.h>
#include <glibmm/miscutils.h>
#include <glib.h>
#include <gtkmm/window.h>
#include <gtkmm/switch.h>
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/grid.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/colorbutton.h>
#include <gtkmm/pagesetup.h>

namespace fdcl
{

class gui : public Gtk::Window
{
public:
    gui(void)
    {
        
    }
};  // end of class gui
}  // end of namespace fdcl


int main(int argc, char **argv)
{
    Glib::set_application_name("gtkmm-plplot-test1");
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(
        argc, argv, "com.fdcl-gwu.gtkmm-plplot-mwe");
    fdcl::gui gui; //(x_va, y_va, x_title, y_title);
    return app->run(gui);
}
    