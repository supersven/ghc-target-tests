
`-static -gdb`:
```
(gdb) c
Continuing.

Program received signal SIGILL, Illegal instruction.
0x0000000120de9558 in stg_ap_v64_info$def ()
(gdb) disassemble
Dump of assembler code for function stg_ap_v64_info$def:
   0x0000000120de9550 <+0>:     addi    a7,a1,-6376
   0x0000000120de9554 <+4>:     movf    zero,zero,$fcc0
=> 0x0000000120de9558 <+8>:     0x3fc8
   0x0000000120de955c <+12>:    nop
   0x0000000120de9560 <+16>:    ddiv    zero,zero,zero
   0x0000000120de9564 <+20>:    nop
End of assembler dump.
```

`mips64el-linux-gnuabi64-objdump -D Main > Main.s`
```
0000000120de9550 <stg_ap_v64_info>:
   120de9550:	20abe718 	addi	a7,a1,-6376
   120de9554:	00000001 	movf	zero,zero,$fcc0
   120de9558:	00003fc8 	0x3fc8
   120de955c:	00000000 	nop
   120de9560:	0000001e 	ddiv	zero,zero,zero
	...
```
