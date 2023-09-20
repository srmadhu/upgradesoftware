#!/usr/bin/bash
INSTALLDIR=nxt/client/bin/
mkdir $INSTALLDIR
cp common/lib/libcommon.so $INSTALLDIR
cp common/lib/libfunctional_1_0.so $INSTALLDIR
ln -s $INSTALLDIR/libfunctional_1_0.so $INSTALLDIR/libfunctional.so
cp client/bin/UpdateClient $INSTALLDIR
cp client/scripts/UpdateClient.sh $INSTALLDIR
