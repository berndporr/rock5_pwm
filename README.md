# Rock5 pwm

## Prerequsisites

Download from
https://www.armbian.com/rock-5b/
the image "Armbian 25.8.2 Bookworm Minimal / IOT".
the 
Call `armbian-config`:
  - upgrade to Debian "trixie"
  - Make sure you have kernel 6.18.x-current-rockchip64

## PWM motor drivers

Start `sudo nano /boot/armbianEnv.txt`, identify these lines and add/edit them that
they look like these:

```
console=display
overlay_prefix=rockchip
overlays=rk3588-pwm13-m0 rk3588-pwm8-m

```

This enables the PWM on the pins 33 (channel 1) and 35 (channel 2)
on the 40 pin header.

Create the group `gpio`:

```
groupadd gpio
```
and add yourself and other users to it who want to write to the PWM device.

Copy the file [90-gpio.rules](90-gpio.rules) to `/etc/udev/rules.d/`. This will
make sure that the PWM can accessed by any user who's in the gpio group.

The library and example programs how to control the motors are in [wheeleddrive](wheeleddrive).

## Demo program

```
cmake .
make
./pwm_test 
```

This generates a PWM at 50% duty cycle, then after a keypress at 25% and then at 75%.

## Credits

- Bernd Porr -  bernd.porr@glasgow.ac.uk
- Yixuan Zha
