#!/bin/bash
./connect_ssh.sh << EOF
git clone -b openmp https://github.com/karnival/game_of_life.git game_of_life_deploy
cd game_of_life_deploy
mkdir build
cd build
cmake ..
make
exit
EOF
