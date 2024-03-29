/*
 * This file is part of the coreboot project.
 *
 * Copyright 2016 Google, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/cpu.h>
#include <cbmem.h>
#include <console/console.h>
#include <cpu/x86/mtrr.h>
#include <main_decl.h>
#include <program_loading.h>
#include <timestamp.h>

/*
 * Systems without a native coreboot cache-as-ram teardown may implement
 * this to use an alternate method.
 */
__weak void late_car_teardown(void) { /* do nothing */ }

void main(void)
{
	printk(BIOS_DEBUG, "DEBUG: Hello from very early postcar!");
	late_car_teardown();

	console_init();
	printk(BIOS_DEBUG, "DEBUG: Hello from early postcar, after console_init!");

	/* Recover cbmem so infrastruture using it is functional. */
	cbmem_initialize();

	timestamp_add_now(TS_START_POSTCAR);

	display_mtrrs();

	/* Load and run ramstage. */
	run_ramstage();
}
