#!/bin/sh
SKIPMOUNT=false
PROPFILE=true
POSTFSDATA=true
LATESTARTSERVICE=true
REPLACE="
"
ui_print ""
ui_print "*************************************"
ui_print "*       REXX SAVE YOUR BATTERY      *"
ui_print "*         Zyarexx @Telegram         *"
ui_print "*************************************"
ui_print ""
sleep 2
ui_print "- for saving battery and to use it more efficient"
ui_print "  without losing much performance. The module will"
ui_print "  need it self a minute or more to start working" 
ui_print "  upon each reboot"

ui_print "- Extracting module files"

unzip -o "$ZIPFILE" 'RSYB' -d "$MODPATH" >&2
chmod +x "$MODPATH/RSYB"

ui_print ""
ui_print "- Installation"
ui_print ""
