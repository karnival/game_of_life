#!/bin/bash
while getopts ":l:o:i:" opt; do
  case $opt in
    l)
      log=$OPTARG >&2
      ;;
    o)
      out_file=$OPTARG >&2
      ;;
    i)
      init_file=$OPTARG >&2
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
    :)
      echo "Option -$OPTARG requires an argument." >&2
      exit 1
      ;;
  esac
done

if [[ -z $log|| -z $out_file || -z $init_file ]]; then
  echo 'Need to set -l (log location), -o (output location) and -i (initialisation file)'
  exit 1
else
  qsub -l h_rt=00:20:00 -N game_of_life -o "$log"_stdout -e "$log"_stderr -l tmem=1.8G -l h_vmem=1.8G -j y -S /bin/bash -b y -cwd -V ./game_of_life --init "$init_file" --out "$out_file" --frames 100
fi
