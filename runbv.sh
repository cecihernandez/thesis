#!/bin/bash

export CLASSPATH=$CLASSPATH:./bvutils/colt-1.2.0.jar:./bvutils/log4j-over-slf4j-1.7.7.jar:./bvutils/slf4j-api-1.7.7.jar:./bvutils/jsap-2.1.jar:./bvutils/fastutil-6.5.15.jar:./bvutils/dsiutils-2.2.0.jar:./bvutils/sux4j-3.1.2.jar:./bvutils/stax-api-1.0.1.jar:./bvutils/commons-math3-3.2.jar:./bvutils/webgraph-3.4.0.jar:.

java -Xmx16g it.unimi.dsi.webgraph.BVGraph -m $2 -w 7 -g ASCIIGraph $1 $1-m$2w7 
