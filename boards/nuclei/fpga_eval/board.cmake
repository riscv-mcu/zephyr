# Copyright (c) 2021 Tokita, Hiroshi <tokita.hiroshi@gmail.com>
# Copyright (c) 2024 Huaqi Fang <hqfang@nucleisys.com>
# SPDX-License-Identifier: Apache-2.0

# Need to use Nuclei OpenOCD which can be downloaded from https://www.nucleisys.com/download.php#tools

board_runner_args(openocd "--cmd-pre-load=evalsoc-pre-load")
board_runner_args(openocd "--cmd-load=evalsoc-load")
board_runner_args(openocd "--cmd-post-verify=evalsoc-post-verify")

include(${ZEPHYR_BASE}/boards/common/openocd.board.cmake)
