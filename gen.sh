grafoin=$1
maxnodes=$2
echo "sort -n -k 1 $grafoin > tmp.txt"
`sort -n -k 1 $grafoin > tmp.txt`
echo "mv tmp.txt $grafoin"
`mv tmp.txt $grafoin`
echo "./scripts/vnmRemapV1 $grafoin $maxnodes 0 > $grafoin.graph-txt"
`./scripts/vnmRemapV1 $grafoin $maxnodes 0 > $grafoin.graph-txt`
echo "cat $grafoin.graph-txt | awk 'BEGIN{s=0}{if (NR == 1)print $1;else printf("%d %s\n", s++, $0);}' > $grafoin.net"
`cat $grafoin.graph-txt | awk 'BEGIN{s=0}{if (NR == 1)print $1;else printf("%d %s\n", s++, $0);}' > $grafoin.net`
