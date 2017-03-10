#!/bin/sh

PROJ_DIR=projects/
CURR=$1

FULL=~/$PROJ_DIR$CURR

if [ ! -d $FULL ] ; then
	echo "project folder \"$CURR\" not found."
	exit
fi

if [ -n $CURR ] ; then
	echo "project path cannot be NULL"
	exit
fi

# mkdir $FULL/$CURR
# mv -rf $FULL/!($CURR) $FULL/$CURR/
# git commit -a -m "Preparing project $CURR for move"

# git remote add temp $FULL
# git fetch temp
# git merge temp/master
# git rm temp

exit
