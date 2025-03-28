/*
 * Copyright (c) 2017 Jean-Paul Etienne <fractalclone@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file SoC configuration macros for the Nuclei Evalsoc processor
 */

#ifndef __RISCV_NUCLEI_EVAL_SOC_H_
#define __RISCV_NUCLEI_EVAL_SOC_H_


#define NUCLEI_TLCLK_BASE_FREQUENCY \
	DT_PROP_BY_PHANDLE_IDX(DT_NODELABEL(tlclk), clocks, 0, clock_frequency)
#define NUCLEI_TLCLK_DIVIDER DT_PROP(DT_NODELABEL(tlclk), clock_div)
#define NUCLEI_PERIPHERAL_CLOCK_FREQUENCY \
	(NUCLEI_TLCLK_BASE_FREQUENCY / NUCLEI_TLCLK_DIVIDER)

#endif /* __RISCV_NUCLEI_EVAL_SOC_H_ */
