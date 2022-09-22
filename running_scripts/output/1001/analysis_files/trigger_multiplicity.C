// multiplicity trigger
//
//   usage: o2sim --trigger external --configKeyValues 'TriggerExternal.fileName=trigger_multiplicity.C;TriggerExternal.funcName="trigger_multiplicity(-0.8, 0.8, 100)"'
//

/// \author R+Preghenella - February 2020

#include "Generators/Trigger.h"
#include "TParticle.h"
#include "TParticlePDG.h"

o2::eventgen::Trigger
  trigger_multiplicity(double etaMin = -0.8, double etaMax = 0.8, int pdg = 100)
{
  auto trigger = [etaMin, etaMax, pdg](const std::vector<TParticle>& particles) -> bool {
    bool fired = false;
    for (const auto& particle : particles) {
      if (particle.Eta() < etaMin || particle.Eta() > etaMax)
        continue;
      if( particle.GetPDG() )
        if (particle.GetPDG()->PdgCode() == pdg )
          fired = true;
    }
    return fired;
  };

  return trigger;
}

