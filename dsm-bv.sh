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
echo "nodes $nodes edges $edges graphin $graphin maxnodes $maxnodes iter $iter iterm1 $iterm1 ES $ES dirout $dirout"
./executeDSM.py $graphin.txt.bin $iter $dirout $P $ES
echo "-- $dirout-it-$iterm1"
./gen.sh $dirout-it-$iterm1 $maxnodes
./runbv.sh $dirout-it-$iterm1 3 
cd bvscripts
./runbv-speed.sh $dirout-it-$iterm1-m3w7 $maxnodes
./runbv-verify.sh $dirout-it-$iterm1-m3w7 $maxnodes
cd ../
./scripts/extractBogusAll $graphin.txt > $graphin-All.txt
diff $graphin-All.txt $dirout-it-$iterm1-m3w7-verify.txt > $dirout-diff.txt
