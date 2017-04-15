#!/bin/sh

## User Variables #############################################################

# Default Library
LIB=libft

# Location of Default Library
LDIR=~/backups/projects

## Variables ##################################################################

# Output directory for C includes
INC=inc

# Output directory for C source code
SRC=src

# Name of C Makefile
MAK=Makefile

# Default git directory. (Is updated if $GIT_DIR is set)
GIT=.git

# File containing vim commands to be run on each file
VIM=.vim_commands

# The commands in said file
COM=":Stdheader\ndd\n:wq"

# Colors, for beauty
R='\033[31m' # Red
Y='\033[33m' # Yellow
G='\033[32m' # Green
C='\033[36m' # Cyan
B='\033[34m' # Blue
P='\033[35m' # Purple
W='\033[37m' # White
N='\033[0m'	 # No Color

## Functions ##################################################################

# Output a red error message
# usage: error <text>
error () {
	echo "${R}Error: $1${N}"
}

# Create a file inside vim and run the commands
# usage: make_with_vim <filename>
make_with_vim () {
	if [ -z $1 ] ; then
		error "NULL parameter passed to ${P}make_with_vim()"
		return 1
	fi
	echo "${G}Creating file ${P}$1"
	vim -s $VIM $1
}

# Create a directory. somewhat redundant
# usage: make_dir <directory>
make_dir () {
	if [ -z $1 ] ; then
		error "NULL parameter passed to ${P}make_dir()"
		return 1
	fi
	echo "${G}Creating directory ${P}$1"
	mkdir $1
}

# Append a line of text to the end of the Makefile
# usage: add_line <text>
add_line () {
	echo "$1" >> $MAK
}

# Insert a line of text at a specific line number
# WARNING: may be off-by-one. check before use
# usage: insert_at <text> <line number>
insert_at () {
	head -n $2 $MAK > .temp$MAK
	echo "$1\c" >> .temp$MAK
	tail -n +$2 $MAK >> .temp$MAK
	mv .temp$MAK $MAK
}

# Add the necessary blocks of code to a C Makefile to include a library
# Initially uses default values later in this code
# WARNING: But those values have to be set before each new call
# usage: add_lib 
add_lib () {
	if [ ! -d $LDIR/$LIB ] ; then
		error "No directory found at ${P}$LDIR/$LIB$R"
		return 1
	fi
	if [ -d ./$LIB ] ; then
		error "Library $P$LIB$R already exists in this directory."
		return 1
	fi
	make_dir ./$LIB
	echo "${B}Copying files from library ${P}$LDIR/$LIB"
	ls -1A $LDIR/$LIB/ | grep -v .git | xargs -I % cp -rf $LDIR/$LIB/% ./$LIB/
	echo "${B}Adding necessary lines to ${P}$MAK"
	NLIB=$(echo $LIB | awk '{print toupper($0)}')
	add_line "\n\$($NLIB):"
	add_line "\t@\$(MAKE) -C \$(${NLIB}_DIR)"
	insert_at "" 27
	insert_at "$NLIB\t\t=\t\$(${NLIB}_DIR)/\$(${NLIB}_LIB)" 27
	insert_at "${NLIB}_INC\\t=\\t#includes directory, if applicable" 27
	insert_at "${NLIB}_LIB\t=\t$LIB.a #assuming project is named the same" 27
	insert_at "${NLIB}_DIR\t=\t$LIB" 27
	sed -i '' -e "s|I $INC|I \$(${NLIB}_DIR)/\\\$(${NLIB}_INC) -I $INC|" $MAK
	sed -i '' "s/^.PHONY: /.PHONY: $LIB /" $MAK
	sed -i '' "s/^all: /all: \$($NLIB) /" $MAK
	# This nonsense here. sed requires an escaped literal newline and tab
	sed -i '' "s/^clean:/clean:\\
	@cd \$(${NLIB}_DIR) \&\& make clean/" $MAK
	sed -i '' "s/^fclean:/fclean:\\
	@cd \$(${NLIB}_DIR) \&\& make fclean/" $MAK
	sed -i '' "s/\$(CC) \$(FLAGS)/\$(CC) \$(FLAGS) \$(${NLIB})/" $MAK
}

## Code #######################################################################

echo "\033[0m\c" #clear the font styling

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

echo "${W}What kind of project is ${P}$NAME${W} going to be?"
echo "\t${C}[1]${W} Shell Script"
echo "\t${C}[2]${W} C Code"
echo "\t${C}[3]${W} Other"
read TYPE

if [ "$TYPE" -eq "1" ] ; then
	echo "${G}Initiallizing a new Shell project."
elif [ $TYPE -eq 2 ] ; then
	echo "${G}Initializing a new C project."
elif [ $TYPE -eq 3 ] ; then
	echo "${G}Initializing a new project."
else
	error "${C}$TYPE${R} is not a valid response."
	exit
fi

echo "${B}Initializing git repository."
git init $NAME >> /dev/null

cd $NAME
echo "Entering repository."

echo "${W}What is the ${C}vogsphere${W} repository url?"
read URL
while [ -z $URL ] ; do
	error "Directory or URL cannot be NULL"
	echo "${W}What is the ${C}vogsphere${W} repository url?"
	read URL
done
echo "${B}Adding remote ${C}origin${B} at ${P}$URL${B}"
git remote add origin $URL
if [ "$?" -eq 1 ] ; then
	error "Invalid repository. ${C}origin${R} will have to be manually set."
	git remote rm origin
	echo "${B}Remote ${C}origin${B} removed."
else
	git pull origin master 2> /dev/null
fi

echo "${W}(OPTIONAL) What is the ${C}github${W} repository url?"
echo "Press enter to skip..."
read URL
if [ ! -z $URL ] ; then
	echo "${B}Adding remote ${C}gh${B} at ${P}$URL${B}"
	git remote add gh $URL
	if [ "$?" -eq 1 ] ; then
		error "Invalid repository. ${C}gh${R} will have to be manually set."
		git remote rm gh
		echo "${B}Remote ${C}gh${B} removed."
	else
		git pull gh master 2> /dev/null	
	fi
else
	echo "\033[1A${B}Skipping..."
fi

if [ ! -z $GIT_DIR ] ; then
	GIT=$GIT_DIR
fi
echo "${B}Setting gitignore."
if [ "$TYPE" -eq "2" ] ; then
	echo "*.[oa]" >> $GIT/info/exclude
fi
echo "*.swp" >> $GIT/info/exclude

if [ "$TYPE" -eq "1" ] ; then
	echo "${G}Creating file ${P}$NAME.sh"
	echo "#!/bin/sh\n" > $NAME.sh
fi

if [ "$TYPE" -eq "2" ] ; then
	echo "$COM" >> $VIM

	make_dir $SRC
	make_dir $INC

	make_with_vim $INC/$NAME.h
	echo "${B}Protecting against double inclusion."
	echo "#ifndef $(echo $NAME | awk '{print toupper($0)}')_H" >> $INC/$NAME.h
	echo "# define $(echo $NAME | awk '{print toupper($0)}')_H" >> $INC/$NAME.h
	echo "\n\n\n#endif" >> $INC/$NAME.h

	make_with_vim $MAK
	echo "${B}Prepopulating text in ${P}$MAK"
	add_line "NAME\t\t=\t$NAME\n" 					#line 13, 14
	add_line "CC\t\t\t=\tgcc"							#line 15
	add_line "CFLAGS\t\t=\t-Wall -Werror -Wextra"		#line 16
	add_line "XFLAGS\t\t=\t#-flags -for -X"			#line 17
	add_line "FLAGS\t\t=\t\$(CFLAGS) \$(XFLAGS)\n" #18 19
	add_line "SRC_DIR\t\t=\t$SRC"
	add_line "SRC_FILE\t=\t##!!##"
	add_line "SRCS\t\t=\t\$(addprefix \$(SRC_DIR)/, \$(SRC_FILE))\n"
	add_line "OBJ_DIR\t\t=\tobj"
	add_line "OBJ_FILE\t=\t\$(SRC_FILE:.c=.o)"
	add_line "OBJS\t\t=\t\$(addprefix \$(OBJ_DIR)/, \$(OBJ_FILE))\n"
	add_line "INC_DIR\t\t=\t-I $INC\n" # append text to specific lines
	add_line ".PHONY: all clean fclean re\n" #libft
	add_line "all: \$(NAME)\n"
	add_line "\$(NAME): \$(SRCS) | \$(OBJS)"
	add_line "\t\$(CC) \$(FLAGS) \$(OBJS) \$(INC_DIR) -o \$(NAME)\n"
	add_line "\$(OBJ_DIR)/%.o: \$(SRC_DIR)/%.c | \$(OBJ_DIR)"
	add_line "\t@\$(CC) -c \$^ \$(CFLAGS) \$(INC_DIR) -o \$@\n"
	add_line "clean:"
	add_line "\t@rm -rf \$(OBJ_DIR)\n"
	add_line "fclean: clean"
	add_line "\t@rm -f \$(NAME)\n"
	add_line "re: fclean all\n"
	add_line "\$(OBJ_DIR):"
	add_line "\t@mkdir -p \$(OBJ_DIR)"

	echo "${W}Would you like to include $P$LIB$W from $P$LDIR$W ?"
	echo "\t${C}[1]$W yes"
	echo "\t${C}[2]$W no"
	read TYPE
	if [ "$TYPE" -eq "1" ] ; then
		add_lib
	elif [ "$TYPE" -ne "2" ] ; then
		error "${C}$TYPE${R} is not a valid response."
	fi

	echo "${W}Would you like to include another library?"
	echo "\t${C}[1]$W yes"
	echo "\t${C}[2]$W no"
	read TYPE
	while [ "$TYPE" -eq "1" ] ; do
		echo "${W}Enter library directory name:"
		read LIB
		echo "Enter path to library: (full path to library)"
		read LDIR
		add_lib
		echo "${W}Would you like to include another library?"
		echo "\t${C}[1]$W yes"
		echo "\t${C}[2]$W no"
		read TYPE
	done
	if [ "$TYPE" -ne "2" ] ; then
		error "${C}$TYPE${R} is not a valid response."
	fi
	rm $VIM
fi

echo "${B}Adding files to git and making first commit.${W}"
git add .
git status
git commit -m "Initial commit"
echo "\n\t${G}Done.${N}\n"
