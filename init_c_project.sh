#!/bin/shi

## Variables ##################################################################

INC=inc
SRC=src
MAK=Makefile

GIT=.git
VIM=.stdheader # file to call that contains vim commands for a new file

R='\033[31m' # Red
Y='\033[33m' # Yellow
G='\033[32m' # Green
C='\033[36m' # Cyan
B='\033[34m' # Blue
P='\033[35m' # Purple
W='\033[37m' # White
N='\033[0m'	 # No Color

## Functions ##################################################################

error () {
	echo "${R}Error: $1${N}"
}

stdheader () {
	if [ -z $1 ] ; then
		error "NULL parameter passed to ${P}stdheader()"
		return 1
	fi
	echo "${G}Creating file ${P}$1"
	vim -s $VIM $1
}

make_dir () {
	if [ -z $1 ] ; then
		error "NULL parameter passed to ${P}make_dir()"
		return 1
	fi
	echo "${G}Creating directory ${P}$1"
	mkdir $1
}

## Code #######################################################################

echo "\033[0m\c" #clear the font styling

echo "${G}Initializing a new C project."
echo "${W}What is the name of the project?"
read NAME

if [ -z "$NAME" ] ; then
	error "The name of the project cannot be NULL."
	exit
fi

if [ -d $NAME ] ; then
	error "A directory called ${P}$NAME${R} already exists."
	exit
fi

if [ -f $NAME ] ; then
	error "A file named ${P}$NAME${R} already exists."
	exit
fi

echo "${G}Initializing project ${P}$NAME${G}."

echo "${B}Initializing git repository."
git init $NAME >> /dev/null

cd $NAME
echo "Entering repository."
if [ ! -z $GIT_DIR ] ; then
	GIT=$GIT_DIR
fi
echo "Setting gitignore."
echo "*.[oa]" >> $GIT/info/exclude
echo "*.swp" >> $GIT/info/exclude

make_dir $SRC
make_dir $INC
stdheader $MAK
