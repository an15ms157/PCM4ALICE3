#! /usr/bin/env bash

# NOTE0: Run in 'alienv enter O2/latest-dev-o2'
# NOTE1: Actual rapidity histogram has -5<y<5 and 0<pT<10 GeV range
# Note2: All bin width are 0.001 units

EFFICIENCY_FILE='mesonEff.C'
ETA_F_LOW1=1.75
ETA_F_LOW2=3.0
ETA_F_HIGH1=3.0
ETA_F_HIGH2=4.0

ETA_B_LOW1=0.0
ETA_B_LOW2=0.8
ETA_B_HIGH1=0.8
ETA_B_HIGH2=1.3

echo "Starting Plotting" >> plotlog.txt
echo "running $EFFICIENCY_FILE" >> plotlog.tx

#Changing sub-ranges in rapidity at Forward
sed -i -e "s/Double_t etaF_low1 =.*;/Double_t etaF_low1 = $ETA_F_LOW1;/" mesonEff.C
sed -i -e "s/Double_t etaF_low2 =.*;/Double_t etaF_low2 = $ETA_F_LOW2;/" mesonEff.C
sed -i -e "s/Double_t etaF_high1 =.*;/Double_t etaF_high1 = $ETA_F_HIGH1;/" mesonEff.C
sed -i -e "s/Double_t etaF_high2 =.*;/Double_t etaF_high2 = $ETA_F_HIGH2;/" mesonEff.C

#Changing sub-ranges in rapidity at Barrel
sed -i -e "s/Double_t etaB_low1 =.*;/Double_t etaB_low1 = $ETA_B_LOW1;/" mesonEff.C
sed -i -e "s/Double_t etaB_low2 =.*;/Double_t etaB_low2 = $ETA_B_LOW2;/" mesonEff.C
sed -i -e "s/Double_t etaB_high1 =.*;/Double_t etaB_high1 = $ETA_B_HIGH1;/" mesonEff.C
sed -i -e "s/Double_t etaB_high2 =.*;/Double_t etaB_high2 = $ETA_B_HIGH2;/" mesonEff.C

root -l mesonEff.C