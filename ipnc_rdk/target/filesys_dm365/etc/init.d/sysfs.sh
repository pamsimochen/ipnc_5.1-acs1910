#!/bin/sh

if [ -e /proc ] && ! [ -e /proc/mounts ]; then
  mount -t proc proc /proc
fi

if [ -e /sys ] && grep -q sysfs /proc/filesystems; then
  echo +++++++++++++++++++++++++++++++++++++++++++++++++++++MOUNTING SYSFS	
  mount sysfs /sys -t sysfs
fi

exit 0
