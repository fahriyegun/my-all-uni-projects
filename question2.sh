#####################################################################
# 			 PROJECT 1 - QUESTION 2                     #
#                                                                   #
# 			FAHRİYE GÜN - 150112025                     #
#								    #
# 			FİLİZ DALIP - 150112078			    #	
#								    #
#####################################################################



echo -e "Enter a sequence of numbers followed by \"end\""
read value
max=0
a=0

#read integers until it reads the word "end"
while [ "$value" != "end" ]
do 
	#check this value it is integer or not
	if [[ $value = *[[:digit:]]* ]]; then
        	#if value is integer, compare with maximum value
	        if [ $value -gt $max ]
   		then
		#if value is greater than maksimum value, assign value to maximum
    		  max=$value
   		fi
 	else 
  	  echo "$value is not numeric! Enter a number...."
  	fi
read value
done

echo "Maximum : $max"
 


