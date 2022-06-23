#! /usr/bin/env bash

PPorPbPb="pp"
EVENTDIVISION=(1 50 100 150 200 250 300 350 400 450 500 550 600 650 700 750 800 850 900+1) #NOTE THE STRUCTURE OF THE ARRAY
LOC_mainfile="./ana.C"
LOC_progressbar="./progressbar.h"


#GET INTO O2 or DELPHES BEFORE EXECUTING THE SCRIPT : alienv enter DelphesO2/latest-o2

for ((t=0; t<${#EVENTDIVISION[@]}-1; t++)); do
  mkdir -p "./ana_RecOut_${PPorPbPb}_eve${EVENTDIVISION[t]}TO$((${EVENTDIVISION[t+1]}-1))"
  cp -f $LOC_mainfile ./ana_RecOut_${PPorPbPb}_eve${EVENTDIVISION[t]}TO$((${EVENTDIVISION[t+1]}-1))
  cp -f $LOC_progressbar ./ana_RecOut_${PPorPbPb}_eve${EVENTDIVISION[t]}TO$((${EVENTDIVISION[t+1]}-1))
  cd ./ana_RecOut_${PPorPbPb}_eve${EVENTDIVISION[t]}TO$((${EVENTDIVISION[t+1]}-1))
  #echo $(pwd)
  #sed -i -e "s/set barrel_Radius .*$/set barrel_Radius ${BARRELRAD}e\-2/" propagate.tcl
  
  screen -dmS eve${EVENTDIVISION[t]}TO$((${EVENTDIVISION[t+1]}-1)) 

  for ((j=${EVENTDIVISION[t]}; j<${EVENTDIVISION[t+1]}; j++)); do
    #echo $j, $t

    case $PPorPbPb in
      "pp")
      eve_FILE='mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve'$j'/o2sim_Kine.root");'
      ;;

      "PbPb")
      eve_FILE='mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve'$j'/o2sim_Kine.root");'
      ;;
    esac
    sed -i -e "/TChain mcTree.*/a $eve_FILE" ./ana.C
    echo $eve_FILE, $j, $t
    screen -S eve${EVENTDIVISION[t]}TO$((${EVENTDIVISION[t+1]}-1)) -p 0 -X ~/.bashrc
    done 
  cd ../

done

