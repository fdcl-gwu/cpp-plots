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
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>

#include <iostream>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 2

struct Params
{
    int argc;
    char **argv;
};

pthread_mutex_t mutex;


bool system_on = true;
std::valarray<double> x(20), y(20);
Params params;


namespace fdcl
{
class gui : public Gtk::Window
{
private:
    Gtk::PLplot::PlotData2D plot_ax, *plot_keep_ax;
    Gtk::PLplot::PlotData2D *plot_update;
    Gtk::PLplot::Plot2D *plot_keep;
    Gtk::PLplot::Plot2D *plot;
    Gtk::PLplot::Canvas canvas;
    Gtk::Grid grid;
    Gtk::Grid button_grid;

    Gtk::Button close;
public:
    gui(std::valarray<double> &x, std::valarray<double> &y):
        plot_ax(x, y),
        close("Exit")
    {
        canvas.set_can_focus(false);

        std::valarray<double> xx(10), yy(10);
        for (int i = 0; i < 10; i++)
        {
            xx[i] = i;
            yy[i] = 5.0;
        }
        plot_keep_ax = Gtk::manage(new Gtk::PLplot::PlotData2D(xx, yy));
        plot_keep = Gtk::manage(new Gtk::PLplot::Plot2D(*plot_keep_ax));
        canvas.add_plot(*plot_keep);

        plot = Gtk::manage(new Gtk::PLplot::Plot2D(plot_ax));
        canvas.add_plot(*plot);

        // // Set window size
        int w = 720, h = 580;
        set_default_size(w, h);
        Gdk::Geometry geometry;
        geometry.min_aspect = geometry.max_aspect = double(w) / double(h);
        set_geometry_hints(*this, geometry, Gdk::HINT_ASPECT);
        
        canvas.set_hexpand(true);
        canvas.set_vexpand(true);


        button_grid.set_row_spacing(5);
        button_grid.set_column_spacing(5);
        button_grid.set_column_homogeneous(false);
        close.signal_clicked().connect(sigc::mem_fun(*this, \
            &gui::on_close_button_clicked));
        button_grid.attach(close, 1, 0, 1, 1);

        grid.attach(button_grid, 0, 0, 1, 1);
        grid.attach(canvas, 0, 1, 1, 1);
        add(grid);
        grid.show_all();

        //create slot for timeout signal
        int timeout_value = 50; //in ms 20 Hz
        sigc::slot<bool> my_slot = sigc::mem_fun(*this, &gui::on_timeout);
        Glib::signal_timeout().connect(my_slot, timeout_value);

    }


    void on_close_button_clicked(void)
    {
        hide();
    }


    bool on_timeout(void)
    {
        pthread_mutex_lock(&mutex);
        canvas.remove_plot(*plot);
        // Gtk::PLplot::Plot *curr_plot;
        // auto curr_plot = canvas.get_plot(0);
        // canvas.remove_plot(*curr_plot);

        plot_update = Gtk::manage(new Gtk::PLplot::PlotData2D(x, y));
        plot = Gtk::manage(new Gtk::PLplot::Plot2D(*plot_update));
        // std::cout << plot << std::endl;
        canvas.add_plot(*plot);
        // canvas.remove_plot(1);

        // canvas.
        pthread_mutex_unlock(&mutex);

        return true;
    }

    bool on_plplot_drawing_area_double_click(GdkEventButton *event) 
    {
        if (event->type == GDK_2BUTTON_PRESS) 
        {
            // plplot_drawing_area.set_region(xmin, xmax, ymin, ymax);
        }
        return false;
    }
};  // end of class gui
}  // end of namespace fdcl

  bool Gtk::PLplot::Canvas::on_motion_notify_event(GdkEventMotion *event)
  {
      return true;
  }

void thread_gui(void)
{
    for (int i = 0; i < 20; i++)
    {
        x[i] = i;
        y[i] = 2.0 * i;
    }

    Glib::set_application_name("gtkmm-plplot-update");
    auto app = Gtk::Application::create(params.argc, params.argv, \
        "com.gwu.fdcl");

    fdcl::gui gui(x, y);
    app->run(gui);

    system_on = false;
    usleep(1000000);  // 1 second
    std::cout << "GUI: thread closed!" << std::endl;
}


void *thread_change_data(void *thread_id)
{
    while (system_on)
    {
        pthread_mutex_lock(&mutex);
        y[0] = y[0] + 0.01;
        pthread_mutex_unlock(&mutex);
        
        usleep(50000);  // 50 millis
    }

    std::cout << "Closing change data thread .."  << std::endl;
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    params.argc = argc;
    params.argv = argv;

    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    struct sched_param param;
    int fifo_max_prio, fifo_min_prio;

    // Set thread attributes.
    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    fifo_max_prio = sched_get_priority_max(SCHED_FIFO);
    fifo_min_prio = sched_get_priority_min(SCHED_FIFO);

    param.sched_priority = fifo_max_prio / NUM_THREADS;
    pthread_attr_setschedparam(&attr, &param);

    pthread_create(&threads[0], &attr, thread_change_data, (void *) 1);

    thread_gui();
    return 0;
}
