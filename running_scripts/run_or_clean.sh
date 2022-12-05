#!/bin/sh -f
############
RUN_OR_CLEAN=$1
INPUT_FILE_BATCH_SIZE=10
INPUT_FILES_START=2100
INPUT_FILE_END=$((2199+1))

mkdir output_bacthof_$INPUT_FILE_BATCH_SIZE
cd output_bacthof_$INPUT_FILE_BATCH_SIZE

case $RUN_OR_CLEAN in
    "run")

    N_INPUT_FILES=($(eval echo "{$INPUT_FILES_START..$INPUT_FILE_END..$INPUT_FILE_BATCH_SIZE}"))
    unset N_INPUT_FILES[-1]
    for i in ${N_INPUT_FILES[@]}
    do
        mkdir $i
        echo $i
        cd $i
        cp -r ../../../analysis_files .
        cd analysis_files
        cp -r ../../../start_analysis.sh .
        cp -r ../../../trigger_ana_C.sh .

        bash start_analysis.sh $i $(($i+$INPUT_FILE_BATCH_SIZE-1))
        cd ../../

    done
    ;;

    "clean")
    hadd ana_pTcut_withft3.root */*/ana_pTcut_withft3_check.root
    ;;
esac

