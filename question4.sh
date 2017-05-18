#####################################################################
# 			 PROJECT 1 - QUESTION 4                     #
#                                                                   #
# 			FAHRİYE GÜN - 150112025                     #
#								    #
# 			FİLİZ DALIP - 150112078			    #	
#								    #
#####################################################################


#First argument is numerical system
#Others arguments are that will converting to another numerical systems

if [ -z $1 ]
then
echo ""
echo "Error: Empty input.... "
echo ""
exit 1
fi
 
echo " "

#check first argument about numerical system. If it is one of -r, -R, -a, -A ; converts number 
if [ $1 = "-r" ] || [ $1 = "-R" ] || [ $1 = "-a" ] || [ $1 = "-A" ] 
then
  
  for (( i=2; $i<=$#; i=$i+1 ))
  do
    #control number between 1 to 29
    if [ "${!i}" -gt 0 ] && [ "${!i}" -lt 30 ] 
    then
      if [ "$1" = "-r" ]
      then
        case ${!i} in
		1) echo "${!i} -> i";;
		2) echo "${!i} -> ii";;
		3) echo "${!i} -> iii";;
		4) echo "${!i} -> iv";;
		5) echo "${!i} -> v";;
		6) echo "${!i} -> vi";;
		7) echo "${!i} -> vii";;
		8) echo "${!i} -> viii";;
		9) echo "${!i} -> ix";;
		10) echo "${!i} -> x";;
		11) echo "${!i} -> xi";;
		12) echo "${!i} -> xii";;
		13) echo "${!i} -> xiii";;
		14) echo "${!i} -> xiv";;
		15) echo "${!i} -> xv";;
		16) echo "${!i} -> xvi";;
		17) echo "${!i} -> xvii";;
		18) echo "${!i} -> xviii";;
		19) echo "${!i} -> xix";;
		20) echo "${!i} -> xx";;
		21) echo "${!i} -> xxi";;
		22) echo "${!i} -> xxii";;
		23) echo "${!i} -> xxiii";;
		24) echo "${!i} -> xxiv";;
		25) echo "${!i} -> xxv";;
		26) echo "${!i} -> xxvi";;
		27) echo "${!i} -> xxvii";;
		28) echo "${!i} -> xxviii";;
		29) echo "${!i} -> xxix";;
	esac

     elif [ "$1" = "-R" ]
     then 
        case ${!i} in
		1) echo "${!i} -> I";;
		2) echo "${!i} -> II";;
		3) echo "${!i} -> III";;
		4) echo "${!i} -> IV";;
		5) echo "${!i} -> V";;
		6) echo "${!i} -> VI";;
		7) echo "${!i} -> VII";;
		8) echo "${!i} -> VIII";;
		9) echo "${!i} -> IX";;
		10) echo "${!i} -> X";;
		11) echo "${!i} -> XI";;
		12) echo "${!i} -> XII";;
		13) echo "${!i} -> XIII";;
		14) echo "${!i} -> XIV";;
		15) echo "${!i} -> XV";;
		16) echo "${!i} -> XVI";;
		17) echo "${!i} -> XVII";;
		18) echo "${!i} -> XVIII";;
		19) echo "${!i} -> XIX";;
		20) echo "${!i} -> XX";;
		21) echo "${!i} -> XXI";;
		22) echo "${!i} -> XXII";;
		23) echo "${!i} -> XXIII";;
		24) echo "${!i} -> XXIV";;
		25) echo "${!i} -> XXV";;
		26) echo "${!i} -> XXVI";;
		27) echo "${!i} -> XXVII";;
		28) echo "${!i} -> XXVIII";;
		29) echo "${!i} -> XXIX";;
	esac	
  
      elif [ "$1" = "-a" ]
      then 
        case ${!i} in
		1) echo "${!i} -> a";;
		2) echo "${!i} -> b";;
		3) echo "${!i} -> c";;
		4) echo "${!i} -> ç";;
		5) echo "${!i} -> d";;
		6) echo "${!i} -> e";;
		7) echo "${!i} -> f";;
		8) echo "${!i} -> g";;
		9) echo "${!i} -> ğ";;
		10) echo "${!i} -> h";;
		11) echo "${!i} -> ı";;
		12) echo "${!i} -> i";;
		13) echo "${!i} -> j";;
		14) echo "${!i} -> k";;
		15) echo "${!i} -> l";;
		16) echo "${!i} -> m";;
		17) echo "${!i} -> n";;
		18) echo "${!i} -> o";;
		19) echo "${!i} -> ö";;
		20) echo "${!i} -> p";;
		21) echo "${!i} -> r";;
		22) echo "${!i} -> s";;
		23) echo "${!i} -> ş";;
		24) echo "${!i} -> t";;
		25) echo "${!i} -> u";;
		26) echo "${!i} -> ü";;
		27) echo "${!i} -> v";;
		28) echo "${!i} -> y";;
		29) echo "${!i} -> z";;
	esac		

 
      elif [ "$1" = "-A" ]
      then 
        case ${!i} in
		1) echo "${!i} -> A";;
		2) echo "${!i} -> B";;
		3) echo "${!i} -> C";;
		4) echo "${!i} -> Ç";;
		5) echo "${!i} -> D";;
		6) echo "${!i} -> E";;
		7) echo "${!i} -> F";;
		8) echo "${!i} -> G";;
		9) echo "${!i} -> Ğ";;
		10) echo "${!i} -> H";;
		11) echo "${!i} -> I";;
		12) echo "${!i} -> İ";;
		13) echo "${!i} -> J";;
		14) echo "${!i} -> K";;
		15) echo "${!i} -> L";;
		16) echo "${!i} -> M";;
		17) echo "${!i} -> N";;
		18) echo "${!i} -> O";;
		19) echo "${!i} -> Ö";;
		20) echo "${!i} -> P";;
		21) echo "${!i} -> R";;
		22) echo "${!i} -> S";;
		23) echo "${!i} -> Ş";;
		24) echo "${!i} -> T";;
		25) echo "${!i} -> U";;
		26) echo "${!i} -> Ü";;
		27) echo "${!i} -> V";;
		28) echo "${!i} -> Y";;
		29) echo "${!i} -> Z";;
	esac
      fi
   else
   echo "${!i} -> is not between 1 to 29"
  fi
done

else
echo "$1 is not available numerical system...."
fi

echo ""
