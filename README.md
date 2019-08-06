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
    ```
    brew install gtkmm
    brew install gtkmm3
    brew install glade
    ```

# Quick Troubleshooting
* OSX: 
    * Package 'libffi', required by 'gobject-2.0', not found: `export PKG_CONFIG_PATH="/usr/local/opt/libffi/lib/pkgconfig"`
    * Package 'icu4c' not found: `export PKG_CONFIG_PATH="/usr/local/opt/icu4c/lib/pkgconfig`