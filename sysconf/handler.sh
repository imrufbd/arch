#!/bin/bash

# fix acpid
# PID=$(pgrep dbus-launch)
# USER=$(ps -o user --no-headers $PID)
# USERHOME=$(getent passwd $USER | cut -d: -f6)
# 
# export XAUTHORITY="$USERHOME/.Xauthority"
# for x in /tmp/.X11-unix/*; do
#     displaynum=`echo $x | sed s#/tmp/.X11-unix/X##`
#     if [ x"$XAUTHORITY" != x"" ]; then
#         export DISPLAY=":$displaynum"
#     fi
# done
# 
# # PATH
# export PATH=$USERHOME/.local/bin:/bin:/usr/bin:/sbin:/usr/sbin


# Default acpi script that takes an entry for all actions

case "$1" in
    button/power)
        case "$2" in
            PBTN|PWRF)
                logger 'PowerButton pressed'
                ;;
            *)
                logger "ACPI action undefined: $2"
                ;;
        esac
        ;;
    button/sleep)
        case "$2" in
            SLPB|SBTN)
                logger 'sleeping...'
                sudo -A zzz
                ;;
            *)
                logger "ACPI action undefined: $2"
                ;;
        esac
        ;;
    ac_adapter)
        case "$2" in
            AC|ACAD|ADP0)
                case "$4" in
                    00000000)
                        logger 'AC unpluged'
                        ;;
                    00000001)
                        logger 'AC pluged'
                        ;;
                esac
                ;;
            *)
                logger "ACPI action undefined: $2"
                ;;
        esac
        ;;
    battery)
        case "$2" in
            BAT0)
                case "$4" in
                    00000000)
                        logger 'Battery online'
                        ;;
                    00000001)
                        logger 'Battery offline'
                        ;;
                esac
                ;;
            CPU0)
                ;;
            *)  logger "ACPI action undefined: $2" ;;
        esac
        ;;
    button/lid)
        case "$3" in
            close)
                logger 'Lid closed sleeping...'
                sudo -A zzz
                ;;
            open)
                logger 'LID opened'
                ;;
            *)
                logger "ACPI action undefined: $3"
                ;;
    esac
    ;;
    *)
        logger "ACPI group/action undefined: $1 / $2"
        ;;
esac

# vim:set ts=4 sw=4 ft=sh et:
