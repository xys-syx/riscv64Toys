#!/bin/sh

REMOTE_LOCATION=/mnt/Home/Ged/portable-project.ru/yuko-va/entropy/riscv64toys/riscv64toys/test

./toy -s $REMOTE_LOCATION/test.xml -c $REMOTE_LOCATION/test.dgml $REMOTE_LOCATION/test.c
./toy -s $REMOTE_LOCATION/branches.xml -c $REMOTE_LOCATION/branches.dgml $REMOTE_LOCATION/branches.c
./toy -s $REMOTE_LOCATION/types.xml -c $REMOTE_LOCATION/types.dgml $REMOTE_LOCATION/types.c
