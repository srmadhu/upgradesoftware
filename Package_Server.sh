#!/usr/bin/bash -x
INSTALLDIR=nxt/server/bin/
rm -rf nxt/server
mkdir -p $INSTALLDIR
cp common/lib/libcommon.so $INSTALLDIR
cp common/lib/libfunctional_1_0.so $INSTALLDIR
cp common/lib/libfunctional_2_0.so $INSTALLDIR
cp server/bin/UpdateServer $INSTALLDIR
cp server/scripts/UpdateServer.sh $INSTALLDIR
tar -cvzf nxt_server.tgz nxt/server
rm -rf nxt
