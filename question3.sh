#####################################################################
# 			 PROJECT 1 - QUESTION 3                     #
#                                                                   #
# 			FAHRİYE GÜN - 150112025                     #
#								    #
# 			FİLİZ DALIP - 150112078			    #	
#								    #
#####################################################################



numbers='^[0-9]+$'
if [ -z "$1" ]
then
	echo ""
	echo "Please retry with a number"
	echo ""
	exit 1

elif [ $# -gt 1 ]
then
	echo ""
	echo "Only first argument is accepted. Others are disabled."
	echo ""
	exit 1

elif ! [[ $1 =~ $numbers ]]
then
	echo ""
	echo "error: $1 is not a number" 
	echo ""
	exit 1

fi
LANG=en_US

echo ""

for (( day_limit=0; day_limit<=` expr $1 - 1 `; day_limit++ ))
do
	#echo $day_limit
	date_to_find="$(date +'%a %b %d' --date="$day_limit days ago")"
	boot_count="$(last reboot | grep "$date_to_find" |wc -l)"
	echo "$(date +'%d'/'%m'/'%Y' --date="$day_limit days ago") booted $boot_count times"
	#echo $date_to_find
done
