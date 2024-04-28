#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "Particle.h"
#include <vector>
#include <string>

std::string to_string(Colour colour);
std::string to_string(DecayType decay_type);
bool is_anti_colour(Colour colour);
Colour get_anti_colour(Colour colour);

bool contains_decay_type(const std::vector<DecayType> &decay_types, DecayType type_to_find);
double energy_sum(double momentum, double product1_rest_mass, double product2_rest_mass);
double find_momentum_of_products(double product1_rest_mass, double product2_rest_mass, double decay_particle_rest_mass, double tolerance = 1e-6);

void clear_screen();

#endif // HELPER_FUNCTIONS_H