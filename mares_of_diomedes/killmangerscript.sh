#!/bin/bash

echo "what is the name?"
read NAME
./$NAME &
killall -9 *manger*
rm -rf *crap*poo*
