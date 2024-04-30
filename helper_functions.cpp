#include "helper_functions.h"

std::string to_string(Colour colour)
{
  switch (colour)
  {
  case Colour::Red:
    return "Red";
  case Colour::Green:
    return "Green";
  case Colour::Blue:
    return "Blue";
  case Colour::AntiRed:
    return "AntiRed";
  case Colour::AntiGreen:
    return "AntiGreen";
  case Colour::AntiBlue:
    return "AntiBlue";
  case Colour::None:
    return "None";
  default:
    return "Unknown Colour";
  }
}

std::string to_string(DecayType decay_type)
{
  switch (decay_type)
  {
  case DecayType::Leptonic:
    return "Leptonic";
  case DecayType::Hadronic:
    return "Hadronic";
  case DecayType::Electromagnetic:
    return "Electromagnetic";
  case DecayType::Bosonic:
    return "Bosonic";
  case DecayType::None:
    return "None";
  default:
    return "Unknown Decay type";
  }
}

bool is_anti_colour(Colour colour)
{
  switch (colour)
  {
  case Colour::Red:
    return false;
  case Colour::Green:
    return false;
  case Colour::Blue:
    return false;
  case Colour::AntiRed:
    return true;
  case Colour::AntiGreen:
    return true;
  case Colour::AntiBlue:
    return true;
  case Colour::None:
    throw std::invalid_argument("Error: Cannot have AntiNone Colour");
  default:
    throw std::invalid_argument("Error: Unrecognised Colour");
  }
}

Colour get_anti_colour(Colour colour)
{
  switch (colour)
  {
  case Colour::Red:
    return Colour::AntiRed;
  case Colour::Green:
    return Colour::AntiGreen;
  case Colour::Blue:
    return Colour::AntiBlue;
  case Colour::AntiRed:
    return Colour::Red;
  case Colour::AntiGreen:
    return Colour::Green;
  case Colour::AntiBlue:
    return Colour::Blue;
  case Colour::None:
    return Colour::None;
  default:
    throw std::invalid_argument("Error: Unrecognised Colour");
  }
}

bool contains_decay_type(const std::vector<DecayType> &decay_types, DecayType type_to_find)
{
  // Iterate over the vector to check if the given type is present
  for (const auto &type : decay_types)
  {
    if (type == type_to_find)
    {
      return true;
    }
  }
  return false;
}

// Function to calculate the sum of energies of products 1 and 2 given a momentum
double energy_sum(double momentum, double product1_rest_mass, double product2_rest_mass)
{
  double E1 = sqrt(product1_rest_mass * product1_rest_mass + momentum * momentum);
  double E2 = sqrt(product2_rest_mass * product2_rest_mass + momentum * momentum);
  return E1 + E2;
}

// Function to perform the bisection method to find the momentum of two decay particles
double find_momentum_of_products(double product1_rest_mass, double product2_rest_mass, double decay_particle_rest_mass, double tolerance)
{
  double low = 0.0;
  double high = decay_particle_rest_mass;
  double mid;

  while (high - low > tolerance)
  {
    mid = (low + high) / 2;
    double total_product_energy = energy_sum(mid, product1_rest_mass, product2_rest_mass);

    if (total_product_energy > decay_particle_rest_mass)
      high = mid;
    else
      low = mid;
  }
  return (low + high) / 2;
}

// Function to calculate the sum of energies of products 1, 2, and 3 given a momentum
double energy_sum_three_body(double p1x, double p2x, double p2y, double m1, double m2, double m3)
{
  double p3x = -p1x - p2x;
  double p3y = -p2y;
  double E1 = std::sqrt(m1 * m1 + p1x * p1x);
  double E2 = std::sqrt(m2 * m2 + p2x * p2x + p2y * p2y);
  double E3 = std::sqrt(m3 * m3 + p3x * p3x + p3y * p3y);
  return E1 + E2 + E3;
}


std::vector<double> find_momentum_of_products_three_body(double product1_rest_mass, double product2_rest_mass, double product3_rest_mass, double decay_particle_rest_mass, double tolerance)
{
  double p1x = 0.0;
  double p2x = 0.0;
  double p2y = 0.0;
  double p3x = 0.0;
  double p3y = 0.0;

  // Select the momentum of the first particle
  double extra_energy = decay_particle_rest_mass - product1_rest_mass - product2_rest_mass - product3_rest_mass;
  double E1 = product1_rest_mass + extra_energy / 3;
  p1x = std::sqrt(E1 * E1 - product1_rest_mass * product1_rest_mass);

  double remaining_energy = decay_particle_rest_mass - E1;

  // Calculate the momentum magnitude of the second and third particles
  double p23_momentum = find_momentum_of_products(product2_rest_mass, product3_rest_mass, remaining_energy, tolerance);

  // Calculate the energies of the second and third particles
  double E2 = std::sqrt(product2_rest_mass * product2_rest_mass + p23_momentum * p23_momentum);
  double E3 = std::sqrt(product3_rest_mass * product3_rest_mass + p23_momentum * p23_momentum);

  // Check if the energies of the decay particles add up to the rest mass of the decaying particle
  if (std::abs(E1 + E2 + E3 - decay_particle_rest_mass) < tolerance)
  {
    p2x = -p1x / 2.0;
    p3x = p2x;
    double p23_y_component = std::sqrt(p23_momentum * p23_momentum - p2x * p2x);
    p2y = p23_y_component;
    p3y = -p23_y_component;
  }
  else
  {
    throw std::runtime_error("Error: Cannot determine 3 body decay problem momenta.");
  }
  // Return the momentum components
  return std::vector<double>{p1x, p2x, p2y, p3x, p3y};
}

// Clears console screen based on operating system
void clear_screen()
{
// Clears terminal window
#ifdef _WIN32 // check if program is compiled on Windows
  system("cls");
#else
  // if not windows, clear screen using ANSI escape code
  std::cout << "\033[2J\033[1;1H";
#endif
}

// Function to clear input buffer
void clear_input_buffer()
{
  std::cin.clear();                                                   // Clear any error flags
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard any remaining characters in the input buffer
}

// Prints a string followed by dots
void print_loading_string(const std::string &input_string, int seconds, bool new_new_line, bool elipses)
{
  std::cout << input_string;
  for (int i = 0; i < seconds; ++i)
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (elipses)
    {
      std::cout << ".";
    }
  }
  std::cout << std::endl; // Move to a new line after printing all dots
  if (new_new_line)
  {
    std::cout << std::endl;
  }
}

void fill_leptons(ParticleCatalogue<Particle> &catalogue)
{
  Tau *tau = new Tau();
  Electron *electron = new Electron();
  Muon *muon = new Muon();
  Neutrino *tau_neutrino = new Neutrino("tau");
  Neutrino *electron_neutrino = new Neutrino("electron");
  Neutrino *muon_neutrino = new Neutrino("muon");

  catalogue.add_particle(tau);
  catalogue.add_particle(electron);
  catalogue.add_particle(muon);
  catalogue.add_particle(tau_neutrino);
  catalogue.add_particle(electron_neutrino);
  catalogue.add_particle(muon_neutrino);
}

void fill_anti_leptons(ParticleCatalogue<Particle> &catalogue)
{
  Tau *anti_tau = new Tau(-1);
  Electron *anti_electron = new Electron(-1);
  Muon *anti_muon = new Muon(-1);
  Neutrino *anti_tau_neutrino = new Neutrino("tau", -1);
  Neutrino *anti_electron_neutrino = new Neutrino("electron", -1);
  Neutrino *anti_muon_neutrino = new Neutrino("muon", -1);

  catalogue.add_particle(anti_tau);
  catalogue.add_particle(anti_electron);
  catalogue.add_particle(anti_muon);
  catalogue.add_particle(anti_tau_neutrino);
  catalogue.add_particle(anti_electron_neutrino);
  catalogue.add_particle(anti_muon_neutrino);
}

void fill_bosons(ParticleCatalogue<Particle> &catalogue)
{
  Photon *photon = new Photon();
  Gluon *gluon = new Gluon();
  Z *z = new Z();
  W *w_plus = new W();
  W *w_minus = new W(-1);
  Higgs *higgs = new Higgs();

  catalogue.add_particle(photon);
  catalogue.add_particle(gluon);
  catalogue.add_particle(z);
  catalogue.add_particle(w_plus);
  catalogue.add_particle(w_minus);
  catalogue.add_particle(higgs);
}

void fill_quarks(ParticleCatalogue<Particle> &catalogue)
{
  Up *up = new Up();
  Down *down = new Down();
  Bottom *bottom = new Bottom();
  Charm *charm = new Charm();
  Top *top = new Top();
  Strange *strange = new Strange();

  catalogue.add_particle(up);
  catalogue.add_particle(down);
  catalogue.add_particle(bottom);
  catalogue.add_particle(top);
  catalogue.add_particle(charm);
  catalogue.add_particle(strange);
}

void fill_anti_quarks(ParticleCatalogue<Particle> &catalogue)
{
  Up *anti_up = new Up(true);
  Down *anti_down = new Down(true);
  Bottom *anti_bottom = new Bottom(true);
  Charm *anti_charm = new Charm(true);
  Top *anti_top = new Top(true);
  Strange *anti_strange = new Strange(true);

  catalogue.add_particle(anti_up);
  catalogue.add_particle(anti_down);
  catalogue.add_particle(anti_bottom);
  catalogue.add_particle(anti_top);
  catalogue.add_particle(anti_charm);
  catalogue.add_particle(anti_strange);
}

void fill_particles(ParticleCatalogue<Particle> &catalogue)
{
  fill_leptons(catalogue);
  fill_bosons(catalogue);
  fill_quarks(catalogue);
}

void fill_anti_particles(ParticleCatalogue<Particle> &catalogue)
{
  fill_anti_leptons(catalogue);
  fill_bosons(catalogue);
  fill_anti_quarks(catalogue);
}

void fill_catalogue(ParticleCatalogue<Particle> &catalogue)
{
  fill_particles(catalogue);
  fill_anti_particles(catalogue);
}