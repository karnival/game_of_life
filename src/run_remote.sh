#!/bin/bash
./connect_ssh.sh << EOF
cd game_of_life_deploy
cd build/bin
./submit_qsub.sh -o outputdata -l logging -i ../test/test_grid_1024.txt
exit
EOF
