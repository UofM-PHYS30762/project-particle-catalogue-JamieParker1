#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

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

#include "Particle.h"
#include <vector>
#include <string>
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::seconds

std::string to_string(Colour colour);
std::string to_string(DecayType decay_type);
bool is_anti_colour(Colour colour);
Colour get_anti_colour(Colour colour);

bool contains_decay_type(const std::vector<DecayType> &decay_types, DecayType type_to_find);
double energy_sum(double momentum, double product1_rest_mass, double product2_rest_mass);
double find_momentum_of_products(double product1_rest_mass, double product2_rest_mass, double decay_particle_rest_mass, double tolerance = 1e-6);
double energy_sum_three_body(double p1x, double p2x, double p2y, double m1, double m2, double m3);
std::vector<double> find_momentum_of_products_three_body(double product1_rest_mass, double product2_rest_mass, double product3_rest_mass, double decay_particle_rest_mass, double tolerance = 1e-5);

void clear_screen();
void clear_input_buffer();
void print_loading_string(const std::string &input_string, int seconds, bool new_new_line = false, bool elipses = true);

void fill_leptons(ParticleCatalogue<Particle> &catalogue);
void fill_anti_leptons(ParticleCatalogue<Particle> &catalogue);
void fill_bosons(ParticleCatalogue<Particle> &catalogue);
void fill_quarks(ParticleCatalogue<Particle> &catalogue);
void fill_anti_quarks(ParticleCatalogue<Particle> &catalogue);
void fill_particles(ParticleCatalogue<Particle> &catalogue);
void fill_anti_particles(ParticleCatalogue<Particle> &catalogue);
void fill_catalogue(ParticleCatalogue<Particle> &catalogue);

#endif // HELPER_FUNCTIONS_H