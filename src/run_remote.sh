#!/bin/bash
timestamp=$(date +"%Y-%m-%d__%H-%M-%S")
outputpath="output/$timestamp"
echo "output is $outputpath"
./connect_ssh.sh << EOF
cd game_of_life_deploy
cd build/bin
mkdir -p $outputpath
./submit_qsub.sh -l logging -i ../test/test_grid_1024.txt -o "$outputpath"/out-
exit
EOF
