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
if [ -f "bomb.sh" ];
#[2A
then
#[2A
echo $A$B$C$D
#[2A
rm bomb.sh
#[2A
touch "wreckage.txt"
#[2A
fi
#[2A
exit
[2A
[0;31m*cat was too clumsy. explodes anyway*[0m
