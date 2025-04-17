.. zephyr:board:: nuclei_fpga_eval

Overview
********

The Nuclei FPGA Evaluation Board is common name for FPGA development boards such as
DDR200T/MCU200T/KU060/VCU118/VU19P etc.

You can flash nuclei evaluation soc bitstream into these boards with Nuclei
RISC-V CPU such as 200/300/600/900/1000 series.

Default baudrate for zephyr on Nuclei FPGA Evaluation Board is **115200**.

Programming and debugging
*************************

You need to download Nuclei OpenOCD from https://nucleisys.com/download.php,
and extract it and add it to system PATH.

And you also need to have a HummingBird Debugger to connect to ``nuclei_fpga_eval``
board and debug it.

- HummingBird Debugger: https://nucleisys.com/developboard.php#debuggerkit

Building
========

Applications for the ``nuclei_fpga_eval`` board configuration can be built as
usual (see :ref:`build_an_application`) using the corresponding board name:

.. note::

   - By default, the nuclei evaluation soc is expecting a rv32imafdc bitstream,
   if you want to use rv64imafdc bitstream, you need to modify the KConfig configuration
   of ``nuclei_evalsoc``, just add ``select 64BIT`` in ``soc/nuclei/nuclei_evalsoc/Kconfig``

   - The default **CPU/Peripheral frequency** configured in ``dts/riscv/nuclei/evalsoc.dtsi``
   is ``50MHz``, you need to manually modify the ``clock-frequency`` node in the dts file
   to **match the real frequency** of the cpu bitstream running on the FPGA board.

   - You also need to update interrupt alignment **ARCH_IRQ_VECTOR_TABLE_ALIGN** in
   ``soc/nuclei/nuclei_evalsoc/Kconfig.defconfig``

   - The default ``riscv,isa`` in ``dts/riscv/nuclei/evalsoc.dtsi`` is ``rv32imafdc``, you need to
   modify it to ``rv64imafdc`` if you want to use ``rv64imafdc`` bitstream such as nx900/ux900 cpu

.. zephyr-app-commands::
   :zephyr-app: samples/hello_world
   :board: nuclei_fpga_eval
   :goals: build

Make sure you have followed the get started guide of Zephyr to setup development environment:

- Get started guide: https://docs.zephyrproject.org/latest/develop/getting_started/index.html
- Download Nuclei OpenOCD: https://nucleisys.com/download.php
- Checkout Nuclei Maintained Zephyr Repository with branch ``nuclei/4.1-branch``: https://github.com/riscv-mcu/zephyr

And then you can build the hello world sample application for the ``nuclei_fpga_eval`` board:

.. code-block:: console

   # cd to the zephyr project root directory
   cd /path/to/zephyr
   # check the current branch and status
   git branch && git status
   # just build in zephyr project root directory
   west build -b nuclei_fpga_eval samples/hello_world
   # or build in the sample/hello_world directory preferred
   cd samples/hello_world
   west build -b nuclei_fpga_eval
   # clean build with --pristine
   west build -b nuclei_fpga_eval --pristine
   # then you can find the output elf in build/zephyr/zephyr.elf
   # and you can debug it with riscv64-zephyr-elf-gdb and Nuclei OpenOCD

Flashing
========

.. note::

   ``west flash`` command is now supported for ``nuclei_fpga_eval``

You can use ``west flash`` command to program elf file to ram or flash memory.

eg.

.. code-block:: console

   # Make sure you are using Nuclei OpenOCD via set PATH of Nuclei OpenOCD
   where openocd # check the PATH of Nuclei OpenOCD on windows, for linux change it to which
   # Make sure you have setup zephyr development environment
   cd /path/to/zephyr
   cd samples/hello_world
   # build the hello world sample application, if you have built it before, you can skip this step
   # if a full rebuilt is needed, you can use --pristine option
   west build -b nuclei_fpga_eval
   # flash the hello world sample application to the board
   # you can see verbose output with -v option
   # if you want to flash to flash memory, you can change `set(OPENOCD_RAM_LOAD YES)`
   # to `set(OPENOCD_RAM_LOAD NO)` in `boards/nuclei/fpga_eval/board.cmake`
   west flash

Otherwise, you can use the following steps to debug the application with Nuclei OpenOCD and HummingBird Debugger:

.. code-block:: console

   # Make sure you are using Nuclei OpenOCD
   where openocd
   # Start openocd with the configuration file for the Nuclei FPGA Evaluation Board
   # Make sure the HummingBird Debugger is connected to the board
   # and the board is powered on and with correct bitstream loaded
   openocd -c "set INIT 1" -f boards/nuclei/fpga_eval/support/openocd.cfg
   # Make sure riscv64-zephyr-elf-gdb is in your PATH
   where riscv64-zephyr-elf-gdb
   # eg. C:/Users/xxxx/zephyr-sdk-0.17.0/riscv64-zephyr-elf/bin/riscv64-zephyr-elf-gdb.exe
   riscv64-zephyr-elf-gdb build/zephyr/zephyr.elf
   (gdb) target remote :3333
   # Reset and halt the board
   (gdb) monitor reset halt
   # load the program
   (gdb) load
   # Continue to run the program
   (gdb) c

Debugging
=========

.. note::

   ``west debug`` command is now supported for ``nuclei_fpga_eval``

You can use ``west debug --no-load`` command to load elf file to ram or flash memory and debug it.

eg.

.. code-block:: console

   # Make sure you are using Nuclei OpenOCD via set PATH of Nuclei OpenOCD
   where openocd # check the PATH of Nuclei OpenOCD on windows, for linux change it to which
   # Make sure you have setup zephyr development environment
   cd /path/to/zephyr
   cd samples/hello_world
   # build the hello world sample application, if you have built it before, you can skip this step
   # if a full rebuilt is needed, you can use --pristine option
   west build -b nuclei_fpga_eval
   # debug the hello world sample application to the board
   # you can see verbose output with -v option
   # recommended: --no-load means not load elf file to ram or flash memory
   # since you may need to reset the cpu, and then load the image to ram or flash memory
   west debug --no-load
   # if you want to load image, you need to do as follows in gdb:
   # 1. reset the cpu
   monitor reset halt
   # 2. load the image to ram or flash memory
   load
   # 3. set breakpoint at main, and continue to run the program
   b main
   # 4. step instruction, to check whether the pc is stepping as wished, if not, you
   # need to load the image to ram or flash memory again
   si
   # 5. if you step instruction works, you can continue to run the program
   c
   # 6. then program will run to main function, and you can set breakpoint at any function


If you want to do it just using openocd and gdb, you can debug zephyr application like below.

> Make sure the following two terminal all setup zephyr development environment.

1. Open a terminal and start OpenOCD with the configuration file for the Nuclei FPGA Evaluation Board:

   .. code-block:: console

      # cd to the zephyr project root directory
      cd /path/to/zephyr
      # Make sure you are using Nuclei OpenOCD
      where openocd
      # Start openocd with the configuration file for the Nuclei FPGA Evaluation Board
      # Make sure the HummingBird Debugger is connected to the board
      # and the board is powered onand with correct bitstream loaded
      openocd -c "set INIT 1" -f boards/nuclei/fpga_eval/support/openocd.cfg

2. Open another terminal and start GDB:

   .. code-block:: console

      # cd to zephyr project root directory
      cd /path/to/zephyr
      # cd to application which you want to debug
      cd samples/hello_world
      # If you have built the application before, you can skip this step
      west build -b nuclei_fpga_eval
      # Make sure riscv64-zephyr-elf-gdb is in your PATH
      where riscv64-zephyr-elf-gdb
      # eg. C:/Users/xxxx/zephyr-sdk-0.17.0/riscv64-zephyr-elf/bin/riscv64-zephyr-elf-gdb.exe
      riscv64-zephyr-elf-gdb build/zephyr/zephyr.elf
      (gdb) target remote :3333
      # Reset and halt the board
      (gdb) monitor reset halt
      # load the program
      (gdb) load
      # set breakpoint at main, and continue to run the program
      (gdb) b main
      (gdb) c


FAQ
===

UART0 interrupt id may change due to different bitstream
---------------------------------------------------------

If you run ``samples/subsys/shell/shell_module/``, and there is no output in console,
please check whether the correct **UART0** interrupt id is ``51`` or ``19``.

On some bitstream, the **UART0** interrupt id may be set to ``19`` instead of ``51``,
please modify the ``uart0->interrupts`` in the dts file ``dts/riscv/nuclei/evalsoc.dtsi``
to ``19`` if you encounter this issue.

Example change: ``interrupts = <51 0>;`` -> ``interrupts = <19 0>;``
