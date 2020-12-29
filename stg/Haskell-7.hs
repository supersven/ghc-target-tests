{-# LANGUAGE RecordWildCards #-}
module Foo where

import GHC.IO.Handle.FD
import GHC.IO.Buffer
import qualified GHC.IO.Handle as Handle
import GHC.IO.Handle.Types
import GHC.IO.Handle.Internals
import GHC.IORef
import Control.Monad
import Foreign
import Foreign.C

foreign import ccall unsafe "stdio.h printf" printf :: CString -> IO()

printHello :: IO ()
printHello = do
    s <- newCString "Hallo"
    printf s
