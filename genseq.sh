#!/bin/bash	

dirin=$1
maxnodes=$2
dirout=$3

#arr=`/bin/ls $dirin`

# get first character of dirin, if 
first=${dirin:0:1}

dos=$(echo $dirin | tr "/" "\n")
n=0
for x in $dos
do
   let n=$n+1
done
filename=$x

#echo " filename $filename"

m=0
dir=""
for x in $dos
do
   let m=$m+1
   #echo " m $m n $n x $x"
   #if [ $m -lt 2 && $first -eq "a" ]
   if [ $m -lt 2 ]
   then 
	 if [ $first == "/" ]
         then
        	dir=`echo $dir/$x`
   	 else
        	dir=`echo $dir$x`
	 fi
   elif [ $m -lt $n ]
   then
        dir=`echo $dir/$x`
   fi
done

#echo "dir $dir"
arr=`/bin/ls $dir`

max=0
for i in ${arr} ; do
	#name=`echo $2${i}|grep -v biclique | awk -F "-it-" '{printf("%s",$2);}'`
	name=`echo $x${i}|grep -v biclique | awk -F "-it-" '{printf("%s",$2);}'`
	if [ "$name" != "" ]	
	then
		if [ $name -gt $max ]
		then 
			max=$name
		fi
		#echo "name $name"
	fi
done
let max1=$max+1
#echo " ./densescripts/createSeq $dirin-biclique-it- $max1 0 > $dirout/out.txt"
./densescripts/createSeq $dirin-biclique-it- $max1 0 > $dirout/out.txt
#echo " ./densescripts/sequences/buildStructure $filename-biclique-it-sequencebin 64 r $filename-biclique-it-bitmappos.txt wt $maxnodes r $dir/ $dirout/ > $dirout/sizes-$filename-64-r-wt.txt"
./densescripts/sequences/buildStructure $filename-biclique-it-sequencebin 64 r $filename-biclique-it-bitmappos.txt wt $maxnodes r $dir/ $dirout/ > $dirout/sizes-$filename-64-r-wt.txt
echo "$max"
