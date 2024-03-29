/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008-2009 coresystems GmbH
 * Copyright (C) 2014 Vladimir Serbinenko
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <southbridge/intel/lynxpoint/nvs.h>
#include "thermal.h"

static void acpi_update_thermal_table(global_nvs_t *gnvs)
{
	gnvs->tmps = CTDP_SENSOR_ID;

	gnvs->f1of = CTDP_NOMINAL_THRESHOLD_OFF;
	gnvs->f1on = CTDP_NOMINAL_THRESHOLD_ON;

	gnvs->f0of = CTDP_DOWN_THRESHOLD_OFF;
	gnvs->f0on = CTDP_DOWN_THRESHOLD_ON;

	gnvs->tcrt = CRITICAL_TEMPERATURE;
	gnvs->tpsv = PASSIVE_TEMPERATURE;
	gnvs->tmax = MAX_TEMPERATURE;
}

void acpi_create_gnvs(global_nvs_t *gnvs)
{
	/* Disable USB ports in S3 by default */
	gnvs->s3u0 = 0;
	gnvs->s3u1 = 0;

	/* Disable USB ports in S5 by default */
	gnvs->s5u0 = 0;
	gnvs->s5u1 = 0;

	// the lid is open by default.
	gnvs->lids = 1;

	acpi_update_thermal_table(gnvs);
}
