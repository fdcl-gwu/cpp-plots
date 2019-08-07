#include "gtkmm-plplot.h"
#include <gtkmm/application.h>
#include <glibmm/miscutils.h>
#include <glib.h>
#include <gtkmm.h>
#include <gtkmm/window.h>
// #include <gtkmm/switch.h>
// #include <gtkmm/label.h>
// #include <gtkmm/comboboxtext.h>
#include <gtkmm/grid.h>
// #include <gtkmm/spinbutton.h>
// #include <gtkmm/colorbutton.h>
// #include <gtkmm/pagesetup.h>

#include <iostream>
// #include <thread>
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
    Gtk::PLplot::PlotData2D plot_ax;
    Gtk::PLplot::PlotData2D *plot_update;
    Gtk::PLplot::Plot2D *plot;
    Gtk::PLplot::Canvas canvas;
    Gtk::Grid grid;
public:
    gui(std::valarray<double> &x, std::valarray<double> &y):
        plot_ax(x, y)
    {
        // canvas.set_focus_on_click(false);
        // canvas.freeze_child_notify();
        canvas.set_can_focus(false);

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

        grid.attach(canvas, 0, 0, 1, 1);
        add(grid);
        grid.show_all();

        //create slot for timeout signal
        int timeout_value = 50; //in ms 20 Hz
        sigc::slot<bool> my_slot = sigc::mem_fun(*this, &gui::on_timeout);
        //connect slot to signal
        Glib::signal_timeout().connect(my_slot, timeout_value);
    }

    bool on_timeout(void)
    {
        canvas.remove_plot(*plot);

        pthread_mutex_lock(&mutex);
        plot_update = Gtk::manage(new Gtk::PLplot::PlotData2D(x, y));
        pthread_mutex_unlock(&mutex);

        plot = Gtk::manage(new Gtk::PLplot::Plot2D(*plot_update));
        canvas.add_plot(*plot);

        return true;
    }
};  // end of class gui
}  // end of namespace fdcl


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
    std::cout << "A" << std::endl;
    while (system_on)
    {
        pthread_mutex_lock(&mutex);
        y[0] = y[0] + 0.01;
        pthread_mutex_unlock(&mutex);
        std::cout << y[0] << std::endl;
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

    // Initialize mutex and condition variables.
    // pthread_mutex_init(&UAV_data_mumtex, NULL);

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
