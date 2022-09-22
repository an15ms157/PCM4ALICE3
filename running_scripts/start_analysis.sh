#!/bin/sh -f
#############

echo ${PWD}
mkdir output
cd output
INPUT_FILES_FIRST=1001
INPUT_FILE_LAST=1002 
N_INPUT_FILES=$(eval echo "{$INPUT_FILES_FIRST..$INPUT_FILE_LAST}")
for i in ${N_INPUT_FILES[@]}
do 
  mkdir $i
  cd $i
  cp -r ../../../analysis_files .
  cd analysis_files

  cp -r ../../../trigger_ana_C.sh .

  eve_FILE='mcTree.AddFile("/misc/alidata130/alice_u/nath/new_Pythia_output/resultsPbPb220623/eve'$i'/o2sim_Kine.root");'
  sed -i -e "/TChain mcTree.*/a $eve_FILE" ./ana.C
  screen -S "eve$i" -d -m "trigger_ana_C.sh"
  #screen -r "eve$i" -X stuff $'alienv enter DelphesO2/latest \n'
  #screen -r "eve$i" -X stuff $'root -l ana.C \n'

  cd ../../

done