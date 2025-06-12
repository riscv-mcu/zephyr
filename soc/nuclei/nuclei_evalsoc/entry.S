#include <zephyr/toolchain.h>
#include <zephyr/arch/cpu.h>
#include <zephyr/arch/riscv/csr.h>

/**
 * Nuclei RISC-V Core Startup Code
 *
 * This code handles the initial boot sequence for Nuclei RISC-V processors.
 * Key operations include:
 * 1. Disabling global interrupts for safe initialization
 * 2. SMP (Symmetric Multi-Processing) and Cache Controller configuration
 *    - Detects and configures SMP features
 *    - Handles both primary and secondary core boot sequences
 *    - Configures L2 cache if present
 * 3. L1 Cache initialization
 *    - Enables L1 instruction cache if present
 *    - Enables L1 data cache if present
 * 4. Misc configurations:
 *    - Sets up Branch Prediction Unit (BPU)
 *    - Configures NMI vector
 *    - Enables/Disables Zc extension based on compiler settings
 *    - Configures performance counters (mcycle and minstret)
 * 5. Finally transfers control to the common start routine
 *
 * This code is crucial for proper initialization of Nuclei RISC-V cores
 * and must execute before any C code runs.
 */
GTEXT(__nuclei_start)
SECTION_FUNC(init, __nuclei_start)
	/* Disable Global Interrupt */
	csrc mstatus, MSTATUS_MIE

	/* Check whether SMP & CC Present */
	/* Get mcfg_info csr to a0 */
	csrr a0, 0xfc2 /* mcfg_info csr */
	li t0, 1<<11 /* SMP bit */
	and t0, a0, t0
	beqz t0, __nuclei_enable_l1_icache
__nuclei_smp_cc_config:
	/* SMP & CC Present */
	/* Get hartid to a1 */
	csrr a1, mhartid
	/* Get SMP&CC Base Address to a2 */
	csrr a2, 0x7f7
	srai a2, a2, 10 // a2 = a2 >> 10
	slli a2, a2, 10 // a2 = a2 << 10
	li t0, 0x40000
	add a2, a2, t0 // a2 = a2 + 0x40000

	li t0, CONFIG_RV_BOOT_HART
	beq a1, t0, __nuclei_boot_first_core
	j __nuclei_boot_secondary_core

__nuclei_boot_first_core:
	/* Check whether L2 Cache is present */
	lw t0, 0x4(a2)
	addi t0, t0, 1
	beqz t0, __nuclei_enable_smp
	sw x0, 0xd8(a2) /* Disable CLM */
	lw t0, 0x10(a2)
	ori t0, t0, 1<<0
	sw t0, 0x10(a2) /* Enable L2 Cache */
__nuclei_enable_smp:
	li t0, 0xFFFFFFFF
	sw t0, 0xc(a2)  /* Enable SMP */
	fence
	j __nuclei_enable_l1_icache

__nuclei_boot_secondary_core:
	/* Wait for SMP to be enabled */
	lw t0, 0xc(a2)
	beqz t0, __nuclei_boot_secondary_core

__nuclei_enable_l1_icache:
	li t0, 1<<9 /* i cache bit */
	and t0, a0, t0
	beqz t0, __nuclei_enable_l1_dcache
	csrsi 0x7ca, 1<<0 /* Enable L1 I Cache */
__nuclei_enable_l1_dcache:
	li t0, 1<<10 /* d cache bit */
	and t0, a0, t0
	beqz t0, __nuclei_config_misc
	li t0, 1<<16 /* Enable L1 D Cache */
	csrs 0x7ca, t0

__nuclei_config_misc:
	fence
	fence.i
	li t0, 1<<3
	csrs 0x7d0, t0 /* Enable BPU */
	li t0, 1<<9
	csrs 0x7d0, t0 /* The value of mnvec is the same as the value of mtvec, mcause.EXCCODE of NMI is 0xfff */
	li t0, 1<<7    /* Enable Zc extension if compiler wants to use Zc extension */
#if defined(__riscv_zcmp) || defined(__riscv_zcmt)
	csrs 0x7d0, t0
#else
	csrc 0x7d0, t0
#endif
	csrci 0x320, 0x5 /* Enable mcycle and minstret counter */

__nuclei_enter_start:
	/* Jump to common start */
	/* Transfer control to the common start function (__start),
	 * which initializes the system and starts the main application.
	 */
	tail __start
