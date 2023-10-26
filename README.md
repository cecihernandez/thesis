# thesis
Compressed representations for web and social networks
Code for paper: The implementation is from 2014 and not been updated since then.
"Compressed representations for web and social networks" (kais 2014):

There are 2 different applications based on the same idea. One uses dense subgraphs in addition to virtual nodes and the other
extract dense subgraphs and apply compact data structures. See the paper for more details.

Both codes use boost_1_40_0 (accesible at http://www.boost.org/doc/libs/1_40_0/more/getting_started/unix-variants.html)

scripts running complete complete tests including computing query times.
        Main  scripts: the following scripts do all what is needed to generate the compressed graphs using
        DSM. Scripts also include the measure of out-neighbor queries. The script dsm-bv.sh also include
        a script that verifies the recovery of the original graph without the self-loops.
                - dsm-bv.sh (uses dsm + BV (conserving the node ordering)
                - dsm-llp.sh (uses dsm + BVLLP (changing the node ordering to LLP)
                - dsm-ad.sh (uses dsm + AD (Apostolico and Drovando default code changes a BFS ordering)
                - dsm-k2tree-nat.sh (uses dsm + k2treeNAT)
                - dsm-k2tree-bfs.sh (uses dsm + k2treeBFS). This combination uses the BFS ordering captured
                        with AD so the k2treeBFS stuff must be done based on the dsm + ad run.
        Using dense subgrapsh:
                - dense-k2tree.sh (uses vnmextract to extract dense subgraphs, uses libcds(v1.0) with Wavelet trees and compressed bitmaps for H component and k2tree with natural ordering for R component.

To compute total space.
        - dsm + bv alternative. Go to bvscripts directory and run ./spacebv.sh transformed_graph:bitmap:num_edges_without_selfloop
                Example. ./spacebv.sh ../outputdir/eu-2005-adj-it-9-m3w7:../outputdir/eu-2005-it-9:18733713
        - dsm + llp alternative. Go to bvscripts directory and run ./spacellp.sh transformed_graph:bitmap:num_edges_without_selfloop
                Example. ./spacellp.sh ../outputdir/eu-2005-adj-it-9-llp-m3w7:../outputdir/eu-2005-it-9:18733713
        - dsm + ad alternative. Go to adscripts directory and run ./spacead.sh transformed_graph:bitmap:num_edges_without_selfloop
                Example. ./spacead.sh ../outputdir/eu-2005-adj-it-9-l8:../outputdir/eu-2005-it-9:18733713

Description of some programs:
        - txtToBin: takes a graph in txt format (eu-2005-adj.txt), with node: <ordered outlinks separated by spaces>,
                nodes without outlinks not included. It generates a binary graph eu-2005-adj.txt.bin
        - extractBogusAll: read a text format graph and prints out the graph without self-loops.
        - query: read a graph in text format (with virtual nodes) and converts it to a graph without virtual nodes (i.e
                        it recovers the original graph)
        - compile: g++ -o txtToBin txtToBin.cpp, and g++ -o extractBogusAll extractBogusAll.cpp

Input graph for the 2 applications (./dsm/vnm and ./dsextract/vnmextract) is given in binary using the following format:
number_nodes number_edges -node <sorted outlinks> -node <sorted outlinks> ...
You can convert a text format graph to the binary format using the script txtTOBIN.cpp

A. Using dense subgraphs with virtual nodes (source code in dsm directory).
 - Modify the Makefile to define the boost directory
 - compile: make
 - executable: vnm
 - Parameters: graph_bin_format format(1) shingles_size(1) threshold bcsize output_dir/outfileprefix
        format=1: is the binary format explained above
        shingle_size: is the number of edges considered for hashing (I used 1)
        num_iterations: is the number of iterations
        output_dir/outfileprefix: is the output and file directory (directory must exist previously to execution)
        num_hashes: is the number of hashes used for clustering (I used 2)
        bcsize: is the size of dense subgraphs to consider (|S|*|C|)

        input: the input graph in binary (built with txtTOBin)
        output:
                - num_iterations graphs with extension .res (contains the compression rate in terms of number of edges).
                - a graph in text format ( node_id: sorted outlinks separated by spaces).
