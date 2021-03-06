# dwm - dynamic window manager

dwm is an extremely fast, small, and dynamic window manager for X.


## Requirements

In order to build dwm you need the Xlib header files.

My build (by default) requires `dmenu`, `alacritty`(terminal), `librewolf`(browser), `pulseaudio`, `pamixer`(audio bindings), and my script `powermenu` (from [jtbx/scripts](https://github.com/jtbx/scripts)). Of course, you can change all of this in `config.h`.

You can install (nearly) all the dependencies on Arch with this command:

    sudo pacman -S alacritty pulseaudio pamixer ttf-jetbrains-mono

After this, you still need to decide on a custom build of `dmenu`, install `librewolf` or `librewolf-bin` from the AUR, and put `powermenu` from [jtbx/scripts](https://github.com/jtbx/scripts) in your $PATH. Again, you can remove the bindings in `config.h`.

## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can copy status.sh into your .xinitrc,

or do something like this:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
        sleep 1
    done &
    exec dwm


## Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
