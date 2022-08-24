 
universe        = vanilla
Getenv          = true
executable      = jobscript_sim

Requirements = (TARGET.Machine == "alice-serv14")
Requirements = (TARGET.Machine == "alice-serv10" ||TARGET.Machine == "alice-serv11" || TARGET.Machine == "alice-serv12" || TARGET.Machine == "alice-serv13")
#requirements = (Machine == "alice-serv10" || Machine == "alice-serv11" || Machine == "alice-serv12" || Machine == "alice-serv13" || Machine == "alice-serv14")

output          = /misc/alidata120/alice_u/nath/electron-pack/pTcut/anaConV3/pythia_testing/condor_logsPbPb220623/jobscript_sim22.out
error           = /misc/alidata120/alice_u/nath/electron-pack/pTcut/anaConV3/pythia_testing/condor_logsPbPb220623/jobscript_sim22.err
log             = /misc/alidata120/alice_u/nath/electron-pack/pTcut/anaConV3/pythia_testing/condor_logsPbPb220623/jobscript_sim22.log
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
transfer_input_files = run_simulation.sh, RecoDecay.h, trigger_multiplicity.C, run_analysis_example.C, runtracking.C
#Requirements    = (Machine != "alice-serv14.physi.uni-heidelberg.de")

#requirements    =!stringListMember(Utsname Nodename, “alice-serv14")

queue
