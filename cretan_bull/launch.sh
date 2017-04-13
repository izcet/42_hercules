#!/bin/bash

DIR=./cor/

if [ "$#" -eq "4" ] ; then
	./corewar -n $DIR$1.cor $DIR$2.cor $DIR$3.cor $DIR$4.cor
elif [ "$#" -eq "3" ] ; then
	./corewar -n $DIR$1.cor $DIR$2.cor $DIR$3.cor
elif [ "$#" -eq "2" ] ; then
	./corewar -n $DIR$1.cor $DIR$2.cor
elif [ "$#" -eq "1" ] ; then
	./corewar -n $DIR$1.cor
else
	./corewar
fi
