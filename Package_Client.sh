#!/usr/bin/bash -x
INSTALLDIR=nxt/client/bin/
rm -rf nxt/client
mkdir -p $INSTALLDIR
cp common/lib/libcommon.so $INSTALLDIR
cp common/lib/libfunctional_1_0.so $INSTALLDIR
OLDPWD=$PWD
cd $INSTALLDIR
ln -s ./libfunctional_1_0.so ./libfunctional.so
cd $OLDPWD
cp client/bin/UpdateClient $INSTALLDIR
cp client/scripts/UpdateClient.sh $INSTALLDIR
tar -cvzf nxt_client.tgz nxt/client
rm -rf nxt
