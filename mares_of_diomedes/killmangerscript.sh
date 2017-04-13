#!/bin/bash

ulimit -u 200
echo "you should run top in another terminal"
echo "you should also look up pkill -9 -g"
echo ""
echo "what is the name?"
read NAME
./$NAME &
killall -9 *manger*
rm -rf *crap*poo*
