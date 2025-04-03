#!/bin/bash

usbipd detach --busid 2-4
usbipd unbind --busid 2-4
usbipd bind --busid 2-4
usbipd attach --busid 2-4
usbipd list