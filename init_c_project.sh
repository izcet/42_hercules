#!/bin/shi

INC=inc
SRC=src
MAK=Makefile

GIT=.git

echo "Initializing a new C project."
echo "What is the name of the project?"
read NAME

if [ -z "$NAME" ] ; then
	echo "The name of the project cannot be NULL."
	exit
fi

if [ -d $NAME ] ; then
	echo "A directory called \"$NAME\" already exists."
	exit
fi

if [ -f $NAME ] ; then
	echo "A file named \"$NAME\" already exists."
	exit
fi


git init $NAME

if [ ! -z $GIT_DIR ] ; then
	GIT=$GIT_DIR
fi

error () {
	echo "${RED}Error: $1${NOC}"
}

stdheader () {
	if [ -z $1 ] ; then
		error "NULL param passed to stdheader"
		return 1
	fi
	vim -s .stdheader $NAME/$1
}




#mkdir $NAME
#touch $NAME/$MAK
#vim -s .stdheader $NAME/$MAK
stdheader $MAK
stdheader ""
stdheader "dickweed"
