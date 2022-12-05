#!/bin/sh -f
#############


##################################
## SET OPTIONS: INITIAL
##################################
fcollision_sys="PbPb" 


##################################
###   Configuring:
##################################

plot_base_location="${PWD}/PLOTS1"
mkdir $plot_base_location
cd $plot_base_location 

cp -r ../plotting_files . # LOCAL COPY

echo ${PWD}

if [[ "$fcollision_sys" = "pp" ]] #  pp = 0 || PbPb = 1; 
then
  sed -i "s|Int_t collisionSystem =.*|Int_t collisionSystem = 0;|g" ./plotting_files/headers/ALICE3_setup.h
  Input_file_location="/home/abhishek/PhD/Work/work_A/photons/output/all_events/pp/ana_pTcut_withft3.root";
  Input_file_location_ALICE3="$plot_base_location/ALICE3_significance_input.root";

else 
  sed -i "s|Int_t collisionSystem =.*|Int_t collisionSystem = 1;|g" ./plotting_files/headers/ALICE3_setup.h
  Input_file_location="/home/abhishek/PhD/Work/work_A/photons/output/all_events/PbPb/ana_pTcut_withft3.root";
  #Input_file_location_ALICE3="/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/plotting/plotting_files/ALICE3_significance_input.root";
  Input_file_location_ALICE3="$plot_base_location/ALICE3_significance_input.root";

fi


###   Mass Resolution
##################################

sed -i "s|TString input_file_loc=.*|TString input_file_loc="\"$Input_file_location"\";|g" ./plotting_files/meson_MassResolution.C


###   Charged primary
##################################

sed -i "s|TString input_file_loc=.*|TString input_file_loc="\"$Input_file_location"\";|g" ./plotting_files/meson_Charged_primary.C


###    Acceptance
##################################

sed -i "s|TString input_file_loc=.*|TString input_file_loc="\"$Input_file_location"\";|g" ./plotting_files/meson_Acceptance.C


###    Efficiency
##################################

sed -i "s|TString input_file_loc=.*|TString input_file_loc="\"$Input_file_location"\";|g" ./plotting_files/meson_Effeciency.C


###    NET Efficiency
##################################

sed -i "s|TString input_file_loc=.*|TString input_file_loc="\"$Input_file_location"\";|g" ./plotting_files/meson_NetEfficiency.C



###    PYTHIA dN/dy
##################################

sed -i "s|TString input_file_loc=.*|TString input_file_loc="\"$Input_file_location"\";|g" ./plotting_files/meson_dNdyPythia.C


###    Opening Angle
##################################

sed -i "s|TString input_file_loc=.*|TString input_file_loc="\"$Input_file_location"\";|g" ./plotting_files/meson_openingangle.C




###    Signal pT bin FIT
##################################

sed -i "s|TString input_file_loc=.*|TString input_file_loc="\"$Input_file_location"\";|g" ./plotting_files/meson_ptbins_fit.C
if [[ "$fcollision_sys" = "pp" ]] #  pp = 0 || PbPb = 1; 
then
  sed -i "s|Int_t collisionSystem =.*|Int_t collisionSystem = 0;|g" ./plotting_files/meson_ptbins_fit.C
else 
  sed -i "s|Int_t collisionSystem =.*|Int_t collisionSystem = 1;|g" ./plotting_files/meson_ptbins_fit.C
fi

sed -i "s|TString fRap =.*;|TString fRap = \"F\";|g" ./plotting_files/meson_ptbins_fit.C
sed -i "s|fMesonId =.*;|fMesonId = 111;|g" ./plotting_files/meson_ptbins_fit.C
root -l -b -q ./plotting_files/meson_ptbins_fit.C

sed -i "s|TString fRap =.*;|TString fRap = \"F\";|g" ./plotting_files/meson_ptbins_fit.C
sed -i "s|fMesonId =.*;|fMesonId = 221;|g" ./plotting_files/meson_ptbins_fit.C
root -l -b -q ./plotting_files/meson_ptbins_fit.C

sed -i "s|TString fRap =.*;|TString fRap = \"B\";|g" ./plotting_files/meson_ptbins_fit.C
sed -i "s|fMesonId =.*;|fMesonId = 111;|g" ./plotting_files/meson_ptbins_fit.C
root -l -b -q ./plotting_files/meson_ptbins_fit.C

sed -i "s|TString fRap =.*;|TString fRap = \"B\";|g" ./plotting_files/meson_ptbins_fit.C
sed -i "s|fMesonId =.*;|fMesonId = 221;|g" ./plotting_files/meson_ptbins_fit.C
root -l -b -q ./plotting_files/meson_ptbins_fit.C



###    Signal pT bin ratio and Background per event
####################################################

sed -i "s|TString input_file_loc=.*|TString input_file_loc="\"$Input_file_location"\";|g" ./plotting_files/meson_invmass_fit.C
if [[ "$fcollision_sys" = "pp" ]] #  pp = 0 || PbPb = 1; 
then
  sed -i "s|Int_t collisionSystem =.*|Int_t collisionSystem = 0;|g" ./plotting_files/meson_invmass_fit.C
else 
  sed -i "s|Int_t collisionSystem =.*|Int_t collisionSystem = 1;|g" ./plotting_files/meson_invmass_fit.C
fi

sed -i "s|TString fRap =.*;|TString fRap = \"F\";|g" ./plotting_files/meson_invmass_fit.C
sed -i "s|fMesonId =.*;|fMesonId = 111;|g" ./plotting_files/meson_invmass_fit.C
root -l -b -q ./plotting_files/meson_invmass_fit.C

sed -i "s|TString fRap =.*;|TString fRap = \"F\";|g" ./plotting_files/meson_invmass_fit.C
sed -i "s|fMesonId =.*;|fMesonId = 221;|g" ./plotting_files/meson_invmass_fit.C
root -l -b -q ./plotting_files/meson_invmass_fit.C

sed -i "s|TString fRap =.*;|TString fRap = \"B\";|g" ./plotting_files/meson_invmass_fit.C
sed -i "s|fMesonId =.*;|fMesonId = 111;|g" ./plotting_files/meson_invmass_fit.C
root -l -b -q ./plotting_files/meson_invmass_fit.C

sed -i "s|TString fRap =.*;|TString fRap = \"B\";|g" ./plotting_files/meson_invmass_fit.C
sed -i "s|fMesonId =.*;|fMesonId = 221;|g" ./plotting_files/meson_invmass_fit.C
root -l -b -q ./plotting_files/meson_invmass_fit.C


###    Signal & background
##################################

sed -i "s|TString input_file_loc=.*|TString input_file_loc="\"$Input_file_location_ALICE3"\";|g" ./plotting_files/meson_signal_AND_background.C



###    Signal VS background
##################################

sed -i "s|TString input_file_loc=.*|TString input_file_loc="\"$Input_file_location"\";|g" ./plotting_files/meson_signalVSbackground.C




###    Significance
##################################

sed -i "s|TString input_file_loc=.*|TString input_file_loc="\"$Input_file_location_ALICE3"\";|g" ./plotting_files/meson_significance.C



##################################
###   RUN: (LOCALLY)
##################################
root -l -b -q ./plotting_files/meson_MassResolution.C
root -l -b -q ./plotting_files/meson_Acceptance.C
root -l -b -q ./plotting_files/meson_NetEfficiency.C
root -l -b -q ./plotting_files/meson_Effeciency.C
root -l -b -q ./plotting_files/meson_dNdyPythia.C 
root -l -b -q ./plotting_files/meson_openingangle.C

rm ALICE3_significance_input.root
hadd ALICE3_significance_input.root /meson_Acceptance/ALICE3_significance_input.root ./meson_dNdyPythia/ALICE3_significance_input.root ./meson_invmass_fit/ALICE3_significance_input.root ./meson_NetEffeciency/ALICE3_significance_input.root

root -l -b -q ./plotting_files/meson_signal_AND_background.C
root -l -b -q ./plotting_files/meson_signalVSbackground.C 
root -l -b -q ./plotting_files/meson_significance.C
root -l -b -q ./plotting_files/meson_Charged_primary.C
##################################
###  Compile plots in PPTX
##################################

#cp -r ~/PhD/Work/work_A/photons/auto_ppt .
#cd auto_ppt
#python3 ./analyze_ppt.py 
