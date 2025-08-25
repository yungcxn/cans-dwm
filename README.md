# cans-dwm - my own dwm fork

dwm is an extremely fast, small, and dynamic window manager for X.

This fork of mine implements my config.

## Dones and Todos

- [x] Repository cleanup (e.g. `.def.h` or man-page removal)
- [x] Custom `config.h` setup
- [x] `~/.config/cans-dwm/autostart.sh` patch
- [x] `-debug` arg to skip `autostart.sh` and run the `-debug.sh` script
- [x] `smartkillclient` to jump back to last tag on empty tag window kill
- [x] `movestack` to focus on stack
- [x] `focustag` to focus tag by number
- [x] `focusnext` and `focusprev` to focus cycle
- [x] `tagandview` to move window and also view tag where window was moved to
- [x] `spawntofree` to spawn windows on free workspaces
- [x] `nexttagged` to cycle through workspaces
- [x] `mfact` and `smfact` modification
- [ ] `mfact` and `smfact` rewrite to calculate windows on the basis of pixel borders
- [ ] Better bar rewrite

## Requirements

In order to build dwm you need the Xlib header files.


## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

    exec exec-dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec cans-dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec cans-dwm


## Autostart

- `~/.config/cans-dwm/autostart.sh` is ran automatically
- with `cans-dwm -debug` the `~/.config/cans-dwm/autostart-debug.sh` script is ran
