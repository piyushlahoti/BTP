# Target codes 
# Happy = 1 : 1 -1 -1 -1 -1 -1
# Sad   = 2: -1  1 -1 -1 -1 -1
# anger = 3: -1 -1  1 -1 -1 -1
# fear  = 4: -1 -1 -1  1 -1 -1 
# surp	= 5: -1 -1 -1 -1  1 -1
# disg  = 6: -1 -1 -1 -1 -1  1
count=0;
for i in *.png
do 

# prefix of the subject name. 
sub_prefix=`echo $i | cut -d'_' -f 1`
count=$((count+1))

#rename selected file.
#name="$sub_prefix" .'_' ."$count" .".png" 
mv $i "${sub_prefix}_${count}_5.png"

#add this file to the list of targets.
echo "${sub_prefix}_${count}_5.png   "
done

