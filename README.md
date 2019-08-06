# Dependencies
* Matplotlib Wrapper
    ```
    sudo apt-get install python-tk python-numpy python2.7-dev python-dev3
    pip install matplotlib numpy
    ```

    Create a file named `matplotlibrc` in `~/.matplotlib` and add this line to the file.
    ```
    backend: TkAgg
    ```

* GTKMM
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

# Quick Troubleshooting
* OSX: 
    * Package 'libffi', required by 'gobject-2.0', not found: `export PKG_CONFIG_PATH="/usr/local/opt/libffi/lib/pkgconfig"`
    * Package 'icu4c' not found: `export PKG_CONFIG_PATH="/usr/local/opt/icu4c/lib/pkgconfig`