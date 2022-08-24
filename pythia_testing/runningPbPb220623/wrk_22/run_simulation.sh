#!/bin/bash
#
# This macro runs all steps in a strangeness tracking effort
#
# Step 1: create simulation via o2-sim
#
# Basic configurations
NEVENTS=10
#NEVENTS=10000
NCPUS=1

DIR=`pwd`

# options to pass to every workflow
gloOpt=" -b --run --shm-segment-size 10000000000"

echo "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
#o2-sim-serial -j ${NCPUS} --field 5 -e TGeant3 -n ${NEVENTS} -g pythia8pp -m TRK FT3 A3IP -o o2sim --trigger external --configKeyValues 'TriggerExternal.fileName=trigger_multiplicity.C;TriggerExternal.funcName=trigger_multiplicity(-1.5,1.5, 11)'
o2-sim-serial -j ${NCPUS} --field 5 -e TGeant3 -n ${NEVENTS} -g pythia8hi -m TRK FT3 A3IP -o o2sim --trigger external --configKeyValues 'GeneratorPythia8.config=/misc/alidata120/alice_u/nath/electron-pack/pTcut/anaConV3/pythia_testing/pythia8_hi.cfg;TriggerExternal.fileName=trigger_multiplicity.C;TriggerExternal.funcName=trigger_multiplicity(-1.5,1.5, 11)'
echo "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
