#!/bin/sh -f
#############

##################################
##################################
#     PLOTS
##################################
##################################

echo ${PWD}
plot_base_location='plotting/plotting_files/plots'
mkdir $plot_base_location
cd $plot_base_location 

##################################
## SET OPTIONS:
##################################

collision_sys="PbPb" 
Input_file_location="/home/abhishek/PhD/Work/work_A/photons/output/no_event_rep/ana_pTcut_withft3_check.root" 


if [[ "$collision_sys" = "pp" ]] #  pp = 0 || PbPb = 1; 
then
  sed -i "s|Int_t collisionSystem =.*|Int_t collisionSystem = 0;|g" ALICE3_setup.h
else 
  sed -i "s|Int_t collisionSystem =.*|Int_t collisionSystem = 1;|g" ALICE3_setup.h
fi

##################################
###   Mass Resolution
##################################

sed -i "s|fileRec = new TFile(.*|fileRec = new TFile(\""$Input_file_location"\");|g" massResol.C
root -l massResol.C
