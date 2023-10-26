#!/bin/bash

export CLASSPATH=$CLASSPATH:./bvutils/colt-1.2.0.jar:./bvutils/log4j-over-slf4j-1.7.7.jar:./bvutils/slf4j-api-1.7.7.jar:./bvutils/jsap-2.1.jar:./bvutils/fastutil-6.5.15.jar:./bvutils/dsiutils-2.2.0.jar:./bvutils/sux4j-3.1.2.jar:./bvutils/stax-api-1.0.1.jar:./bvutils/commons-math3-3.2.jar:./adutils/gc-noBV-0.2.1.jar:.

java -Xms16g -Xmx16g -d64 it.uniroma3.dia.gc.Main ac $1 -l $2 -map 
mv $1.map $1-l$2.map
mv $1.gc $1-l$2.gc
