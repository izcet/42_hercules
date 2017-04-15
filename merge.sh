#!/bin/sh

PROJ_DIR=projects/
CURR=$1

BACK=~/backups/projects/hercules

FULL=~/$PROJ_DIR$CURR

if [ ! -d $FULL ] ; then
	echo "project folder \"$CURR\" not found."
	exit
fi

if [ -z $CURR ] ; then
	echo "project path cannot be NULL"
	exit
fi

mkdir $FULL/$CURR
mv -f $FULL/* $FULL/$CURR/

cd $FULL
git add .
git commit -a -m "Preparing project $CURR for move"

cd $BACK
git remote add temp $FULL
git fetch temp
git merge temp/master
git rm temp
gp

cd $FULL
mv -f $CURR/* .
rm -r $CURR
git add .
git commit -a -m "Project $CURR moved and restored"

cd $BACK
exit
