#include "pwmled.h"
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>

#define LOG_MODULE_NAME xlnx_ssf_pwmled
#define LOG_LEVEL CONFIG_GPIO_LOG_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER( LOG_MODULE_NAME );

#define DT_DRV_COMPAT xlnx_ssf_pwmled

struct pwmled_config {
	mm_reg_t base;
};

struct pwmled_data {
	int value;
};

static inline int pwmled_impl_setvalue( const struct device *dev, int value ) {
	const struct pwmled_config *config = dev->config;

	LOG_INF( "H pwmled_impl_setvalue. Base addr: 0x%08lx, value: %d",
			 config->base, value );

	sys_write32( value, config->base );

	return 0;
}

static const struct pwmled_driver_api pwmled_impl_driver_api = {
	.pwmled_set_value = pwmled_impl_setvalue,
};

static int pwmled_init( const struct device *dev ) {
	// No init - just log
	const struct pwmled_config *config = dev->config;
	LOG_INF( "pwmled_init, address: 0x%08lx", config->base );

	return 0;
}

#define PWMLED_DEVICE( n )                                                     \
	static struct pwmled_data pwmled_data_##n;                                 \
	static const struct pwmled_config pwmled_config_##n = {                    \
		.base = DT_INST_REG_ADDR( n ),                                         \
	};                                                                         \
                                                                               \
	DEVICE_DT_INST_DEFINE( n, pwmled_init, NULL, &pwmled_data_##n,             \
						   &pwmled_config_##n, POST_KERNEL,                    \
						   CONFIG_KERNEL_INIT_PRIORITY_DEVICE,                 \
						   &pwmled_impl_driver_api );

DT_INST_FOREACH_STATUS_OKAY( PWMLED_DEVICE )

void test() {}