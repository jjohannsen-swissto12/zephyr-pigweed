zephyr_library()
zephyr_syscall_header(./pwmled.h)
zephyr_include_directories(.)
zephyr_library_sources(pwmled.c)
