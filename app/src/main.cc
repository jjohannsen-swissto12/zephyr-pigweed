/* Copyright (c) 2024 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

#define PW_LOG_MODULE_NAME "codelab"

#include "hello.h"
#include "pw_log/log.h"
#include <pwmled.h>

int main() {
	pw::StringBuffer<128> buffer;
	pw::InlineString<6> greeting = "Hello";
	pw::InlineString<6> name = "World";
	app::WelcomeMessage( buffer, greeting, name );
	PW_LOG_INFO( "%s", buffer.c_str() );

	// Get the device
	auto device = device_get_binding( "pwmled0" );
	if ( device == NULL ) {
		LOG_ERR( "Failed to get PWMLED device binding\n" );
		return 0;
	}

	LOG_INF( "device is %p, name is %s", device, device->name );

	pwmled_set_value( device, 50 );

	return 0;
}
