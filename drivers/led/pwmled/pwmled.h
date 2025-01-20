#ifndef PWMLED_H
#define PWMLED_H

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include <zephyr/device.h>
#include <zephyr/types.h>

typedef int ( *pwmled_set_int )( const struct device *dev, int value );

__subsystem struct pwmled_driver_api {
	// Define function in API
	pwmled_set_int pwmled_set_value;
};

__syscall int pwmled_set_value( const struct device *dev, int value );

static inline int z_impl_pwmled_set_value( const struct device *dev,
										   int value ) {
	const struct pwmled_driver_api *api =
		(const struct pwmled_driver_api *)dev->api;
	if ( api->pwmled_set_value == NULL ) {
		return -ENOSYS;
	}
	return api->pwmled_set_value( dev, value );
}

#include <syscalls/pwmled.h>

#ifdef __cplusplus
}
#endif

#endif // PWMLED_H
