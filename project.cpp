#include "FourMomentum.h"
#include "Particle.h"
#include "ParticleCatalogue.h"

#include "leptons/Lepton.h"
#include "leptons/Electron.h"
#include "leptons/Muon.h"
#include "leptons/Tau.h"
#include "leptons/Neutrino.h"

#include "bosons/Boson.h"
#include "bosons/Photon.h"
#include "bosons/Gluon.h"
#include "bosons/Z.h"
#include "bosons/W.h"

#include <iostream>
#include <vector>
#include <algorithm>

void testing_catalogue()
{
  ParticleCatalogue<Particle> catalogue;

  Tau *tau = new Tau();
  Electron *electron = new Electron();
  Muon *muon = new Muon();
  Neutrino *neutrino = new Neutrino();

  Photon *photon = new Photon();
  Gluon *gluon = new Gluon();
  Z *z = new Z();
  W *w = new W();

  // Example of setting decay products
  std::vector<std::unique_ptr<Particle>> decay_products;
  auto tau_decay = std::make_unique<Tau>();
  decay_products.push_back(std::move(tau_decay));
  tau->set_decay_products(std::move(decay_products), DecayType::Leptonic);
  
  catalogue.add_particle(tau);
  catalogue.add_particle(electron);
  catalogue.add_particle(muon);
  catalogue.add_particle(neutrino);
  
  catalogue.add_particle(photon);
  catalogue.add_particle(gluon);
  catalogue.add_particle(z);
  catalogue.add_particle(w);

  std::cout << "Printing all particles:\n";
  catalogue.print_all();
  size_t totalParticles = catalogue.get_number_of_particles();
  std::map<std::string, int> particleCounts = catalogue.get_particle_count_by_type();
  FourMomentum totalFourMomentum = catalogue.sum_four_momenta();

  std::cout << "\nNumber of particles: " << totalParticles << std::endl
            << std::endl;
  for (const auto &pair : particleCounts)
  {
    std::cout << "Type: " << pair.first << ", Count: " << pair.second << std::endl;
  }
  std::cout << "\nFour momentum sum:" << totalFourMomentum << std::endl;

  std::vector<Lepton *> subContainer = catalogue.get_sub_container<Lepton>();

  std::cout << "\nPrinting all leptons only:\n";
  catalogue.print_info_by_type<Lepton>();
}

int main()
{
  //testing_catalogue();

  // Example of autoset decay particles, will only work with something that can decay to
  // two particles so far

  Z z = Z();

  std::vector<std::unique_ptr<Particle>> decay_products;
  auto e_decay = std::make_unique<Electron>();
  auto ae_decay = std::make_unique<Electron>(-1);

  decay_products.push_back(std::move(e_decay));
  decay_products.push_back(std::move(ae_decay));
  
  std::unique_ptr<FourMomentum> z_fm = std::make_unique<FourMomentum>(91200, 0, 0, 0, true);
  
  std::cout << *z_fm << std::endl;
  std::cout << z_fm->invariant_mass() << std::endl;

  z_fm ->lorentz_boost(0.01, 0.01, 0.01);
  std::cout << *z_fm << std::endl;
  std::cout << z_fm->invariant_mass() << std::endl;
  z_fm ->lorentz_boost(-0.01, -0.01, -0.01);
  std::cout << *z_fm << std::endl;
  std::cout << z_fm->invariant_mass() << std::endl;

  // z.set_four_momentum(std::make_unique<FourMomentum>(91200, 1, 2, 30, true));
  // z.set_four_momentum(std::move(z_fm));
  
  // z.auto_set_decay_products(std::move(decay_products), DecayType::Leptonic);
  //z.print();
  return 0;
}
