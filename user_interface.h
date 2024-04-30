#include "ParticleCatalogue.h"
#include "Particle.h"
#include "helper_functions.h"

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>


int get_integer_input(const std::string &prompt, int min_value, int max_value);
// Function to display the main menu
void display_main_menu();

// Function to display options to showcase program
void display_program_showcase_menu();

// Function to display the custom usage menu
void display_custom_usage_menu();

// Function to display user catalogue operations
void display_user_Catalogue_operations_menu();

// Function to display help menu
void display_help();

// Function to display the add particles submenu
void display_add_particles_menu();

// Function to display the operations submenu
void display_operations_menu();

// Function to handle user input for custom usage menu
void custom_usage_menu_navigation(ParticleCatalogue<Particle> &user_catalogue);

// Function to display program showcase options
void program_showcase_menu_navigation(ParticleCatalogue<Particle> &showcase_catalogue);

// Function to handle user input for main menu
void main_menu_navigation(ParticleCatalogue<Particle> &showcase_catalogue, ParticleCatalogue<Particle> &user_catalogue);
