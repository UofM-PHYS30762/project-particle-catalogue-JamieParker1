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
  z.auto_set_decay_products(std::move(decay_products), DecayType::Leptonic);
  z.print();
}

int main()
{
  // ParticleCatalogue<Particle> showcase_catalogue;
  // ParticleCatalogue<Particle> user_catalogue;
  // main_menu_navigation(showcase_catalogue, user_catalogue);

  // showcase_basic_class_hierarchy();
  // showcase_four_momentum_class();
  // showcase_particle_attributes_and_functionality();
  //  Auto settinf decay products for Higgs, Z and W


  Tau tau;
  tau.set_four_momentum(std::make_unique<FourMomentum>(Mass::tau, 10, 4, 2, true));

  std::unique_ptr<Electron> electron_decay = std::make_unique<Electron>();
  std::unique_ptr<Neutrino> electron_neutrino = std::make_unique<Neutrino>("electron", -1);
  std::unique_ptr<Neutrino> tau_neutrino = std::make_unique<Neutrino>();
  std::vector<std::unique_ptr<Particle>> decay_products;
  decay_products.push_back(std::move(electron_decay));
  decay_products.push_back(std::move(electron_neutrino));
  decay_products.push_back(std::move(tau_neutrino));
  tau.auto_set_decay_products(std::move(decay_products), DecayType::Leptonic);
  tau.print();

  tau.set_four_momentum(std::make_unique<FourMomentum>(Mass::tau, 100, 4, 2, true));
  tau.print();

  

  // double m1 = 1.0;  // Rest mass of the first decay particle
  // double m2 = 4.0;  // Rest mass of the second decay particle
  // double m3 = 3.0;  // Rest mass of the third decay particle
  // double m_particle = 10.0;  // Rest mass of the decaying particle

  // std::vector<double> momenta = find_momentum_of_products_three_body(m1, m2, m3, m_particle);

  // // Access the momentum components
  // double p1x = momenta[0];
  // double p2x = momenta[1];
  // double p2y = momenta[2];
  // double p3x = momenta[3];
  // double p3y = momenta[4];

  // std::cout << "HERE" << std::endl;
  // std::cout << "p1x: " << p1x << std::endl;
  // std::cout << "p2x: " << p2x << std::endl;
  // std::cout << "p2y: " << p2y << std::endl;
  // std::cout << "p3x: " << p3x << std::endl;
  // std::cout << "p3y: " << p3y << std::endl;

  // std::cout << "p2x + p3x: " << p2x + p3x << std::endl;
  // std::cout << "p2y + p3y: " << p2y + p3y << std::endl;

  // double E1 = std::sqrt(m1 * m1 + p1x * p1x);
  // double E2 = std::sqrt(m2 * m2 + p2x * p2x + p2y * p2y);
  // double E3 = std::sqrt(m3 * m3 + p3x * p3x + p3y * p3y);

  // FourMomentum decaying(10, 5, 5, 5, true);
  // FourMomentum d1(E1, p1x, 0, 0);
  // FourMomentum d2(E2, p2x, p2y);
  // FourMomentum d3(E3, p3x, p3y, 0);
  // d1.lorentz_boost(decaying.get_velocity_vector(false));
  // d2.lorentz_boost(decaying.get_velocity_vector(false));
  // d3.lorentz_boost(decaying.get_velocity_vector(false));

  // std::cout << "1 " << d1 << std::endl;
  // std::cout << "2 " << d2 << std::endl;
  // std::cout << "3 " << d3 << std::endl;
  // std::cout << "P " << decaying << std::endl;

  // std::cout << "sum " << d1 + d2 + d3;

  


  return 0;
}