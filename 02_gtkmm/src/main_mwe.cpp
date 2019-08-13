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
private:
    Gtk::PLplot::PlotData2D plot_ax;
    Gtk::PLplot::Plot2D plot;
    Gtk::PLplot::Canvas canvas;
    Gtk::Grid grid;
public:
    gui(std::valarray<double> &x, std::valarray<double> &y):
        plot_ax(x, y),
        plot(plot_ax),
        canvas(plot)
    {
        // Set window size
        int w = 720, h = 580;
        set_default_size(w, h);
        Gdk::Geometry geometry;
        geometry.min_aspect = geometry.max_aspect = double(w) / double(h);
        set_geometry_hints(*this, geometry, Gdk::HINT_ASPECT);
        
        canvas.set_hexpand(true);
        canvas.set_vexpand(true);

        grid.attach(canvas, 0, 0, 1, 1);
        add(grid);
        grid.show_all();
    }
};  // end of class gui
}  // end of namespace fdcl


int main(int argc, char **argv)
{
    std::valarray<double> x(20), y(20);

    for (int i = 0; i < 20; i++)
    {
        x[i] = i;
        y[i] = 2.0 * i;
    }

    Glib::set_application_name("gtkmm-plplot-mwe");
    auto app = Gtk::Application::create(argc, argv, \
        "com.fdcl-gwu.gtkmm-plplot-mwe");
    fdcl::gui gui(x, y);
    app->run(gui);
    return 0;
}