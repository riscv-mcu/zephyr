/*
 * Copyright (c) 2017 Jean-Paul Etienne <fractalclone@gmail.com>
 * Copyright (c) 2017 Palmer Dabbelt <palmer@dabbelt.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/init.h>
#include <zephyr/devicetree.h>
#include "evalsoc.h"

volatile unsigned long NucleiCpuIRegionBase = 0xFFFFFFFF;
#ifndef BOOT_HARTID
#define BOOT_HARTID                 0
#endif

void nuclei_cpu_init(void)
{
    // TODO to make it possible for configurable boot hartid
    unsigned long hartid = __get_hart_id();
    unsigned long mcfginfo = __RV_CSR_READ(CSR_MCFG_INFO);

    /* __ICACHE_PRESENT and __DCACHE_PRESENT are defined in evalsoc.h */
    // For our internal cpu testing, they want to set evalsoc __ICACHE_PRESENT/__DCACHE_PRESENT to be 1
    // __CCM_PRESENT is still default to 0 in evalsoc.h, since it is used in core_feature_eclic.h to register interrupt, if set to 1, it might cause exception
    // but in the cpu, icache or dcache might not exist due to cpu configuration, so here
    // we need to check whether icache/dcache really exist, if yes, then turn on it
#if defined(__ICACHE_PRESENT) && (__ICACHE_PRESENT == 1)
    if (ICachePresent()) { // Check whether icache real present or not
        EnableICache();
    }
#endif
#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1)
    if (DCachePresent()) { // Check whether dcache real present or not
        EnableDCache();
    }
#endif

    /* Do fence and fence.i to make sure previous ilm/dlm/icache/dcache control done */
    __RWMB();
    __FENCE_I();

    // BOOT_HARTID is defined <Device.h> and also controlled by BOOT_HARTID in conf/evalsoc/build.mk
#ifndef CFG_IREGION_BASE_ADDR       // Need to probe the cpu iregion base address
    if (hartid == BOOT_HARTID) { // only done in boot hart
        // IREGION INFO MUST BE AFTER L1/L2 Cache enabled and SMP enabled if SMP present
        NucleiCpuIRegionBase = (__RV_CSR_READ(CSR_MIRGB_INFO) >> 10) << 10;
    } else {
        // wait for correct iregion base addr is set by boot hart
        while (NucleiCpuIRegionBase == 0xFFFFFFFF);
    }
#endif

#if defined(RUNMODE_L2_EN)
    if ((mcfginfo & (0x1 << 11)) && SMP_CTRLREG(__SMPCC_BASEADDR, 0x4) & 0x1 ) { // L2 Cache present
#if RUNMODE_L2_EN == 1
        // Enable L2, disable cluster local memory
        SMP_CTRLREG(__SMPCC_BASEADDR, 0x10) = 0x1;
        SMP_CTRLREG(__SMPCC_BASEADDR, 0xd8) = 0x0;
        __SMP_RWMB();
#else
        // Disable L2, enable cluster local memory
        SMP_CTRLREG(__SMPCC_BASEADDR, 0x10) = 0x0;
        // use as clm or cache, when l2 disable, the affect to ddr is the same, l2 is really disabled
        SMP_CTRLREG(__SMPCC_BASEADDR, 0xd8) = 0;//0xFFFFFFFF;
        __SMP_RWMB();
#endif
    }
#endif

    // Enable BPU
    __RV_CSR_SET(CSR_MMISC_CTL, MMISC_CTL_BPU);

#if defined(__CCM_PRESENT) && (__CCM_PRESENT == 1)
    // NOTE: CFG_HAS_SMODE and CFG_HAS_UMODE are defined in auto generated cpufeature.h if present in cpu
#if defined(CFG_HAS_SMODE) || defined(CFG_HAS_UMODE)
    EnableSUCCM();
#endif
#endif
}
void soc_early_init_hook(void)
{
#if 0
	#include <zephyr/arch/riscv/csr.h>
	unsigned long mcfginfo = csr_read(0xFC2);

	// Enable ICache and DCache when present
	if (mcfginfo & (1<<9)) {
		csr_set(0x7CA, (1<<0));
	}
	if (mcfginfo & (1<<10)) {
		csr_set(0x7CA, (1<<16));
	}
	// Do fence
	__asm__ volatile ("fence");
	__asm__ volatile ("fence.i");
#else
	nuclei_cpu_init();
#endif

}
