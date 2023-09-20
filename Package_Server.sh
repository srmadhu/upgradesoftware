#!/usr/bin/bash
INSTALLDIR=nxt/server/bin/
mkdir $INSTALLDIR
cp common/lib/libcommon.so $INSTALLDIR
cp common/lib/libfunctional_1_0.so $INSTALLDIR
cp common/lib/libfunctional_2_0.so $INSTALLDIR
cp client/bin/UpdateServer $INSTALLDIR
cp client/scripts/UpdateServer.sh $INSTALLDIR
