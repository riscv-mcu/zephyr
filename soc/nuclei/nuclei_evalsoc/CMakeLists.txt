# SPDX-License-Identifier: Apache-2.0

zephyr_sources(
  entry.S
  soc.c
)
zephyr_include_directories(.)
zephyr_include_directories(../NMSIS/Core/Include)
# Configure ROM_START using init.ld for Nuclei RISC-V SoC entry point defined in entry.S
zephyr_linker_sources(ROM_START SORT_KEY 0x0 init.ld)

set(SOC_LINKER_SCRIPT ${ZEPHYR_BASE}/include/zephyr/arch/riscv/common/linker.ld CACHE INTERNAL "")
