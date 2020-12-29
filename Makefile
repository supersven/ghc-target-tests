# -optc-mabicalls -fPIE
Main:
	~/src/ghc-mips-llvm/inplace/bin/ghc-stage1 -v3 -fPIC -debug -static -keep-s-files -keep-llvm-files -g Main.hs
	mips64el-unknown-linux-gnuabi64-objdump -d Main > Main.exe.s

Fibonacci:
	$(GHC_MIPS) -v3 -fPIC -debug -static -keep-s-files -keep-llvm-files -c -O0 Fibonacci.hs
	$(GHC_MIPS) -v3 -fPIC -debug -static -keep-s-files -keep-llvm-files --make -no-hs-main -optc-O0 fibonacci.c Fibonacci -o fibonacci.mips.exe

Simple:
	$(GHC_MIPS) $(GHC_FLAGS) -c Simple.hs
	$(GHC_MIPS) $(GHC_FLAGS) --make simple.c Simple -o simple.mips.exe
	mips64el-unknown-linux-gnuabi64-objdump -d simple.mips.exe > simple.mips.exe.s

Timer:
	mips64el-unknown-linux-gnuabi64-gcc -lrt debug/Timer.c -o debug/Timer.mips.exe

StgCRun:
	mips64el-unknown-linux-gnuabi64-gcc -lrt debug/StgCRun.c -o debug/StgCRun.mips.exe

stg-1:
	$(GHC_MIPS) $(GHC_FLAGS) --make stg/cmm-1.cmm stg/main-1.c -o stg/stg-1.mips.exe

stg-2:
	$(GHC_MIPS) $(GHC_FLAGS) --make stg/main-2.c -o stg/stg-2.mips.exe

stg-3:
	$(GHC_MIPS) $(GHC_FLAGS) --make stg/Haskell-3.hs stg/main-3.c  -optl="-Wl,-u,Foo_plusOne_closure" -o stg/stg-3.mips.exe

stg-4:
	$(GHC_MIPS) $(GHC_FLAGS) --make stg/Haskell-4.hs stg/main-4.c  -optl="-Wl,-u,Foo_aritySeven_closure" -o stg/stg-4.mips.exe

stg-5:
	$(GHC_MIPS) $(GHC_FLAGS) --make stg/main-5.c -optl="-Wl,-u,base_GHCziTopHandler_flushStdHandles_closure" -o stg/stg-5.mips.exe

stg-6:
	$(GHC_MIPS) $(GHC_FLAGS) --make stg/main-6.c stg/Haskell-6.hs -optl="-Wl,-u,Foo_printHello_closure" -o stg/stg-6.mips.exe

stg-7:
	$(GHC_MIPS) $(GHC_FLAGS) --make stg/main-7.c stg/Haskell-7.hs -optl="-Wl,-u,Foo_printHello_closure" -o stg/stg-7.mips.exe

GHC_X64:=ghc
GHC_MIPS:=~/src/ghc-mips-llvm/inplace/bin/ghc-stage1
GHC_FLAGS:=-v3 -fllvm -fPIC -cpp -dcmm-lint -keep-s-files -ddump-cmm -ddump-to-file -optl-v -optlc-mips-tail-calls -keep-llvm-files -keep-tmp-files -O0 -debug -optc-g -opta-g -static -optc-mxgot -no-hs-main

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
	rm -f *.dump-cmm
	rm -f stg/*.s
	rm -f stg/*.ll
	rm -f stg/*.o
	rm -f stg/*.exe
	rm -f stg/*.dump-cmm

show-defaults:
	mips64el-linux-gnuabi64-gcc -Q --help=target
