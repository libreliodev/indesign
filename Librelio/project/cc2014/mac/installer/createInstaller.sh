#!/bin/bash
cd installer
cp Librelio.mxi ../../../../build/cc2014/mac/release/
./ZXPSignCmd -sign ../../../../build/cc2014/mac/release Librelio.zxp ../../common/key.p12 adobe