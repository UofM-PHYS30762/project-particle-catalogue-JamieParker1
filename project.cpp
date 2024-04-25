#include "FourMomentum.h"
#include "Particle.h"
#include "leptons/Lepton.h"
#include "leptons/Electron.h"
#include "leptons/Muon.h"
#include "leptons/Tau.h"
#include "ParticleCatalogue.h"

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  Tau tau = Tau();
  std::vector<std::unique_ptr<Particle>> decay_products;
  auto tau_decay = std::make_unique<Tau>();
  decay_products.push_back(std::move(tau_decay));
  tau.set_decay_products(std::move(decay_products), DecayType::Leptonic);
  tau.print();

  Electron e = Electron();
  e.print();


  return 0;
}
