#!/bin/sh -f
#############

echo ${PWD}
INPUT_FILES_FIRST=$1
INPUT_FILE_LAST=$2
N_INPUT_FILES=$(eval echo "{$INPUT_FILES_FIRST..$INPUT_FILE_LAST}")
for i in ${N_INPUT_FILES[@]}
do
  echo $i
  #eve_FILE='mcTree.AddFile("/misc/alidata130/alice_u/nath/new_Pythia_output/resultsPbPb221031/eve'$i'/o2sim_Kine.root");'  
  eve_FILE='mcTree.AddFile("/misc/alidata130/alice_u/nath/new_Pythia_output/resultsPP220930/eve'$i'/o2sim_Kine.root");'  
  sed -i -e "/TChain mcTree.*/a $eve_FILE" ./ana.C

done          

screen -S "eve$INPUT_FILES_FIRST-$INPUT_FILE_LAST" -d -m
screen -r "eve$INPUT_FILES_FIRST-$INPUT_FILE_LAST" -X stuff "bash trigger_ana_C.sh && exit^M"
#screen -r "eve$i" -X stuff $'root -l ana.C \n'         


