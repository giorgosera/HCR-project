#!/bin/bash
# Path: /usr/local/bin/gnome-terminal
if [ "x$*" != "x" ]; then
  /usr/bin/gnome-terminal "$@"
else
  pgrep -u "$USER" gnome-terminal | grep -qv "$$"
  if [ "$?" == "0" ]; then
    WID=`xdotool search --class "gnome-terminal" | head -1`
    xdotool windowfocus $WID
    xdotool key ctrl+shift+t
    wmctrl -i -a $WID
  else
    /usr/bin/gnome-terminal
  fi
fi

rosrun ROSARIA RosAria

if [ "x$*" != "x" ]; then
  /usr/bin/gnome-terminal "$@"
else
  pgrep -u "$USER" gnome-terminal | grep -qv "$$"
  if [ "$?" == "0" ]; then
    WID=`xdotool search --class "gnome-terminal" | head -1`
    xdotool windowfocus $WID
    xdotool key ctrl+shift+t
    wmctrl -i -a $WID
  else
    /usr/bin/gnome-terminal
  fi
fi
