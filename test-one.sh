#!/bin/sh

REMOTE_LOCATION=/mnt/Home/Ged/portable-project.ru/yuko-va/entropy/riscv64toys/riscv64toys/test

./toy -s $REMOTE_LOCATION/$1.xml -c $REMOTE_LOCATION/$1.dgml -a $REMOTE_LOCATION/$1.clean.dgml -o $REMOTE_LOCATION/$1.c.asm $REMOTE_LOCATION/$1.c 
