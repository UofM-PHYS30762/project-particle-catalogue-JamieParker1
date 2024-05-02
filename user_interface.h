#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "ParticleCatalogue.h"
#include "Particle.h"
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

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>
#include <variant>
#include <stack>

double get_valid_number(const std::string &prompt, double minVal = -std::numeric_limits<double>::infinity(), double maxVal = std::numeric_limits<double>::infinity());
int get_integer_input(const std::string &prompt, int min_value, int max_value);

std::string input_particle_type();
std::string input_specific_particle_type();

// Function to display the main menu
void display_main_menu();
// Function to display options to showcase program
void display_program_showcase_menu();
// Function to display the custom usage menu
void display_custom_usage_menu(int sub_num = 0);
// Function to display user catalogue operations
void display_user_catalogue_operations_menu();
// Function to display help menu
void display_help();
// Function to display the add particles submenu
void display_add_particles_menu();
// Function to display the operations submenu
void display_operations_menu();

void get_momentum_values(double &px, double &py, double &pz);
void get_quark_details(Colour &colour_charge, bool is_anti);
void get_electron_details(std::vector<double> &energy_deposited_in_layers, double energy);
void get_neutrino_details(std::string &flavour, bool &has_interacted);
void get_w_details(int &charge);
void get_tau_decay_products(std::vector<std::unique_ptr<Particle>> &decay_products, DecayType &decay_type, bool is_anti);
void get_higgs_decay_products(std::vector<std::unique_ptr<Particle>> &decay_products, DecayType &decay_type);
void get_z_decay_products(std::vector<std::unique_ptr<Particle>> &decay_products, DecayType &decay_type);
void get_w_decay_products(std::vector<std::unique_ptr<Particle>> &decay_products, DecayType &decay_type, int charge);



// Function to get sub catalogue
//void get_sub_catalogue_menu(ParticleCatalogue<Particle>& user_catalogue, int sub_num);
ParticleCatalogue<Particle> get_sub_catalogue(ParticleCatalogue<Particle>& user_catalogue);

// Function to handle printing information by type or exact type
void print_information_by_type(ParticleCatalogue<Particle> &user_catalogue, bool exact);

// Menu for adding a particle
void add_particles_menu_navigation(ParticleCatalogue<Particle> &user_catalogue);

// Function to handle user input viewing operations on particle catalogue
void view_catalogue_menu_navigation(ParticleCatalogue<Particle> &user_catalogue, bool sub_catalogue = false);
// Overloaded functions

// Function to handle user input for custom usage menu
//void custom_usage_menu_navigation(ParticleCatalogue<Particle> &user_catalogue,  int sub_num = 0);
void custom_usage_menu_navigation(ParticleCatalogue<Particle> &user_catalogue);

// Function to display program showcase options
void program_showcase_menu_navigation();

// Function to handle user input for main menu
void main_menu_navigation(ParticleCatalogue<Particle> &user_catalogue);

#endif // USER_INTERFACE_H