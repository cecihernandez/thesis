grafoin=$1
maxnodes=$2
iter=$3
P=$4
ES=$5
dirout=$6

nodes=`wc -l $grafoin.txt | awk -F " " '{printf("%d",$1);}'`
rows=`wc -w $grafoin.txt | awk -F " " '{printf("%d",$1);}'`
edges=`echo "scale=2;($rows - $nodes)" | bc`
iterm1=`echo "scale=2;($iter - 1)" | bc`
echo "nodes $nodes edges $edges grafoin $grafoin maxnodes $maxnodes iter $iter iterm1 $iterm1 ES $ES dirout $dirout"
#./convertFormat.py $grafoin.txt $nodes $edges
#./executeDSM.py $grafoin.txt.bin $iter $dirout $P $ES
echo "-- $dirout-it-$iterm1"
./gen.sh $dirout-it-$iterm1 $maxnodes
