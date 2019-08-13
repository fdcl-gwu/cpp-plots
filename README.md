# Plotting with C++

C++ is an extremely useful language, especially when it comes to working with hardware.
One of the limitations with using C++ is inflexibility when it comes to plotting data. 
This repository explores different ways to plot with C++.

This repository uses the below three different apporaches, and each may be useful in different scenarios.
1. [Matplotlib wrapper](#matplotlib-wrapper)
2. [gtkmm](#gtkmm)
3. [Local server-client connection](#local-server-client-connection)


## Matplotlib Wrapper
This method uses the [matplotlib-cpp](https://github.com/lava/matplotlib-cpp) written by [Benno Evers](https://github.com/lava).
This library basically gives you a Python like functions to be used directly inside C++ code.

### Dependencies
* Matplotlib Wrapper
    ```
    sudo apt-get install python-tk python-numpy python2.7-dev python-dev3
    pip install matplotlib numpy
    ```

    If you already don't have one, create a file named `matplotlibrc` in `~/.matplotlib` and add this line to the file.
    ```
    backend: TkAgg
    ```

### Running the Code
* Compiling the code
    ```
    cd 01_matplotlib-wrapper 
    mkdir build && cd build
    cmake ../
    make
    ```
* Running the program:
    * Draw a line plot with static data: `./plot_line`
    * Draw a plot with changing data: `./animate`

## gtkmm
This method uses [gtkmm-plplot](https://github.com/tschoonj/gtkmm-plplot) by [Tom Schoonjans](https://github.com/tschoonj).
This library uses [PLplot](http://plplot.sourceforge.net/), and brings it's functions to gtkmm.
This has been successfully tested in both Ubuntu 18.04 and macOS Mojave.

### Dependencies
* Linux
    ```
    sudo apt-get install libgtkmm-3.0-dev
    sudo apt-get install libltdl3-dev libqhull-dev libpango1.0-0 libplplot-dev
    ```

* MacOS
    ```
    brew install gtkmm gtkmm3 glade plplot
    brew install tschoonj/tap/gtkmm-plplot
    ```

### Running the Code
* Compiling the code
    ```
    cd 02_gtkmm 
    mkdir build && cd build
    cmake ../
    make
    ```
* Running the program:
    * Hello world (just an application screen with button): `./hello_world`
    * A copy of a PLplot example which includes a plot and some interactive plots: `./hello_world_plot`
    * A plot example with minimum requirements: `./minimal_working_example`
    * A plot with utlizing multithreading: `./updating_plot`

### Known Issues
* At least in macOS Mojave, the main GUI window needs to called in the main thread. So using multithreading requires the threads to not to be joined. Users need to stick to other measures to make sure that the program prematurely ends once a single thread exits.
* The app crashes randomly when the mouse is being moved over the drawing canvas area.

### Quick Troubleshooting
* OSX: 
    * Package 'libffi', required by 'gobject-2.0', not found: `export PKG_CONFIG_PATH="/usr/local/opt/libffi/lib/pkgconfig"`
    * Package 'icu4c' not found: `export PKG_CONFIG_PATH="/usr/local/opt/icu4c/lib/pkgconfig`

## Local Server-Client Connection
All the methods discussed so far uses different libraries developed in C++.
In contrast, this method uses a server-client communication between C++ code and Python code so that all the plots are drawn using Python's Matplotlib.
This does not suffer from issues related to multithreading as discussed above.
Also, has the potential to explore all the Matplotlib functions even after the updates without waiting for some third party developers (most of whome develop them as a service to others in spite of working on actual jobs) to update their libraries.

This method works as follows:
* C++ code:
    This is the server connection. C++ code does some calculations and send those data which requires poltting to the Python code.
* Python code:
    This is the client connection. Python code receives the data from the C++ code and plots them.

Both of these codes utilize multithreading to so that data transmission and plotting work independently.

### C++ code
```
cd 03_server-client 
mkdir build && cd build
cmake ../
make
./server
```

**NOTE**: server (C++ code) must be run first.

### Python code
Below instructions assuems you have installed Anaconda (or atleast Python with numpy and matplotlib) in your system.
```
cd 03_server-client/scripts
python client.py
```
**NOTE**: client (Python code) must be run while the server (C++ code) is running.
