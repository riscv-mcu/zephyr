.. zephyr:board:: nuclei_fpga_eval

Overview
********

The Nuclei FPGA Evaluation Board is common name for FPGA development boards such as
DDR200T/MCU200T/KU060/VCU118/VU19P etc.

You can flash nuclei evaluation soc bitstream into these boards with Nuclei
RISC-V CPU such as 200/300/600/900/1000 series.

Programming and debugging
*************************

Building
========

Applications for the ``nuclei_fpga_eval`` board configuration can be built as
usual (see :ref:`build_an_application`) using the corresponding board name:

.. note::

   By default, the nuclei evaluation soc is expecting a rv32imafdc bitstream,
   if you want to use rv64imafdc bitstream, you need to modify the KConfig configuration
   of ``nuclei_evalsoc``, just add ``select 64BIT`` in ``soc/nuclei/nuclei_evalsoc/Kconfig``


.. zephyr-app-commands::
   :zephyr-app: samples/hello_world
   :board: nuclei_fpga_eval
   :goals: build

Flashing
========

You need to download Nuclei OpenOCD from https://nucleisys.com/download.php,
and extract it and add it to system PATH.

And you also need to have a HummingBird Debugger to connect to ``nuclei_fpga_eval``
board and debug it.

- HummingBird Debugger: https://nucleisys.com/developboard.php#debuggerkit

.. code-block:: console

   # Make sure you are using Nuclei OpenOCD
   which openocd
   openocd -c 'bindto 0.0.0.0' \
           -f boards/nuclei/fpga_eval/support/openocd.cfg
   riscv64-zephyr-elf-gdb build/zephyr/zephyr.elf
   (gdb) target remote :3333
   (gdb) c

Debugging
=========

Refer to the detailed overview about :ref:`application_debugging`.
