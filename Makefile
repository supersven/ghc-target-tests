# -optc-mabicalls -fPIE
Main:
	~/src/ghc-mips-llvm/inplace/bin/ghc-stage1 -v3 -fPIC -debug -static -keep-s-files -keep-llvm-files -g Main.hs
	mips64el-unknown-linux-gnuabi64-objdump -d Main > Main.exe.s

Fibonacci:
	$(GHC_MIPS) -v3 -fPIC -debug -static -keep-s-files -keep-llvm-files -c -O0 Fibonacci.hs
	$(GHC_MIPS) -v3 -fPIC -debug -static -keep-s-files -keep-llvm-files --make -no-hs-main -optc-O0 fibonacci.c Fibonacci -o fibonacci.mips.exe

Simple:
	$(GHC_MIPS) $(GHC_FLAGS) -static -optc-mxgot -c Simple.hs
	$(GHC_MIPS) $(GHC_FLAGS) -static -optc-mxgot -optlc-mxgot --make simple.c Simple -o simple.mips.exe
	mips64el-unknown-linux-gnuabi64-objdump -d simple.mips.exe > simple.mips.exe.s

Timer:
	mips64el-unknown-linux-gnuabi64-gcc -lrt debug/Timer.c -o debug/Timer.mips.exe

StgCRun:
	mips64el-unknown-linux-gnuabi64-gcc -lrt debug/StgCRun.c -o debug/StgCRun.mips.exe

GHC_X64:=ghc
GHC_MIPS:=~/src/ghc-mips-llvm/inplace/bin/ghc-stage1
GHC_FLAGS:=-v3 -fllvm -fPIC -cpp -dcmm-lint -keep-s-files -optl-v -keep-llvm-files -keep-tmp-files -O0 -debug -optc-g -opta-g -no-hs-main

MIPS_EXES:=$(patsubst %.cmm, %.mips.exe, $(wildcard *.cmm))
X64_EXES:=$(patsubst %.cmm, %.x64.exe, $(wildcard *.cmm))

all-cmm-mips: $(MIPS_EXES)

all-cmm-x64: $(X64_EXES)

%.mips.exe: %.cmm
	$(GHC_MIPS) $(GHC_FLAGS) -o $@ $<

%.x64.exe: %.cmm
	$(GHC_X64) $(GHC_FLAGS) -o $@ $<

clean:
	rm -f *.s
	rm -f *.ll
	rm -f *.o
	rm -f Main
	rm -f *.core
	rm -f *.exe
	rm -f *.hi
	rm -f debug/*.exe

show-defaults:
	mips64el-linux-gnuabi64-gcc -Q --help=target
