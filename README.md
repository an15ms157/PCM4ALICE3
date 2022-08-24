# PCM4ALICE3
Analysis code for light mesons from soft photon in ALICE3 detector simulation.
To start the simulation, do the followings: 
1. Get into AliceO2 (alienv enter O2/latest-dev-o2)
2. root -l ./analysis_files/ana.C

For plotting, use: 
root -l ./plots/histogramplots.C

## Installation of ALICEO2 in PI server
    Please follow the following steps: (assuming you are outside PI)

* ssh -X username@alice-head.physi.uni-heidelberg.de  
* ssh -X username@alice-serv13 or ssh -X name@alice-serv11

* Please store your O2 version in /misc/alidata110/alice_u/username (This part of the server is not backed up and is meant to store heavy softwares. Create the folder username if there is not one)

* Follow :https://alice-doc.github.io/alice-analysis-tutorial/building/ to build O2 (In PI server, probably already the prerequisites are present so one can skip it. You might need to create the sw folder in /misc/alidata110/alice_u/username/alice/ after running ‘AliBuild init @&#%%’ )

* Add the following files in ~/.bashrc to get the: 
  export ALIBUILD_WORK_DIR="/misc/alidata110/alice_u/username/alice/sw"
  eval "`alienv shell-helper`"

### For visualisation purpose, change the following options in alidist/geant4.sh file:      
  -DGEANT4_USE_QT=ON                                    -DGEANT4_USE_OPENGL=ON

* If you are trying to install the ALICE3 detectors in your O2,  use the command: ENABLE_UPGRADES=ON aliBuild build O2 --defaults o2 

* Before you build it, type screen (this makes sure that the installation goes on even if you get logged out)

* Once you have installation running, Run ‘source ~/.bashrc’  (this loads your local O2)

If the build is successful, you can use your O2.                         Run the command ‘alienv enter O2/latest-dev-o2’ . Please note that you always need to source your ~/.bashrc file before each session to run your local version. 

Right now, there is an error related to CMake.  But hopefully, this does not cause any problem with the simulation. (https://alice-talk.web.cern.ch/t/cmake-module-for-ubuntu/912).  


