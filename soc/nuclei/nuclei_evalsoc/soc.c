/*
 * Copyright (c) 2017 Jean-Paul Etienne <fractalclone@gmail.com>
 * Copyright (c) 2017 Palmer Dabbelt <palmer@dabbelt.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/init.h>
#include <zephyr/devicetree.h>
#include <zephyr/arch/riscv/csr.h>

void soc_early_init_hook(void)
{
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

}
