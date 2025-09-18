.. zephyr:board:: nuclei_fpga_eval

Overview
********

.. note::

   - Nuclei RISC-V CPU must support IREGION feature to run Zephyr.

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

Here we are just using Zephyr official development environment, so you must follow the official steps
to setup your development environment, and we only provide a zephyr repo contains our porting code,
so you need to switch to our maintained zephyr repo and branch after environment setup.

- **MUST** Following get started guide here to setup Zephyr development environment: https://docs.zephyrproject.org/4.1.0/develop/getting_started/index.html
- **MUST** Make sure you are using Zephyr SDK == 0.17.0, upper than 0.17.0 is not compatible with Zephyr 4.1
- **MUST** Download Nuclei OpenOCD: https://nucleisys.com/download.php
- **MUST** Checkout Nuclei Maintained Zephyr Repository with branch ``nuclei/4.1-branch`` and do ``west update``: https://github.com/riscv-mcu/zephyr

And then you can build the hello world sample application for the ``nuclei_fpga_eval`` board:

.. code-block:: console

   # MUST: setup zephyr development environment as described above
   # zephyr sdk == 0.17.0 is required
   # assume you have set it up correctly
   # cd to the zephyr project root directory
   cd /path/to/zephyr
   # make sure you are using the branch nuclei/4.1-branch from https://github.com/riscv-mcu/zephyr
   # you can add a new remote such as below
   # if you have already switched to nuclei/4.1-branch, ignore this step
   git remote add nuclei https://github.com/riscv-mcu/zephyr.git
   git fetch nuclei
   git checkout nuclei/4.1-branch
   # execute west update to sync repos to match the branch required
   # see https://docs.zephyrproject.org/4.1.0/develop/west/basics.html#west-update-basics
   # Whenever you check out a different revision in your manifest repository,
   # you should run west update to make sure your workspace contains the project repositories
   # the new revision expects.
   # MUST: execute west update
   west update
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


FAQ
===

1. Compile sample met following error ``zephyr/lib/libc/picolibc/locks.c:11:16: error: conflicting types for '__lock___libc_recursive_mutex'; have 'struct k_mutex'``

See https://github.com/zephyrproject-rtos/zephyr/issues/92505 and https://docs.google.com/spreadsheets/d/1wzGJLRuR6urTgnDFUqKk7pEB8O6vWu6Sxziw_KROxMA/edit?gid=0#gid=0

Zephyr **v4.1.0** is compatible with Zephyr SDK **0.17.0**, Partially compatible with later versions, please download Zephyr SDK 0.17.0

2. Show me a sample build command and command log

.. code-block:: console

   (.venv) PS C:\Work\Code\zephyrproject> dir

      Directory: C:\Work\Code\zephyrproject

   Mode                 LastWriteTime         Length Name
   ----                 -------------         ------ ----
   d----           2024/12/4    10:36                .venv
   d----          2024/12/12    16:33                .vscode
   d----           2024/12/4    10:45                .west
   d----           2024/12/4    11:01                bootloader
   d----           2024/12/4    11:03                modules
   d----           2024/12/4    11:01                tools
   d----           2025/9/18    14:41                zephyr
   (.venv) PS C:\Work\Code\zephyrproject> cd zephyr
   (.venv) PS C:\Work\Code\zephyrproject\zephyr> python --version
   Python 3.11.4
   (.venv) PS C:\Work\Code\zephyrproject\zephyr> pip list
   Package             Version
   ------------------- ------------
   anytree             2.12.1
   appdirs             1.4.4
   arrow               1.2.3
   astroid             3.3.5
   canopen             2.3.0
   capstone            4.0.2
   cbor                1.0.0
   cbor2               5.6.5
   certifi             2024.8.30
   cffi                1.17.1
   charset-normalizer  3.4.0
   clang-format        19.1.4
   click               8.1.3
   cmsis-pack-manager  0.5.3
   colorama            0.4.6
   colorlog            6.9.0
   coverage            7.6.8
   cryptography        44.0.0
   Deprecated          1.2.15
   dill                0.3.9
   docopt              0.6.2
   gcovr               8.2
   gitdb               4.0.11
   gitlint             0.19.1
   gitlint-core        0.19.1
   GitPython           3.1.43
   graphviz            0.20.3
   grpcio              1.68.1
   grpcio-tools        1.68.1
   hidapi              0.14.0.post4
   idna                3.10
   imgtool             2.1.0
   importlib_metadata  8.5.0
   importlib_resources 6.4.5
   iniconfig           2.0.0
   intelhex            2.3.0
   intervaltree        3.1.0
   isort               5.13.2
   Jinja2              3.1.4
   junit2html          31.0.2
   junitparser         3.2.0
   lark                1.2.2
   libusb-package      1.0.26.2
   lpc-checksum        3.0.0
   lxml                5.3.0
   MarkupSafe          3.0.2
   mccabe              0.7.0
   mock                5.1.0
   mypy                1.13.0
   mypy-extensions     1.0.0
   natsort             8.4.0
   numpy               2.2.6
   packaging           24.2
   pandas              2.2.3
   pathspec            0.12.1
   patool              3.1.0
   pillow              11.0.0
   pip                 24.3.1
   platformdirs        4.3.6
   pluggy              1.5.0
   ply                 3.11
   polib               1.2.0
   prettytable         3.12.0
   progress            1.6
   protobuf            5.29.0
   psutil              6.1.0
   pycparser           2.22
   pyelftools          0.31
   PyGithub            2.5.0
   Pygments            2.18.0
   PyJWT               2.10.1
   pykwalify           1.8.0
   pylink-square       1.3.0
   pylint              3.3.2
   PyNaCl              1.5.0
   pyocd               0.36.0
   pyserial            3.5
   pytest              8.3.4
   python-can          4.5.0
   python-dateutil     2.9.0.post0
   python-magic        0.4.27
   python-magic-bin    0.4.14
   pytz                2025.2
   pyusb               1.2.1
   PyYAML              6.0.2
   regex               2024.11.6
   requests            2.32.3
   ruamel.yaml         0.18.6
   ruamel.yaml.clib    0.2.12
   ruff                0.8.1
   semver              3.0.2
   setuptools          65.5.0
   six                 1.16.0
   smmap               5.0.1
   sortedcontainers    2.4.0
   sphinx-lint         1.0.0
   tabulate            0.9.0
   tomlkit             0.13.2
   tqdm                4.67.1
   typing_extensions   4.12.2
   tzdata              2025.2
   unidiff             0.7.5
   urllib3             2.2.3
   wcwidth             0.2.13
   west                1.3.0
   windows-curses      2.4.0
   wrapt               1.17.0
   yamllint            1.35.1
   zcbor               0.9.1
   zipp                3.21.0
   (.venv) PS C:\Work\Code\zephyrproject> west --version
   West version: v1.3.0
   (.venv) PS C:\Work\Code\zephyrproject\zephyr> west sdk list
   0.17.0:
   path: C:\Users\hqfang\zephyr-sdk-0.17.0
   installed-toolchains:
      - aarch64-zephyr-elf
      - arc-zephyr-elf
      - arc64-zephyr-elf
      - arm-zephyr-eabi
      - microblazeel-zephyr-elf
      - mips-zephyr-elf
      - nios2-zephyr-elf
      - riscv64-zephyr-elf
      - sparc-zephyr-elf
      - x86_64-zephyr-elf
      - xtensa-amd_acp_6_0_adsp_zephyr-elf
      - xtensa-dc233c_zephyr-elf
      - xtensa-espressif_esp32s2_zephyr-elf
      - xtensa-espressif_esp32s3_zephyr-elf
      - xtensa-espressif_esp32_zephyr-elf
      - xtensa-intel_ace15_mtpm_zephyr-elf
      - xtensa-intel_ace30_ptl_zephyr-elf
      - xtensa-intel_tgl_adsp_zephyr-elf
      - xtensa-mtk_mt8195_adsp_zephyr-elf
      - xtensa-nxp_imx8m_adsp_zephyr-elf
      - xtensa-nxp_imx8ulp_adsp_zephyr-elf
      - xtensa-nxp_imx_adsp_zephyr-elf
      - xtensa-nxp_rt500_adsp_zephyr-elf
      - xtensa-nxp_rt600_adsp_zephyr-elf
      - xtensa-nxp_rt700_hifi1_zephyr-elf
      - xtensa-nxp_rt700_hifi4_zephyr-elf
      - xtensa-sample_controller32_zephyr-elf
      - xtensa-sample_controller_zephyr-elf
   available-toolchains:
   (.venv) PS C:\Work\Code\zephyrproject\zephyr> west list
   manifest     zephyr                       HEAD                                     N/A
   acpica       modules/lib/acpica           8d24867bc9c9d81c81eeac59391cda59333affd4 https://github.com/zephyrproject-rtos/acpica
   cmsis        modules/hal/cmsis            d1b8b20b6278615b00e136374540eb1c00dcabe7 https://github.com/zephyrproject-rtos/cmsis
   cmsis-dsp    modules/lib/cmsis-dsp        d80a49b2bb186317dc1db4ac88da49c0ab77e6e7 https://github.com/zephyrproject-rtos/cmsis-dsp
   cmsis-nn     modules/lib/cmsis-nn         e9328d612ea3ea7d0d210d3ac16ea8667c01abdd https://github.com/zephyrproject-rtos/cmsis-nn
   cmsis_6      modules/lib/cmsis_6          783317a3072554acbac86cca2ff24928cbf98d30 https://github.com/zephyrproject-rtos/CMSIS_6
   edtt         tools/edtt                   b9ca3c7030518f07b7937dacf970d37a47865a76 https://github.com/zephyrproject-rtos/edtt
   fatfs        modules/fs/fatfs             16245c7c41d2b79e74984f49b5202551786b8a9b https://github.com/zephyrproject-rtos/fatfs
   hal_adi      modules/hal/adi              633fcecf3717aaa22079cf6121627a879f24df51 https://github.com/zephyrproject-rtos/hal_adi
   hal_altera   modules/hal/altera           4fe4df959d4593ce66e676aeba0b57f546dba0fe https://github.com/zephyrproject-rtos/hal_altera
   hal_ambiq    modules/hal/ambiq            87a188b91aca22ce3ce7deb4a1cbf7780d784673 https://github.com/zephyrproject-rtos/hal_ambiq
   hal_atmel    modules/hal/atmel            da767444cce3c1d9ccd6b8a35fd7c67dc82d489c https://github.com/zephyrproject-rtos/hal_atmel
   hal_espressif modules/hal/espressif        202c59552dc98e5cd02386313e1977ecb17a131f https://github.com/zephyrproject-rtos/hal_espressif
   hal_ethos_u  modules/hal/ethos_u          50ddffca1cc700112f25ad9bc077915a0355ee5d https://github.com/zephyrproject-rtos/hal_ethos_u
   hal_gigadevice modules/hal/gigadevice       2994b7dde8b0b0fa9b9c0ccb13474b6a486cddc3 https://github.com/zephyrproject-rtos/hal_gigadevice
   hal_infineon modules/hal/infineon         468e955eb49b8a731474ff194ca17b6e6a08c2d9 https://github.com/zephyrproject-rtos/hal_infineon
   hal_intel    modules/hal/intel            0355bb816263c54eed23c7781034447af5d8200c https://github.com/zephyrproject-rtos/hal_intel
   hal_microchip modules/hal/microchip        fa2431a906ffb560160d40739d7cf04169551103 https://github.com/zephyrproject-rtos/hal_microchip
   hal_nordic   modules/hal/nordic           37ca068d7b013fb65a2acc9306bffa48a3e72839 https://github.com/zephyrproject-rtos/hal_nordic
   hal_nuvoton  modules/hal/nuvoton          466c3eed9c98453fb23953bf0e0427fea01924be https://github.com/zephyrproject-rtos/hal_nuvoton
   hal_nxp      modules/hal/nxp              9dc7449014a7380355612453b31be479cb3a6833 https://github.com/zephyrproject-rtos/hal_nxp
   hal_openisa  modules/hal/openisa          eabd530a64d71de91d907bad257cd61aacf607bc https://github.com/zephyrproject-rtos/hal_openisa
   hal_quicklogic modules/hal/quicklogic       bad894440fe72c814864798c8e3a76d13edffb6c https://github.com/zephyrproject-rtos/hal_quicklogic
   hal_renesas  modules/hal/renesas          3204903bdc5eda6869a40363560a69369c8d0e22 https://github.com/zephyrproject-rtos/hal_renesas
   hal_rpi_pico modules/hal/rpi_pico         7b57b24588797e6e7bf18b6bda168e6b96374264 https://github.com/zephyrproject-rtos/hal_rpi_pico
   hal_silabs   modules/hal/silabs           8a173e9e566a396a19d18da4661cb54ce098f268 https://github.com/zephyrproject-rtos/hal_silabs
   hal_st       modules/hal/st               05fd4533730a9aea845261c5d24ed9832a6f0b6e https://github.com/zephyrproject-rtos/hal_st
   hal_stm32    modules/hal/stm32            55043bcc35fffa3b4a8c75a696d932b5020aad09 https://github.com/zephyrproject-rtos/hal_stm32
   hal_tdk      modules/hal/tdk              6727477af1e46fa43878102489b9672a9d24e39f https://github.com/zephyrproject-rtos/hal_tdk
   hal_telink   modules/hal/telink           4226c7fc17d5a34e557d026d428fc766191a0800 https://github.com/zephyrproject-rtos/hal_telink
   hal_ti       modules/hal/ti               258652a3ac5d7df68ba8df20e4705c3bd98ede38 https://github.com/zephyrproject-rtos/hal_ti
   hal_wch      modules/hal/wch              1de9d3e406726702ce7cfc504509a02ecc463554 https://github.com/zephyrproject-rtos/hal_wch
   hal_wurthelektronik modules/hal/wurthelektronik  e3e2797b224fc48fdef1bc3e5a12a7c73108bba2 https://github.com/zephyrproject-rtos/hal_wurthelektronik
   hal_xtensa   modules/hal/xtensa           baa56aa3e119b5aae43d16f9b2d2c8112e052871 https://github.com/zephyrproject-rtos/hal_xtensa
   hostap       modules/lib/hostap           697fd2cf5cbbd0c5375fc34761b6a9d7489a67d2 https://github.com/zephyrproject-rtos/hostap
   liblc3       modules/lib/liblc3           48bbd3eacd36e99a57317a0a4867002e0b09e183 https://github.com/zephyrproject-rtos/liblc3
   libmctp      modules/lib/libmctp          b97860e78998551af99931ece149eeffc538bdb1 https://github.com/zephyrproject-rtos/libmctp
   libmetal     modules/hal/libmetal         3e8781aae9d7285203118c05bc01d4eb0ca565a7 https://github.com/zephyrproject-rtos/libmetal
   littlefs     modules/fs/littlefs          ed0531d59ee37f5fb2762bcf2fc8ba4efaf82656 https://github.com/zephyrproject-rtos/littlefs
   loramac-node modules/lib/loramac-node     fb00b383072518c918e2258b0916c996f2d4eebe https://github.com/zephyrproject-rtos/loramac-node
   lvgl         modules/lib/gui/lvgl         1ed1ddd881c3784049a92bb9fe37c38c6c74d998 https://github.com/zephyrproject-rtos/lvgl
   mbedtls      modules/crypto/mbedtls       4952e1328529ee549d412b498ea71c54f30aa3b1 https://github.com/zephyrproject-rtos/mbedtls
   mcuboot      bootloader/mcuboot           346f7374ff4467e40b5594658f8ac67a5e9813c9 https://github.com/zephyrproject-rtos/mcuboot
   mipi-sys-t   modules/debug/mipi-sys-t     33e5c23cbedda5ba12dbe50c4baefb362a791001 https://github.com/zephyrproject-rtos/mipi-sys-t
   net-tools    tools/net-tools              93acc8bac4661e74e695eb1aea94c7c5262db2e2 https://github.com/zephyrproject-rtos/net-tools
   nrf_hw_models modules/bsim_hw_models/nrf_hw_models 73a5d5827a94820be65b7d276d28173ec10bab9f https://github.com/zephyrproject-rtos/nrf_hw_models
   nrf_wifi     modules/lib/nrf_wifi         e35f707a782b7c4c0eb83a3b06ca4e6eb693f29f https://github.com/zephyrproject-rtos/nrf_wifi
   open-amp     modules/lib/open-amp         52bb1783521c62c019451cee9b05b8eda9d7425f https://github.com/zephyrproject-rtos/open-amp
   openthread   modules/lib/openthread       3ae741f95e7dfb391dec35c48742862049eb62e8 https://github.com/zephyrproject-rtos/openthread
   percepio     modules/debug/percepio       49e6dc202aa38c2a3edbafcc2dab85dec6aee973 https://github.com/zephyrproject-rtos/percepio
   picolibc     modules/lib/picolibc         82d62ed1ac55b4e34a12d0390aced2dc9af13fc9 https://github.com/zephyrproject-rtos/picolibc
   segger       modules/debug/segger         cf56b1d9c80f81a26e2ac5727c9cf177116a4692 https://github.com/zephyrproject-rtos/segger
   tinycrypt    modules/crypto/tinycrypt     1012a3ebee18c15ede5efc8332ee2fc37817670f https://github.com/zephyrproject-rtos/tinycrypt
   trusted-firmware-a modules/tee/tf-a/trusted-firmware-a 713ffbf96c5bcbdeab757423f10f73eb304eff07 https://github.com/zephyrproject-rtos/trusted-firmware-a
   trusted-firmware-m modules/tee/tf-m/trusted-firmware-m 918f32d9fce5e0ee59fc33844b5317b7626ce37a https://github.com/zephyrproject-rtos/trusted-firmware-m
   uoscore-uedhoc modules/lib/uoscore-uedhoc   54abc109c9c0adfd53c70077744c14e454f04f4a https://github.com/zephyrproject-rtos/uoscore-uedhoc
   zcbor        modules/lib/zcbor            9b07780aca6fb21f82a241ba386ad9b379809337 https://github.com/zephyrproject-rtos/zcbor
   (.venv) PS C:\Work\Code\zephyrproject\zephyr> west build -b nuclei_fpga_eval samples/hello_world
   -- west build: generating a build system
   Loading Zephyr default modules (Zephyr base).
   -- Application: C:/Work/Code/zephyrproject/zephyr/samples/hello_world
   -- CMake version: 3.31.6
   -- Found Python3: C:/Work/Code/zephyrproject/.venv/Scripts/python.exe (found suitable version "3.11.4", minimum required is "3.10") found components: Interpreter
   -- Cache files will be written to: C:/Work/Code/zephyrproject/zephyr/.cache
   -- Zephyr version: 4.1.0 (C:/Work/Code/zephyrproject/zephyr)
   -- Found west (found suitable version "1.3.0", minimum required is "0.14.0")
   -- Board: nuclei_fpga_eval, qualifiers: nuclei_evalsoc
   -- ZEPHYR_TOOLCHAIN_VARIANT not set, trying to locate Zephyr SDK
   -- Found host-tools: zephyr 0.17.0 (C:/Users/hqfang/zephyr-sdk-0.17.0)
   -- Found toolchain: zephyr 0.17.0 (C:/Users/hqfang/zephyr-sdk-0.17.0)
   -- Could NOT find Dtc (missing: DTC) (Required is at least version "1.4.6")
   Hint: The project() command has not yet been called.  It sets up system-specific search paths.
   -- Found BOARD.dts: C:/Work/Code/zephyrproject/zephyr/boards/nuclei/fpga_eval/nuclei_fpga_eval.dts
   -- Generated zephyr.dts: C:/Work/Code/zephyrproject/zephyr/build/zephyr/zephyr.dts
   -- Generated pickled edt: C:/Work/Code/zephyrproject/zephyr/build/zephyr/edt.pickle
   -- Generated devicetree_generated.h: C:/Work/Code/zephyrproject/zephyr/build/zephyr/include/generated/zephyr/devicetree_generated.h
   -- Including generated dts.cmake file: C:/Work/Code/zephyrproject/zephyr/build/zephyr/dts.cmake
   Parsing C:/Work/Code/zephyrproject/zephyr/Kconfig
   Loaded configuration 'C:/Work/Code/zephyrproject/zephyr/boards/nuclei/fpga_eval/nuclei_fpga_eval_defconfig'
   Merged configuration 'C:/Work/Code/zephyrproject/zephyr/samples/hello_world/prj.conf'
   Configuration saved to 'C:/Work/Code/zephyrproject/zephyr/build/zephyr/.config'
   Kconfig header saved to 'C:/Work/Code/zephyrproject/zephyr/build/zephyr/include/generated/zephyr/autoconf.h'
   -- Found GnuLd: c:/users/hqfang/zephyr-sdk-0.17.0/riscv64-zephyr-elf/riscv64-zephyr-elf/bin/ld.bfd.exe (found version "2.38")
   -- The C compiler identification is GNU 12.2.0
   -- The CXX compiler identification is GNU 12.2.0
   -- The ASM compiler identification is GNU
   -- Found assembler: C:/Users/hqfang/zephyr-sdk-0.17.0/riscv64-zephyr-elf/bin/riscv64-zephyr-elf-gcc.exe
   -- Configuring done (24.5s)
   -- Generating done (1.0s)
   -- Build files have been written to: C:/Work/Code/zephyrproject/zephyr/build
   -- west build: building application
   [1/109] Generating include/generated/zephyr/version.h
   -- Zephyr version: 4.1.0 (C:/Work/Code/zephyrproject/zephyr), build: v4.1.0-38-g2d67cb01ad31
   [109/109] Linking C executable zephyr\zephyr.elf
   Memory region         Used Size  Region Size  %age Used
               ROM:       20672 B       128 KB     15.77%
               RAM:        4204 B       128 KB      3.21%
         IDT_LIST:          0 GB         2 KB      0.00%
   Generating files from C:/Work/Code/zephyrproject/zephyr/build/zephyr/zephyr.elf for board: nuclei_fpga_eval
