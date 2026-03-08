# tsc_khz
Linux kernel module that exports tsc clock frequency to sysfs

The TSC clock frequency can be read from `/sys/devices/system/cpu/tsc_khz`

## Build (Ubuntu 24.04)

Install prerequisites:
```bash
sudo apt install build-essential linux-headers-$(uname -r)
```

Build and load the module:
```bash
make
sudo insmod tsc_khz.ko
```

Verify:
```bash
cat /sys/devices/system/cpu/tsc_khz
```

Unload:
```bash
sudo rmmod tsc_khz
```
