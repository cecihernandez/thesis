graphin=$1
iter=$2
P=$3
ES=$4
dirout=$5

nodes=`wc -l $graphin.txt | awk -F " " '{printf("%d",$1);}'`
rows=`wc -w $graphin.txt | awk -F " " '{printf("%d",$1);}'`
edges=`echo "scale=2;($rows - $nodes)" | bc`
iterm1=`echo "scale=2;($iter - 1)" | bc`
maxnodes=`scripts/txtTOBIN $graphin.txt $nodes $edges`
echo "nodes $nodes edges $edges graphin $graphin maxnodes $maxnodes iter $iter iterm1 $iterm1 ES $ES P $2 dirout $dirout"
./executeDSM.py $graphin.txt.bin $iter $dirout $P $ES
./gen.sh $dirout-it-$iterm1 $maxnodes
#./runbv.sh $dirout-it-$iterm1 50 
./runbvw50m50.sh $dirout-it-$iterm1 50 
#./runbv-speed.sh $dirout-it-$iterm1-m3w7 $maxnodes
cd bvscripts/
./runllp-reord.sh $dirout-it-$iterm1-m50w50 $dirout-it-$iterm1-symgraph $dirout-it-$iterm1-sym.perm $dirout-it-$iterm1-llp-m50w50
./runllp-speed.sh $dirout-it-$iterm1-sym.perm $maxnodes $dirout-it-$iterm1-llp-m50w50 2000000
./runllp-speedall.sh $dirout-it-$iterm1-sym.perm $maxnodes $dirout-it-$iterm1-llp-m50w50
cd ../
