# SPDX-License-Identifier: Apache-2.0

zephyr_sources(
  soc.c
  system_evalsoc.c
)
zephyr_include_directories(.)
zephyr_include_directories(../NMSIS/Core/Include)

set(SOC_LINKER_SCRIPT ${ZEPHYR_BASE}/include/zephyr/arch/riscv/common/linker.ld CACHE INTERNAL "")
