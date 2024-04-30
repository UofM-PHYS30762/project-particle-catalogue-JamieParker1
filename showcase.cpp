#include "FourMomentum.h"
#include "Particle.h"
#include "ParticleCatalogue.h"
#include "helper_functions.h"

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

void showcase_basic_class_hierarchy()
{
  Particle *general_particle = new Particle();
  Lepton *general_lepton = new Lepton();
  Quark *general_quark = new Quark();
  Boson *general_boson = new Boson();

  ParticleCatalogue<Particle> hierarchy_catalogue;
  hierarchy_catalogue.add_particle(general_particle);
  hierarchy_catalogue.add_particle(general_lepton);
  hierarchy_catalogue.add_particle(general_boson);
  hierarchy_catalogue.add_particle(general_quark);

  clear_screen();
  std::cout << "==== Class Hierarchy Showcase ====\n";
  print_loading_string("Now outputting different class attributes for particle base classes", 1, true);
  print_loading_string("General Particle Attributes:", 1);
  hierarchy_catalogue.print_info_by_exact_type<Particle>();

  print_loading_string("\nGeneral Lepton Attributes:", 1);
  hierarchy_catalogue.print_info_by_exact_type<Lepton>();

  print_loading_string("\nGeneral Quark Attributes:", 1);
  hierarchy_catalogue.print_info_by_exact_type<Quark>();

  print_loading_string("\nGeneral Boson Attributes:", 1);
  hierarchy_catalogue.print_info_by_exact_type<Boson>();
}

void showcase_particle_attributes_and_functionality()
{
  clear_screen();
  std::cout << "==== Particle Attribute Showcase ====\n";
  print_loading_string("\nSpecific particles have extra attributes", 1, true, false);

  // Creating Electron object
  print_loading_string("Creating Electron object", 1, true);
  Electron electron;
  std::unique_ptr<FourMomentum> electron_fm = std::make_unique<FourMomentum>(0.511, 0.2, 0.3, 0.4, true);
  electron.set_four_momentum(std::move(electron_fm));
  electron.set_label("Electron 1");
  electron.print();

  print_loading_string("\nNow attempting to change energy deposits:", 1, true);
  std::vector<double> electron_energy_deposit = {2.5, 3.7, 1.2, 0.8};
  std::cout << "New Energy Deposits: " << electron_energy_deposit[0] << ", "<< electron_energy_deposit[1] << ", "<< electron_energy_deposit[2] << ", "<< electron_energy_deposit[3] << std::endl;
  try
  {
    electron.set_energy_deposited_in_layers(electron_energy_deposit);
  }
  catch(const std::invalid_argument& e)
  {
    std::cerr << "\nException caught -" << e.what() << std::endl;
  }
  print_loading_string("\nElectron energy deposits remains unchanged", 1, true, false);
  std::cout << electron.get_energy_deposited_in_layers()[0] << ", " << electron.get_energy_deposited_in_layers()[1] << ", " << electron.get_energy_deposited_in_layers()[2] << ", " << electron.get_energy_deposited_in_layers()[3] << std::endl;

  // Creating Muon object
  print_loading_string("\nCreating Muon object", 1, true);
  std::unique_ptr<FourMomentum> muon_fm = std::make_unique<FourMomentum>(105.7, 1.2, 2.3, 3.4, true);
  Muon muon("Muon1", std::move(muon_fm), true, 1);
  muon.print();

  // Accessing Muon's isolation status
  print_loading_string("\nAccessing Muon's isolation status", 1, true);
  bool is_isolated = muon.get_is_isolated();
  std::cout << "Is Muon isolated? " << (is_isolated ? "Yes" : "No") << std::endl;

  // Creating Neutrino object
  print_loading_string("\nCreating Neutrino object:", 1, true);
  std::unique_ptr<FourMomentum> neutrino_fm = std::make_unique<FourMomentum>(1.1e-6, 0.5, 0.6, 0.7, true);
  Neutrino neutrino("Neutrino1", std::move(neutrino_fm), "electron", true, 1);
  neutrino.print();

  // Accessing Neutrino's interaction status
  print_loading_string("\nAccessing Neutrino's interaction status:", 1, true);
  bool has_interacted = neutrino.get_has_interacted();
  std::cout << "Has Neutrino interacted? " << (has_interacted ? "Yes" : "No") << std::endl;

  // Creating Tau object
  print_loading_string("\nCreating Tau object with no decay products", 1, true);
  std::unique_ptr<FourMomentum> tau_fm = std::make_unique<FourMomentum>(1777, 0, 0, 0, true);
  Tau tau;
  tau.set_label("Tau1");
  tau.set_four_momentum(std::move(tau_fm));
  tau.print();

  // Setting Tau's decay products
  print_loading_string("\nSetting Tau's decay products manually", 1, true);
  // std::unique_ptr<FourMomentum> electron_decay_fm = std::make_unique<FourMomentum>(Mass::electron, 0, 0, 0, true);
  // std::unique_ptr<FourMomentum> electron_neutrino_decay_fm = std::make_unique<FourMomentum>(1.1e-6, 0, 0, 0, true);
  // std::unique_ptr<FourMomentum> tau_neutrino_decay_fm = std::make_unique<FourMomentum>(1.1e-6, 0, 0, 0, true);
  // std::unique_ptr<Particle> electron_decay = std::make_unique<Electron>("Electron decay", std::move(electron_decay_fm), std::vector<double>{1.0, 2.0, 3.0, 4.0});
  // std::unique_ptr<Particle> electron_neutrino_decay = std::make_unique<Neutrino>("Electron neutrino decay", std::move(electron_neutrino_decay_fm), "electron", false, -1);
  // std::unique_ptr<Particle> tau_neutrino_decay = std::make_unique<Neutrino>("Tau neutrino decay", std::move(tau_neutrino_decay_fm), "tau", false, -1);

  // std::vector<std::unique_ptr<Particle>> tau_decay_products;
  // tau_decay_products.push_back(std::move(electron_decay));
  // tau_decay_products.push_back(std::move(electron_neutrino_decay));
  // tau_decay_products.push_back(std::move(tau_neutrino_decay));
  // tau.set_decay_products(std::move(tau_decay_products), DecayType::Leptonic);
  // tau.print();

  // Auto settinf decay products for Higgs, Z and W
  print_loading_string("\nCreating Higgs boson", 1, true);
  Higgs higgs;
  higgs.print();

  print_loading_string("\nAuto Setting Higgs decay products to two Z bosons", 1, true);
  std::unique_ptr<Z> z1_decay = std::make_unique<Z>();
  std::unique_ptr<Z> z2_decay = std::make_unique<Z>();
  std::vector<std::unique_ptr<Particle>> higgs_decay_products;
  higgs_decay_products.push_back(std::move(z1_decay));
  higgs_decay_products.push_back(std::move(z2_decay));
  higgs.auto_set_decay_products(std::move(higgs_decay_products), DecayType::Bosonic);

  print_loading_string("\nHiggs boson doesn't have enough rest energy to decay to two real Z bosons", 1, true);
  std::unique_ptr<Z> z1_decay_2 = std::make_unique<Z>();
  std::unique_ptr<Z> z2_decay_2 = std::make_unique<Z>();
  z1_decay_2->set_is_virtual(true);
  z2_decay_2->set_is_virtual(true);
  std::vector<std::unique_ptr<Particle>> higgs_decay_products_2;
  higgs_decay_products_2.push_back(std::move(z1_decay_2));
  higgs_decay_products_2.push_back(std::move(z2_decay_2));
  higgs.auto_set_decay_products(std::move(higgs_decay_products_2), DecayType::Bosonic);
  higgs.print();


}


void showcase_four_momentum_class()
{
  clear_screen();
  std::cout << "==== FourMomentum Class Showcase ====\n";

  // Creating FourMomentum objects
  print_loading_string("Creating FourMomentum objects:", 1, true);
  FourMomentum fm1(10.0, 2.0, 3.0, 4.0);
  FourMomentum fm2(5.0, 1.0, 2.0, 3.0);
  std::cout << "FourMomentum 1: " << fm1 << std::endl;
  std::cout << "FourMomentum 2: " << fm2 << std::endl;

  // Accessing individual components
  print_loading_string("\nAccessing individual components:", 1, true);
  std::cout << "Energy of FourMomentum 1: " << fm1.get_energy() << std::endl;
  std::cout << "Px of FourMomentum 2: " << fm2.get_Px() << std::endl;

  // Performing arithmetic operations
  print_loading_string("\nPerforming arithmetic operations:", 1, true);
  FourMomentum fm_sum = fm1 + fm2;
  FourMomentum fm_diff = fm1 - fm2;
  double dot_product = fm1 * fm2;
  std::cout << "Sum of FourMomentum 1 and 2: " << fm_sum << std::endl;
  std::cout << "Difference of FourMomentum 1 and 2: " << fm_diff << std::endl;
  std::cout << "Dot product of FourMomentum 1 and 2: " << dot_product << std::endl;

  // Creating FourMomentum objects from rest-mass
  print_loading_string("\nCreating Four Momentum Objects for a particle of rest mass 10(MeV) with a momentum of 2(MeV):", 1, true);
  FourMomentum particle_fm(10, 2, 0, 0, true);
  std::cout << "Particle's FourMomentum: " << particle_fm << std::endl;

  // Calculating invariant mass
  print_loading_string("\nCalculating invariant mass from this FourMomentum:", 1, true);
  double mass = particle_fm.invariant_mass();
  std::cout << "Invariant mass of Particle's FourMomentum: " << mass << std::endl;

  // Calculating velocity components
  print_loading_string("\nCalculating velocity components:", 1);
  std::cout << "Velocity magnitude of Particle's FourMomentum: " << particle_fm.get_velocity_magnitude() << std::endl;
  std::cout << "Velocity x-component of Particle's FourMomentum: " << particle_fm.get_velocity_x() << std::endl;
  std::cout << "Velocity y-component of Particle's FourMomentum: " << particle_fm.get_velocity_y() << std::endl;
  std::cout << "Velocity z-component of Particle's FourMomentum: " << particle_fm.get_velocity_z() << std::endl;

  // Performing Lorentz boost
  print_loading_string("\nPerforming Lorentz boost to Particles rest frame using these velocity values:", 1, true);
  particle_fm.lorentz_boost(particle_fm.get_velocity_vector());
  std::cout << "Particle's FourMomentum after Lorentz boost: " << particle_fm << std::endl;
}

// void test_particle_attributes()
// {
//   // Create instances of particles and test their attributes
//   Electron electron;
//   electron.set_energy_deposited_in_layers(10, 20, 30, 40);
//   electron.print();

//   Muon muon;
//   muon.set_is_isolated(true);
//   muon.print();

//   // ... Test attributes of other particles
// }

// void test_particle_decays()
// {
//   // Create instances of particles that can decay and test decay functionality
//   Z z;
//   Electron electron;
//   Positron positron;
//   z.add_decay_product(&electron);
//   z.add_decay_product(&positron);
//   z.print();

//   // ... Test more particle decays
// }

// void test_catalogue_functionality(ParticleCatalogue<Particle>& catalogue)
// {
//   // Test particle catalogue functionality
//   std::cout << "Total number of particles: " << catalogue.get_number_of_particles() << std::endl;

//   std::map<std::string, int> counts = catalogue.get_particle_count_by_type();
//   for (const auto& pair : counts) {
//     std::cout << "Number of " << pair.first << ": " << pair.second << std::endl;
//   }

//   FourMomentum total_momentum = catalogue.sum_four_momenta();
//   std::cout << "Total four-momentum: " << total_momentum << std::endl;

//   std::vector<Lepton*> leptons = catalogue.get_sub_container<Lepton>();
//   std::cout << "Number of leptons: " << leptons.size() << std::endl;

//   catalogue.print_info_by_type<Quark>();

//   // ... Test more catalogue functionality
// }