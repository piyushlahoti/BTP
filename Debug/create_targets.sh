# Target codes 
# Happy = 1 : 1 -1 -1 -1 -1 -1
# Sad   = 2: -1  1 -1 -1 -1 -1
# anger = 3: -1 -1  1 -1 -1 -1
# fear  = 4: -1 -1 -1  1 -1 -1 
# surp	= 5: -1 -1 -1 -1  1 -1
# disg  = 6: -1 -1 -1 -1 -1  1
count=0;
for i in dataset_test/*.png
do 

# prefix of the subject name. 
file=`echo $i | cut -d'/' -f 2`
name_prefix=`echo $file | cut -d'.' -f 1`
expression=`echo $name_prefix | cut -d'_' -f 3`

echo "${i},$expression"
#count=$((count+1))

#rename selected file.
#name="$sub_prefix" .'_' ."$count" .".png" 
#mv $i "${sub_prefix}_${count}_5.png"

#add this file to the list of targets.
#echo "${sub_prefix}_${count}_5.png   "
done

