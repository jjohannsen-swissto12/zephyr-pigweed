# Links

* <https://mind.be/zephyr-tutorial-105-writing-a-simple-device-driver/>
* <https://zephyrproject.org/how-to-build-drivers-for-zephyr-rtos/>
* Custom API: <https://blog.golioth.io/how-to-write-a-zephyr-device-driver-with-a-custom-api/>

# Notes

## Clean Build

To clean the build and configure correct tools paths, do this in a console from the project root:

1. `rm -rf build`
2. `source third_party/pigweed/bootstrap.sh`
3. `west build -p -b kr260_r5 app/`

## File Structure

As much as possible, everything has been placed in ./drivers.

A couple of exceptions:

1. The "Device Tree Binding File" (.yaml) is placed in `./third_party/pigweed/environment/packages/zephyr/dts/bindings/led/xlnx,ssf-pwmled.yaml` since - apparently - that is where Zephyr looks for Device Tree Bindings files.
2. The top-level `./Kconfig` has been modified to include the Kconfig file from `./drivers`.
3. The top-level `./CMakeLists.txt` has been modified to include the `drivers` subdirectory.
4. Device driver include file: at the moment, it is located in both drivers/led/pwmled, app/src and in third_party/pigweed/environment/packages/zephyr/include/zephyr/drivers/pwmled.h. That should probably be fixed...