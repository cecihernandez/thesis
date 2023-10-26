#./dsm-ad.sh test/eu-2005-adj 10 2 6 testoutad/eu-2005-adj
#./dsm-bv.sh test/eu-2005-adj 10 2 30 testoutbv/eu-2005-adj
#./dsm-llp.sh test/eu-2005-adj 10 2 30 testoutllp/eu-2005-adj
#./dense-k2tree.sh test/eu-2005-adj 862664 1000 2 1000,500 testdense/eu testdense/seq
#./dsm-k2tree-nat.sh test/eu-2005-adj 862664 10 2 15 outdsmk2tree/eu-2005-adj
./dsm-k2tree-bfs.sh test/eu-2005-adj 862664 10 2 15 outdsmk2treebfs/eu-2005-adj testoutad/eu-2005-adj
#./dsm-llp.sh test/eu-2005-adj 10 2 6 testoutes6/eu-2005-adj
#./dsm-llpw50m50.sh test/eu-2005-adj 10 2 30 testoutes30/eu-2005-adj
