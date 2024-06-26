#!/bin/bash

sudo /sbin/losetup /dev/loop35 floppy.img
sudo mount /dev/loop35 /mnt
sudo cp src/kernel /mnt/kernel
sudo umount /dev/loop35
sudo /sbin/losetup -d /dev/loop35
