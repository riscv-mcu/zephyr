.. zephyr:board:: nuclei_fpga_eval

Overview
********

.. note::

   Nuclei RISC-V CPU must support IREGION feature to run Zephyr.

The Nuclei FPGA Evaluation Board is common name for FPGA development boards such as
DDR200T/MCU200T/KU060/VCU118/VU19P etc.

You can flash nuclei evaluation soc bitstream into these boards with Nuclei
RISC-V CPU such as 200/300/600/900/1000 series.

Currently we support Zephyr SMP and Non-SMP version, and Nuclei Qemu not yet able to run Zephyr on it, still working on it.

Default baudrate for Zephyr on Nuclei FPGA Evaluation Board is **115200**.

Now program is default built for sram memory region since we need to consider both SMP(2 Core by default) and Non-SMP configurations.

You can evaluate Zephyr on Nuclei FPGA Evaluation Board using Nuclei Prebuilt CPU bitsteam such as u900 or ux900 bitstream.

- ECLIC is required for Zephyr to run on Nuclei FPGA Evaluation Board, so you need to use bitstream with ECLIC support.
- For SMP support, you need to use bitstream with smp 2 core support.

Programming and debugging
*************************

.. note::

   - By default, the default cpu isa supported is ``rv32imafdc``, default cpu frequency is 50MHz,
     if you want to run on a different cpu frequency, you need to change ``DT_FREQ_M(50)`` in
     ``dts/riscv/nuclei/evalsoc.dtsi`` to other value
   - If you want to use ``rv64imafdc``, you need to modify ``soc/nuclei/nuclei_evalsoc/Kconfig``, uncomment the line ``select 64BIT``,
     and change ``rv32imafdc`` to ``rv64imafdc`` in ``dts/riscv/nuclei/evalsoc.dtsi``.


You need to download Nuclei OpenOCD from https://nucleisys.com/download.php,
and extract it and add it to system **PATH**.

And you also need to have a HummingBird Debugger to connect to ``nuclei_fpga_eval``
board and debug it.

- HummingBird Debugger: https://nucleisys.com/developboard.php#debuggerkit

SMP Support
===========

This porting code supports both SMP and Non-SMP configurations for the Nuclei FPGA Evaluation Board.

You can use different bitstreams to run Zephyr on Nuclei FPGA Evaluation Board to evaluate SMP and Non-SMP configurations.

You need to customize the ``soc/nuclei/nuclei_evalsoc/Kconfig.defconfig`` and ``dts/riscv/nuclei/evalsoc.dtsi``
to enable SMP support.

- ``MP_MAX_NUM_CPUS`` in ``soc/nuclei/nuclei_evalsoc/Kconfig.defconfig``: You need to set this to the number of cores you want to support, eg. 2 for dual-core.
- ``systimer`` and ``clint`` nodes in ``dts/riscv/nuclei/evalsoc.dtsi``: You need to change register base address to match the real address of the registers.

You can try SMP support using ``samples/arch/smp/pi`` sample application.

.. note::

   # Sample output for SMP 2 Cores
   *** Booting Zephyr OS build v4.1.0-35-g271814f03046 ***
   Calculate first 240 digits of Pi independently by 16 threads.
   Pi value calculated by thread #0: 314159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223176
   Pi value calculated by thread #1: 314159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223176
   Pi value calculated by thread #2: 314159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223176
   Pi value calculated by thread #3: 314159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223176
   Pi value calculated by thread #4: 314159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223176
   Pi value calculated by thread #5: 314159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223176
   Pi value calculated by thread #6: 314159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223176
   Pi value calculated by thread #7: 314159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223176
   Pi value calculated by thread #8: 314159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223176
   Pi value calculated by thread #9: 314159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223176
   Pi value calculated by thread #10: 31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822316
   Pi value calculated by thread #11: 31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822316
   Pi value calculated by thread #12: 31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822316
   Pi value calculated by thread #13: 31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822316
   Pi value calculated by thread #14: 31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822316
   Pi value calculated by thread #15: 31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822316
   All 16 threads executed by 2 cores in 191 msec

If you want to try non-smp configuration, you can just go to ``samples\synchronization`` and just build and run it without any modification.

Building
========

Applications for the ``nuclei_fpga_eval`` board configuration can be built as
usual (see :ref:`build_an_application`) using the corresponding board name:

.. note::

   - Nuclei Qemu 2025.02 is not able to run Zephyr, please check the FAQ section.

   - By default, the nuclei evaluation soc is expecting a ``rv32imafdc`` bitstream,
   if you want to use ``rv64imafdc`` bitstream, you need to modify the KConfig configuration
   of ``nuclei_evalsoc``, just add ``select 64BIT`` in ``soc/nuclei/nuclei_evalsoc/Kconfig``

   - The default **CPU/Peripheral frequency** configured in ``dts/riscv/nuclei/evalsoc.dtsi``
   is ``50MHz``, you need to manually modify the ``clock-frequency`` node in the dts file
   to **match the real frequency** of the cpu bitstream running on the FPGA board.

   - You also need to update interrupt alignment **ARCH_IRQ_VECTOR_TABLE_ALIGN** in
   ``soc/nuclei/nuclei_evalsoc/Kconfig.defconfig`` according to your real CPU configuration.

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

   - ``west flash`` command is now supported for ``nuclei_fpga_eval`` for only single core version, **SMP is not supported**.
   - For **SMP** debugging, please refer to note below which contains ``SMP`` key word.


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
   # WARN: This command dont support SMP system
   west flash

Otherwise, you can use the following steps to debug the application with Nuclei OpenOCD and HummingBird Debugger:

.. code-block:: console

   # Make sure you are using Nuclei OpenOCD
   where openocd
   # Start openocd with the configuration file for the Nuclei FPGA Evaluation Board
   # Make sure the HummingBird Debugger is connected to the board
   # and the board is powered on and with correct bitstream loaded
   # If you are running for SMP system, eg SMP 2 Cores, you need to pass extra -c "set SMP 2"
   # eg. for SMP 2 Cores: openocd -c "set SMP 2" -c "set INIT 1" -f boards/nuclei/fpga_eval/support/openocd.cfg
   openocd -c "set INIT 1" -f boards/nuclei/fpga_eval/support/openocd.cfg
   # Make sure riscv64-zephyr-elf-gdb is in your PATH
   where riscv64-zephyr-elf-gdb
   # eg. C:/Users/xxxx/zephyr-sdk-0.17.0/riscv64-zephyr-elf/bin/riscv64-zephyr-elf-gdb.exe
   riscv64-zephyr-elf-gdb build/zephyr/zephyr.elf
   (gdb) target remote :3333
   # Reset and halt the board
   (gdb) monitor reset halt
   # If you are using SMP CPU, you need to set each CPU's reset pc to __nuclei_start via command below
   (gdb) thread apply all set $pc=__nuclei_start
   # load the program
   (gdb) load
   # Continue to run the program
   (gdb) c

Debugging
=========

.. note::

   - ``west debug`` command is now supported for ``nuclei_fpga_eval`` for only single core version, **SMP is not supported**.
   - For **SMP** debugging, please refer to note below which contains ``SMP`` key word.

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
   # WARN: This command dont support SMP system
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
      # If you are running for SMP system, eg SMP 2 Cores, you need to pass extra -c "set SMP 2"
      # eg. for SMP 2 Cores: openocd -c "set SMP 2" -c "set INIT 1" -f boards/nuclei/fpga_eval/support/openocd.cfg
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
      # If you are using SMP CPU, you need to set each CPU's reset pc to __nuclei_start via command below
      (gdb) thread apply all set $pc=__nuclei_start
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

Nuclei Qemu 2025.02 not able to run Zephyr
-------------------------------------------

If you are using Nuclei Qemu 2025.02, it is not able to run zephyr on Nuclei CPU in Qemu.

.. note::

   - You need to download Nuclei Qemu development version from https://drive.weixin.qq.com/s?k=ABcAKgdSAFcNoqkNsB
   - This qemu version also not support SMP, still working on it.

And the source code related to Nuclei Qemu is pushed to  https://github.com/riscv-mcu/qemu/tree/nuclei/9.0

Here are sample usage:

.. code-block:: console

   # cd to the zephyr project root directory
   cd /path/to/zephyr
   # Make sure you are using Nuclei Qemu
   # Make sure you are using the development version of Nuclei Qemu
   # QEMU emulator version 9.0.4 (v9.0.4-93-g34445bffa0-dirty)
   where qemu-system-riscv64
   # cd to application which you want to run, eg. samples/hello_world
   cd samples/hello_world
   west build -b nuclei_fpga_eval --pristine
   # If you want to run on n300fd
   qemu-system-riscv32 -M nuclei_evalsoc,download=sram -cpu nuclei-n300fd,ext= -smp 1 -icount shift=0 -nodefaults -nographic -serial stdio -kernel .\build\zephyr\zephyr.elf
   # If you want to run on nx900fd
   # CAUTION: you need to modify source code as described in Building section
   # Change cpu configuration from rv32 to rv64
   rm -rf build
   west build -b nuclei_fpga_eval
   qemu-system-riscv64 -M nuclei_evalsoc,download=sram -cpu nuclei-nx900fd,ext= -smp 1 -icount shift=0 -nodefaults -nographic -serial stdio -kernel .\build\zephyr\zephyr.elf

Source Code Review
------------------

Please check the TODO items in the porting code and modify it to fit for your real SoC.

The dts files should always be modified to match the real SoC you are using.

Our porting implementation is based on Zephyr v4.1 branch. You can review the changes
and implementation details by comparing the branches:

* **Base**: ``v4.1-branch``
* **Port**: ``nuclei/4.1-branch``
* **Comparison**: https://github.com/riscv-mcu/zephyr/compare/v4.1-branch...nuclei/4.1-branch
