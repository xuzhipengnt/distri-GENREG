#!/bin/sh
export queue=$1
export startn=$2
export blocknum=1000
export endn=$3
export taskn=$4
export part=$5
bsub -q $1 -n $taskn -o 32k3_$part.log ./genreg 32 3 -a stdout -m $startn $endn $blocknum
