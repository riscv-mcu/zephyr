# Copyright (c) 2024 Huaqi Fang <hqfang@nucleisys.com>
# SPDX-License-Identifier: Apache-2.0

# Need to use Nuclei OpenOCD which can be downloaded from https://www.nucleisys.com/download.php#tools

set(OPENOCD_RAM_LOAD YES)

board_runner_args(openocd "--config=${BOARD_DIR}/support/openocd.cfg")

if(OPENOCD_RAM_LOAD)
board_runner_args(openocd "--use-elf")
endif()

include(${ZEPHYR_BASE}/boards/common/openocd.board.cmake)
