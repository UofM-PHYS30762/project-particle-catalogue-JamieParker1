#include "FourMomentum.h"
#include "Particle.h"
#include "ParticleCatalogue.h"

#include "showcase.h"
#include "user_interface.h"

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
#include "quarks/QuarkTemplate.h"
#include "quarks/IndividualQuarks.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>

void testing_catalogue()
{
  ParticleCatalogue<Particle> catalogue;
  fill_catalogue(catalogue);

  size_t totalParticles = catalogue.get_number_of_particles();
  std::map<std::string, int> particle_counts = catalogue.get_particle_count_by_type();
  FourMomentum total_four_momentum = catalogue.sum_four_momenta();

  std::cout << "\nNumber of particles: " << totalParticles << std::endl
            << std::endl;
  for (const auto &pair : particle_counts)
  {
    std::cout << "Type: " << pair.first << ", Count: " << pair.second << std::endl;
  }

  std::cout << "Printing all leptons:\n";
  catalogue.print_info_by_type<Lepton>();

  std::cout << "\nPrinting all bosons:\n";
  catalogue.print_info_by_type<Boson>();

  std::cout << "\nPrinting all quarks:\n";
  catalogue.print_info_by_type<Quark>();

  std::cout << "\nFour momentum sum:" << total_four_momentum << std::endl;
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
  z.auto_set_decay_products(std::move(decay_products), DecayType::Weak);
  z.print();
}

int main()
{
  // ParticleCatalogue<Particle> catalogue;
  // Photon *p = new Photon();
  // Higgs *h = new Higgs();
  // Electron *e = new Electron();
  // e->set_label("HERE");
  // h->set_label("HERE");
  // catalogue.add_particle(p);
  // catalogue.add_particle(h);
  // catalogue.add_particle(e);

  // std::vector<Particle*> heres = catalogue.find_particles_by_label("HERE");
  // heres[0]->print();
  // size_t remove_index = 0;
  // catalogue.remove_particle(remove_index);
  // std::cout << "___________________________" << std::endl;
  // catalogue.print_all();
  // catalogue.remove_particle(e);
  // std::cout << "___________________________" << std::endl;
  // catalogue.print_all();
  // std::cout << "___________________________" << std::endl;
  // catalogue.remove_particle("HERE");
  // catalogue.print_all();

  // catalogue.apply_function_to_particles<void (Particle::*)(const std::string&), const char*>(&Particle::set_label, "random label", std::vector<std::string>{"HERE"});
  // //catalogue.apply_function_to_particles(&Particle::set_label, "random label", std::vector<std::string>{"HERE"});

  // catalogue.apply_function_to_particles<Lepton>(&Lepton::set_label, "1");
  // catalogue.print_all();

  Tau tau;
  std::vector<std::unique_ptr<Particle>> dp;
  // std::unique_ptr<Neutrino> tau_neutrino = std::make_unique<Neutrino>("tau");
  // std::unique_ptr<Muon> electron = std::make_unique<Muon>();
  // std::unique_ptr<Neutrino> anti_electron_neutrino = std::make_unique<Neutrino>("muon", -1);
  // dp.push_back(std::move(tau_neutrino));
  // dp.push_back(std::move(electron));
  // dp.push_back(std::move(anti_electron_neutrino));
  // tau.auto_set_decay_products(std::move(dp), DecayType::Leptonic);
  // tau.print();
  std::unique_ptr<Neutrino> tau_neutrino = std::make_unique<Neutrino>("tau");
  std::unique_ptr<Up> anti_up = std::make_unique<Up>(true);
  std::unique_ptr<Down> down = std::make_unique<Down>();
  down->print();
  std::cout << anti_up->get_charge() << down->get_charge();
  dp.push_back(std::move(tau_neutrino));
  dp.push_back(std::move(anti_up));
  dp.push_back(std::move(down));
  
  tau.auto_set_decay_products(std::move(dp), DecayType::Weak);






  // wait_for_enter("Hit Enter to continue to Class Hierachy Showcase:");
  // showcase_basic_class_hierarchy();
  // wait_for_enter();
  // showcase_four_momentum_class();
  // wait_for_enter();
  // showcase_particle_attributes();
  // wait_for_enter();
  // showcase_decay_product_functionality();
  // showcase_particle_catalogue();

  return 0;
}
