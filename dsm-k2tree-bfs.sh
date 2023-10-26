grafoin=$1
maxnodes=$2
iter=$3
P=$4
ES=$5
dirout=$6
dirad=$7

nodes=`wc -l $grafoin.txt | awk -F " " '{printf("%d",$1);}'`
rows=`wc -w $grafoin.txt | awk -F " " '{printf("%d",$1);}'`
edges=`echo "scale=2;($rows - $nodes)" | bc`
iterm1=`echo "scale=2;($iter - 1)" | bc`
echo "nodes $nodes edges $edges grafoin $grafoin maxnodes $maxnodes iter $iter iterm1 $iterm1 ES $ES dirout $dirout"
cp $dirad-it-$iterm1-l8.map $dirout-it-$iterm1.map
cp $dirad-it-$iterm1 $dirout-it-$iterm1
cd k2treescripts/
./k2treeformat.sh ../$dirout-it-$iterm1 $maxnodes
./runk2tree-bfs.sh ../$dirout-it-$iterm1 4 2 5 $maxnodes
./recoverk2tree-bfs.sh ../$dirout-it-$iterm1 4 2 5
./runk2tree-speedall-bfs.sh ../$dirout-it-$iterm1 4 2 5 $maxnodes
cd ../
diff $dirout-it-$iterm1-bfsad-4-2-5.rb $dirout-it-$iterm1-bfsad.bin > $dirout-it-$iterm1-bfsad-diff.txt
