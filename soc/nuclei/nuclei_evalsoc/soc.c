/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include "evalsoc.h"

#ifndef CFG_IREGION_BASE_ADDR
// If not in the Zephyr environment, this variable is defined in system_evalsoc.c; when in Zephyr, it's defined here.
// Note: Use of this variable is discouraged. Instead, use the __IREGION_BASEADDR macro defined in evalsoc.h.
volatile unsigned long CpuIRegionBase = 0xFFFFFFFF;
#endif


void soc_prep_hook(void)
{

}

void soc_early_init_hook(void)
{
#ifndef CFG_IREGION_BASE_ADDR
	CpuIRegionBase = (__RV_CSR_READ(CSR_MIRGB_INFO) >> 10) << 10;
#endif
}

void soc_per_core_init_hook(void)
{
#if defined(__CCM_PRESENT) && (__CCM_PRESENT == 1)
    // NOTE: CFG_HAS_SMODE and CFG_HAS_UMODE are defined in auto generated cpufeature.h if present in cpu
#if defined(CFG_HAS_SMODE) || defined(CFG_HAS_UMODE)
    EnableSUCCM();
#endif
#endif

}
