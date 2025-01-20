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

1. The top-level `./Kconfig` has been modified to include the Kconfig file from `./drivers`.
3. The top-level `./CMakeLists.txt` has been modified to include the `drivers` subdirectory.
4. Device driver include file: at the moment, it is located in both drivers/led/pwmled, app/src and in third_party/pigweed/environment/packages/zephyr/include/zephyr/drivers/pwmled.h. That should probably be fixed...

# Memory Access

In order to allow read/write to the memory addresses used by the AXI bus, a region needs to be defined in the device tree.

If this is _not_ done, the MPU will halt the processor with a "BACKGROUND FAULT" error when attempting to access the AXI memory address.

To allow access, add the following to the `soc` node of the device tree:

```
axi_shared: memory@80020000 {
    compatible = "zephyr,memory-region", "mmio-sram";
    reg = <0x80020000 0x10000>;
    zephyr,memory-region = "AXI_SHARED";
    zephyr,memory-attr = <( DT_MEM_ARM(ATTR_MPU_RAM) )>;
};
```

