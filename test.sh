#!/bin/sh

REMOTE_LOCATION=/mnt/Home/Ged/portable-project.ru/yuko-va/entropy/riscv64toys/riscv64toys/test
ASAN_OPTIONS=detect_leaks=0 ./toy -s $REMOTE_LOCATION/test.xml -c $REMOTE_LOCATION/test.dgml -a $REMOTE_LOCATION/test.clean.dgml -o $REMOTE_LOCATION/test.c.asm $REMOTE_LOCATION/test.c

# riscv64-linux-gnu-as --gen-debug -o $REMOTE_LOCATION/test.c.o $REMOTE_LOCATION/test.c.asm
# gcc -o $REMOTE_LOCATION/test $REMOTE_LOCATION/test.c.o

