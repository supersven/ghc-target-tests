{-# LANGUAGE ForeignFunctionInterface #-}

module Simple where

import Foreign.C.Types

fortyTwo :: CInt
fortyTwo = 42

foreign export ccall fortyTwo :: CInt
