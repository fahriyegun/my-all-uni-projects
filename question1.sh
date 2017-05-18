#####################################################################
# 			 PROJECT 1 - QUESTION 1                     #
#                                                                   #
# 			FAHRİYE GÜN - 150112025                     #
#								    #
# 			FİLİZ DALIP - 150112078			    #	
#								    #
#####################################################################

# Takes name of file or directory as an argument
 
#control this argument
#If argument number is greter than 1, give warnings.
if [ $# -gt 1 ]
then
echo " "
echo "Please enter only one input..."
echo " "
exit 1
#if input in null, give warnings
elif test -z $1
then
echo ""
echo "Opps! Empty input. Please try again...."
echo " "
exit 1
#if ther is input file, tell us that we find 
elif test -a $1
then
echo " "
echo "Yes, we find this argument in current directory"
#if there is no this file, give us error
else
echo " "
echo "NOT FOUND THIS FILE!!"
echo ""
exit 1
fi

# find out if file has write permission or not
[ -w $1 ] && W="write" || W="not write"
 
# find out if file has excute permission or not
[ -x $1 ] && X="execute" || X="not execute"
 
# find out if file has read permission or not
[ -r $1 ] && R="read" || R="not read"

#If this is a file, control that permissions of this file 
if test -f $1
then
echo "$1 is a file"
echo "$1 has $W permission and $R permission and $X permission for the user! "
echo ""
exit 1
fi

#If this is a directory, control that permissions of this directory 
if test -d $1
then
echo "$1 is a directory"
echo "$1 has $W permission and $R permission and $X permission for the user! "
echo ""
exit 1
fi

#If this is a symbolic link, control that permissions of this link 
if test -h $1
then
echo "$1 is a link"
echo "$1 has $W permission and $R permission and $X permission for the user! "
echo ""
exit 1
fi


