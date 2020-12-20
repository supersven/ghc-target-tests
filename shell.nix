import /home/sven/src/ghc-mips-llvm/ghc.nix/default.nix {
    version = "9.1";
    withDocs = false;
    withHadrianDeps = true;
    crossTargetArch = "mips64el-unknown-linux-gnuabi64";
    nixCrossTools = "svenmips";
    withNuma = false;
    withLlvm = true;
    useClang = false;
    withDwarf = false;
    withCustomLlvm = "/home/sven/src/llvm-project/build";
    nixpkgs = import /home/sven/src/nixpkgs { };
}
