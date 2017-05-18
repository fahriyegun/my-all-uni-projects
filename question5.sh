#####################################################################
# 			 PROJECT 1 - QUESTION 5                     #
#                                                                   #
# 			FAHRİYE GÜN - 150112025                     #
#								    #
# 			FİLİZ DALIP - 150112078			    #	
#								    #
#####################################################################



#if no argument, delete allzero file in current directory and subdirectory
echo ""

if  test $# -gt 1
then 
echo "there is greter than one input. Try again..."
echo ""
exit 1
elif [ -z $1 ] 
then
   echo ""	
   find $PWD -size 0 | wc -l
   echo  "zero-length files are removed from the directory: $PWD"
   find . -size 0c -delete
   #find . -type f -size 0
   echo ""	
   exit 1
fi

echo ""
#if there is an argument, search that and when there is this directory, delete allzero length file of input directory
if find . -maxdepth 1 -name "$1" -print -quit | grep -q . 
then
  echo "You found the file"
  find $1 -size 0 | wc -l
  echo  "zero-length files are removed from the directory: $1"
  cd $1
  find . -size 0c -delete
   echo ""
   exit 1
else 
#if not found this argument, Give an error!!
  echo "This directory is not found!!"
  echo ""
  exit 1
fi



