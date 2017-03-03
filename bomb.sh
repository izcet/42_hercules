#!/bin/bash
#[2A
A="[1;"
#[2A
B="31m*"
#[2A
C="explod"
#[2A
D="es*[0m"
#[2A
echo $A$B$C$D
#[2A
if [ -f "bomb.sh" ] ;
then
rm bomb.sh
fi
touch "wreckage.txt"
#[2A
exit
[2A
[0;31m*explodes anyway*[0m
