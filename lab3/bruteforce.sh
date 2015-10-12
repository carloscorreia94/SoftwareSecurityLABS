#!/bin/sh


old=`Returned Properly`
oldgh=`Returned Properly`
new=`Returned Properly`
count=1
while [ "$old" = "$new" ]
do
    ./exploit | echo $count &
    new=$(./stack)
	count=$((count+1))
echo $oldgh
echo $new
done

echo "STOP... The root thing worked"
