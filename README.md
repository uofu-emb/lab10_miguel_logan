![example workflow](https://github.com/uofu-emb/lab10_miguel_logan/actions/workflows/main.yml/badge.svg)

# sleep_ms (running directly in main)
1.85V: 80mA, 148mW
3.3V:  22mA, 72.5mW
5.5V: 10mA, 55mW

# sleep_ms (running in a FreeRTOS Task)
1.85V: 79mA, 146mW
3.3V: 22mA, 72.5mW
5.5V: 10mA, 55mW

# FreeRTOS Thread
1.85V: 112mA, 207.2mW
3.3V: 25mA, 82.5mW
5.5V: 12mA, 66mW

# Busy Loop 100% CPU Utilization
1.85V: 90mA, 166.5mW
3.3V: 25mA, 82.5mW
5.5V: 11mA, 60.5mW


# External Signal Interrupt
1.85V:
3.3V:
5.5V:

This is the last part of the lab that we needed to complete everything but we did not get a chance to use the trigger to perform external interrupts at some freq f. 


# Sleep Demo (Sleep current/power->awake current/power)
1.85V: 45mA->45mA, 83.25mW->83.25mW
3.3V: 0->22mA, 0->72.6mW
5.5V: 0->10mA, 0->55mW

# Dormant Demo (Awake current/power->dormant current/power)
1.85V: 70mA->21mA, 129.5mW->38.85mW
3.3V: 22mA->0mA, 72.6mW->0mW
5.5V: 10mA->0mA, 55mW->0mW



# Renode setup
The Raspberry Pico needs configuration files for Renode to work properly.

* On MacOS, the installation location is `/Applications/Renode.app/Contents/MacOs`
* On Linux, the location for Debian, Fedora, and Arch is `/opt/renode`
* On Windows, the location is `C://Program Files/Renode`

To add the Pico configuration files:
1. Copy `rp2040_spinlock.py` and `rp2040_divider.py` to the `scripts/pydev` directory of your Renode installation.
1. Copy `rpi_pico_rp2040_w.repl` to the `platforms/cpus` directory.


Removing the call to vTaskScheduler() stops code from being able to execute because it requires it to do anything. 
