/**
 * @file ld.script
 *
 * This is the linker script for the Xinu kernel on the RISCV64 qemu virt 
 * platform (emulated virt board features CLINT, PLIC, 16550A UART, VirtIO, 
 * device-tree, Priv ISA v1.10). 

 * QEMU loads the kernel from the xinu.elf file and starts execution in the
 * emulated ROM on address 0x1000, from there it will jump to the provided
 * _start entry point address (that we place at 0x80000000).
 * 
 * Every section is aligned on a 64-byte (cache block) boundary.
 */
/* Embedded Xinu, Copyright (C) 2018.  All rights reserved. */

ENTRY(_start)

SECTIONS {
      . = 0x80000000;
     

    . = ALIGN(64);

    .text : {
    _text = .;
        *(.text .text.*)
        *(.rodata .rodata.*)
        _etext = .;
    }

    . = ALIGN(64);
    _sdata = .;
    .data : {
        *(.data .data.*)

    }
    .sdata : {
       __global_pointer$ = . + 10k;
    }

    _edata = .;

    . = ALIGN(64);
   _sbss = .;
    _bss = . ;
    .bss : {
        *(.bss .bss.*)
    }
    _ebss = .;
    . = ALIGN(64);
    _end = .;

    /* Discard comment and note (but not debugging) sections.  Some
     * versions of GNU ld would otherwise automatically place the
     * ".note.gnu.build-id" section before _start!  */
    . = 0x8007d000;
    fs = ABSOLUTE(.);

    /* Aquí se reserva un espacio de 500 KB para el sistema de archivos */
    . += 512K;
    _fs_end = .;
}