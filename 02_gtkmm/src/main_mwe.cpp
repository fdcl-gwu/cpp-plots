/* 
 * Copyright (c) 2019 Flight Dynamics and Control Lab
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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