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
#echo "-- $dirout-it-$iterm1"
#./gen.sh $dirout-it-$iterm1 $maxnodes
#./runbv.sh $dirout-it-$iterm1 3
#cd bvscripts/
#./runllp-reord.sh $dirout-it-$iterm1-m3w7 $dirout-it-$iterm1-symgraph $dirout-it-$iterm1-sym.perm $dirout-it-$iterm1-llp-m3w7
#./runllp-speedall.sh $dirout-it-$iterm1-sym.perm $maxnodes $dirout-it-$iterm1-llp-m3w7
#cd ../
cd k2treescripts/
#./k2treeformat.sh ../$dirout-it-$iterm1 $maxnodes
./runk2tree-llp.sh ../$dirout-it-$iterm1 4 2 5 $maxnodes
#./recoverk2tree-bfs.sh ../$dirout-it-$iterm1-llp-4-2-5
./runk2tree-speedall-llp.sh ../$dirout-it-$iterm1 4 2 5
cd ../
#diff $dirout-it-$iterm1-bfsad-4-2-5.rb $dirout-it-$iterm1-bfsad.bin > k2treescripts/diff.txt
