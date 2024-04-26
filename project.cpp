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
#include "bosons/Higgs.h"

#include "quarks/Quark.h"
#include "quarks/Up.h"
#include "quarks/Down.h"
#include "quarks/Bottom.h"
#include "quarks/Charm.h"
#include "quarks/Top.h"
#include "quarks/Strange.h"

#include <iostream>
#include <vector>
#include <algorithm>

void testing_catalogue()
{
  ParticleCatalogue<Particle> catalogue;

  Tau *tau = new Tau();
  Electron *electron = new Electron();
  Muon *muon = new Muon();
  Neutrino *tau_neutrino = new Neutrino("tau");
  Neutrino *electron_neutrino = new Neutrino("electron");
  Neutrino *muon_neutrino = new Neutrino("muon");
  Tau *anti_tau = new Tau(-1);
  Electron *anti_electron = new Electron(-1);
  Muon *anti_muon = new Muon(-1);
  Neutrino *anti_tau_neutrino = new Neutrino("tau", -1);
  Neutrino *anti_electron_neutrino = new Neutrino("electron", -1);
  Neutrino *anti_muon_neutrino = new Neutrino("muon", -1);

  Photon *photon = new Photon();
  Gluon *gluon = new Gluon();
  Z *z = new Z();
  W *w_plus = new W();
  W *w_minus = new W(-1);
  Higgs *higgs = new Higgs();

  Up *up = new Up();
  Down *down = new Down();
  Bottom *bottom = new Bottom();
  Charm *charm = new Charm();
  Top *top = new Top();
  Strange *strange = new Strange();
  Up *anti_up = new Up(true);
  Down *anti_down = new Down(true);
  Bottom *anti_bottom = new Bottom(true);
  Charm *anti_charm = new Charm(true);
  Top *anti_top = new Top(true);
  Strange *anti_strange = new Strange(true);

  // Example of setting decay products
  std::vector<std::unique_ptr<Particle>> decay_products;
  auto e_decay = std::make_unique<Electron>();
  auto ae_decay = std::make_unique<Electron>(-1);
  decay_products.push_back(std::move(e_decay));
  decay_products.push_back(std::move(ae_decay));
  z->auto_set_decay_products(std::move(decay_products), DecayType::Leptonic);
  
  catalogue.add_particle(tau);
  catalogue.add_particle(electron);
  catalogue.add_particle(muon);
  catalogue.add_particle(tau_neutrino);
  catalogue.add_particle(electron_neutrino);
  catalogue.add_particle(muon_neutrino);
  catalogue.add_particle(anti_tau);
  catalogue.add_particle(anti_electron);
  catalogue.add_particle(anti_muon);
  catalogue.add_particle(anti_tau_neutrino);
  catalogue.add_particle(anti_electron_neutrino);
  catalogue.add_particle(anti_muon_neutrino);
  
  catalogue.add_particle(photon);
  catalogue.add_particle(gluon);
  catalogue.add_particle(z);
  catalogue.add_particle(w_plus);
  catalogue.add_particle(w_minus);
  catalogue.add_particle(higgs);

  catalogue.add_particle(up);
  catalogue.add_particle(down);
  catalogue.add_particle(bottom);
  catalogue.add_particle(top);
  catalogue.add_particle(charm);
  catalogue.add_particle(strange);
  catalogue.add_particle(anti_up);
  catalogue.add_particle(anti_down);
  catalogue.add_particle(anti_bottom);
  catalogue.add_particle(anti_top);
  catalogue.add_particle(anti_charm);
  catalogue.add_particle(anti_strange);

  std::cout << "Printing all leptons:\n";
  catalogue.print_info_by_type<Lepton>();

  std::cout << "\nPrinting all bosons:\n";
  catalogue.print_info_by_type<Boson>();

  std::cout << "\nPrinting all quarks:\n";
  catalogue.print_info_by_type<Quark>();

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
}

void auto_decay_product_example()
{
  // Example of autoset decay particles, will only work with something that can decay to
  // two particles so far
  Z z = Z();
  std::vector<std::unique_ptr<Particle>> decay_products;
  auto e_decay = std::make_unique<Electron>();
  auto ae_decay = std::make_unique<Electron>(-1);

  decay_products.push_back(std::move(e_decay));
  decay_products.push_back(std::move(ae_decay));
  
  std::unique_ptr<FourMomentum> z_fm = std::make_unique<FourMomentum>(91200, 10, 10, 10, true);
  z.set_four_momentum(std::move(z_fm));
  z.auto_set_decay_products(std::move(decay_products), DecayType::Leptonic);
  z.print();
}

int main()
{
  testing_catalogue(); 
  return 0;
}
