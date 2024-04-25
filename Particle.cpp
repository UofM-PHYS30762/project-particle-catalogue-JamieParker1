// Lepton.cpp
#include "Particle.h"
#include "FourMomentum.h"
#include <iostream>  // For std::cout
#include <stdexcept> // For std::invalid_argument

const int fm_initialise_error(-1);

// Helper functions
bool contains_decay_type(const std::vector<DecayType>& decay_types, DecayType type_to_find) {
    // Iterate over the vector to check if the given type is present
    for (const auto& type : decay_types) {
        if (type == type_to_find) {
            return true;
        }
    }
    return false;
}

// Default constructor
Particle::Particle() : charge(0), four_momentum(std::make_unique<FourMomentum>()), possible_decay_types(std::vector<DecayType>{DecayType::None}) {}

// Protected constructor without label with four-momentum
Particle::Particle(std::string type, int charge, double spin, double rest_mass, std::unique_ptr<FourMomentum> four_momentum, std::vector<DecayType> possible_decay_types)
    : type(type), charge(charge), spin(spin), rest_mass(rest_mass), four_momentum(std::move(four_momentum)), possible_decay_types(possible_decay_types)
{
  if (this->four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
  check_mass_validity();
}

// Protected constructor with label with four-momentum
Particle::Particle(std::string type, const std::string &label, int charge, double spin, double rest_mass, std::unique_ptr<FourMomentum> fourMomentum, std::vector<DecayType> possible_decay_types)
    : type(type), label(label), spin(spin), charge(charge), rest_mass(rest_mass), four_momentum(std::move(fourMomentum)), possible_decay_types(possible_decay_types)
{
  if (this->four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
  check_mass_validity();
}

// Constructor without label without four-momentum
Particle::Particle(std::string type, int charge, double spin, double rest_mass, std::vector<DecayType> possible_decay_types)
    : type(type), charge(charge), spin(spin), rest_mass(rest_mass), four_momentum(std::make_unique<FourMomentum>(rest_mass, 0, 0, 0, true)), possible_decay_types(possible_decay_types) {}

// Constructor with label without four-momentum
Particle::Particle(std::string type, const std::string &label, int charge, double spin, double rest_mass, std::vector<DecayType> possible_decay_types)
    : type(type), label(label), charge(charge), spin(spin), rest_mass(rest_mass), four_momentum(std::make_unique<FourMomentum>(rest_mass, 0, 0, 0, true)), possible_decay_types(possible_decay_types) {}

// Copy constructor
Particle::Particle(const Particle &other)
    : label(other.label), charge(other.charge), spin(other.spin),
      four_momentum(other.four_momentum ? std::make_unique<FourMomentum>(*other.four_momentum) : nullptr) 
{
  decay_products.reserve(other.decay_products.size());
  for (const auto &particle : other.decay_products)
  {
    decay_products.push_back(particle ? std::make_unique<Particle>(*particle) : nullptr);
  } 
}

// Move constructor
Particle::Particle(Particle &&other) noexcept
    : label(std::move(other.label)), charge(other.charge), spin(other.spin), four_momentum(std::move(other.four_momentum)), decay_products(std::move(other.decay_products)) {}

// Virtual destructor
Particle::~Particle() {}

// Copy assignment operator
Particle &Particle::operator=(const Particle &other)
{
  if (this != &other)
  {
    label = other.label;
    charge = other.charge;
    spin = other.spin;
    rest_mass = other.rest_mass;
    type = other.type;
    four_momentum = other.four_momentum ? std::make_unique<FourMomentum>(*other.four_momentum) : nullptr;
    decay_products.clear();
    decay_products.reserve(other.decay_products.size());
    for (const auto &particle : other.decay_products)
    {
      decay_products.push_back(particle ? std::make_unique<Particle>(*particle) : nullptr);
    }
  }
  return *this;
}

// Move assignment operator
Particle &Particle::operator=(Particle &&other) noexcept
{
  if (this != &other)
  {
    label = std::move(other.label);
    charge = other.charge;
    spin = other.spin;
    rest_mass = other.rest_mass;
    type = other.type;
    four_momentum = std::move(other.four_momentum);
    decay_products = std::move(other.decay_products);
  }
  return *this;
}

// Setters
void Particle::set_label(const std::string &label)
{
  this->label = label;
}

void Particle::set_four_momentum(std::unique_ptr<FourMomentum> fourMomentum)
{
  this->four_momentum = std::move(fourMomentum);
  check_mass_validity();
}

void Particle::set_decay_products(std::vector<std::unique_ptr<Particle>> decay_products, DecayType decay_type)
{
  if (!contains_decay_type(possible_decay_types, decay_type))
  {
    std::cerr << "Error: Particle cannot decay via that path\n";
  }
  else if (validate_decay_products(decay_products, decay_type))
  {
    this->decay_products = std::move(decay_products);
  }
  else
  {
    std::cerr << "Decay products validation failed." << std::endl;
  }
}

void Particle::auto_set_decay_products(std::vector<std::unique_ptr<Particle>> decay_products, DecayType decay_type)
{
  return;
}
// void Tau::auto_set_decay_products(std::vector<std::unique_ptr<Particle>> decayProducts)
// {
//   if (decayProducts.empty())
//   {
//     return;
//   }

//   double tau_invmass = four_momentum->invariant_mass();

//   if (decayProducts.size() == 3) // if there are three decay products
//   {
//     double rest_mass_1 = decayProducts[0]->get_rest_mass();
//     double rest_mass_2 = decayProducts[1]->get_rest_mass();
//     double rest_mass_3 = decayProducts[2]->get_rest_mass();

//     // Calculate energies for decay products in the center of mass frame
//     // No decay model, effectively random, but possible, energies
//     double energy_1 = (std::pow(tau_invmass, 2) + std::pow(rest_mass_1, 2) - (std::pow(rest_mass_2, 2) + std::pow(rest_mass_3, 2))) / (2 * tau_invmass);
//     double energy_2 = (std::pow(tau_invmass, 2) + std::pow(rest_mass_2, 2) - (std::pow(rest_mass_1, 2) + std::pow(rest_mass_3, 2))) / (2 * tau_invmass);
//     double energy_3 = (std::pow(tau_invmass, 2) + std::pow(rest_mass_3, 2) - (std::pow(rest_mass_1, 2) + std::pow(rest_mass_2, 2))) / (2 * tau_invmass);

//     // Calculate momentum magnitudes from energies
//     double momentum_1 = std::sqrt(std::pow(energy_1, 2) - std::pow(rest_mass_1, 2));
//     double momentum_2 = std::sqrt(std::pow(energy_2, 2) - std::pow(rest_mass_2, 2));
//     double momentum_3 = std::sqrt(std::pow(energy_3, 2) - std::pow(rest_mass_3, 2));

//     // Define the spatial distribution of momenta
//     // For a planar decay in the x-y plane, evenly distribute angles
//     double angle_1 = 0;            // Direct particle 1 along the x-axis
//     double angle_2 = 2 * M_PI / 3; // Direct particle 2 at 120 degrees
//     double angle_3 = 4 * M_PI / 3; // Direct particle 3 at 240 degrees

//     // Set decay product four-momenta in the center of mass frame
//     decayProducts[0]->set_four_momentum(std::make_unique<FourMomentum>(energy_1, momentum_1 * std::cos(angle_1), momentum_1 * std::sin(angle_1), 0));
//     decayProducts[1]->set_four_momentum(std::make_unique<FourMomentum>(energy_2, momentum_2 * std::cos(angle_2), momentum_2 * std::sin(angle_2), 0));
//     decayProducts[2]->set_four_momentum(std::make_unique<FourMomentum>(energy_3, momentum_3 * std::cos(angle_3), momentum_3 * std::sin(angle_3), 0));

//     // Apply a Lorentz boost from the center of mass frame to the laboratory frame
//     std::vector<double> tau_velocity = four_momentum->get_velocity_vector();

//     decayProducts[0]->lorentz_boost(tau_velocity);
//     decayProducts[1]->lorentz_boost(tau_velocity);
//     decayProducts[2]->lorentz_boost(tau_velocity);

//     if (validate_decay_products(decayProducts))
//     {
//       this->decay_products = std::move(decay_products);
//     }
//     else
//     {
//       std::cerr << "INVALID DECAY PRODUCTS\n";
//     }
//   }
//   else if (decayProducts.size() != 3)
//   {
//     std::cerr << "Error: Incorrect number of decay products.\n";
//     return;
//   }
// }
// void Tau::auto_set_decay_products(std::vector<std::unique_ptr<Particle>> decayProducts)
// {
//   if (decayProducts.empty() || decayProducts.size() != 3)
//   {
//     std::cerr << "Error: Incorrect number of decay products." << std::endl;
//     return;
//   }
//   double rest_mass_1 = decayProducts[0]->get_rest_mass();
//   double rest_mass_2 = decayProducts[1]->get_rest_mass();
//   double rest_mass_3 = decayProducts[2]->get_rest_mass();

//   std::random_device rd;
//   std::mt19937 gen(rd());
//   // Define distribution for theta (0 to pi)
//   std::uniform_real_distribution<> dist_theta(0, M_PI);
//   // Define distribution for phi (0 to 2*pi)
//   std::uniform_real_distribution<> dist_phi(0, 2 * M_PI);

//   // Generate random theta and phi values for first two decay particles
//   double theta1 = dist_theta(gen);
//   double phi1 = dist_phi(gen);
//   double theta2 = dist_theta(gen);
//   double phi2 = dist_phi(gen);
//   // Generate momentum values for first two decay particles with size guesses
//   double px1 = std::sin(theta1) * std::cos(phi1) * (four_momentum->get_Px() / 3);
//   double px2 = std::sin(theta2) * std::cos(phi2) * (four_momentum->get_Px() / 3);
//   double py1 = std::sin(theta1) * std::sin(phi1) * (four_momentum->get_Py() / 3);
//   double py2 = std::sin(theta2) * std::sin(phi2) * (four_momentum->get_Py() / 3);
//   double pz1 = std::cos(theta1) * (four_momentum->get_Pz() / 3);
//   double pz2 = std::cos(theta2) * (four_momentum->get_Pz() / 3);
//   // Determine third particles momentum from momentum conservation of these three particles
//   double px3 = -(px1 + px2);
//   double py3 = -(py1 + py2);
//   double pz3 = -(pz1 + pz2);
//   // Compute energies of particles from rest masses and momentum values
//   double e1 = std::sqrt(px1 * px1 + py1 * py1 + pz1 * pz1 + rest_mass_1 * rest_mass_1);
//   double e2 = std::sqrt(px2 * px2 + py2 * py2 + pz2 * pz2 + rest_mass_2 * rest_mass_2);
//   double e3 = std::sqrt(px3 * px3 + py3 * py3 + pz3 * pz3 + rest_mass_3 * rest_mass_3);
//   // Sum energies and check against taus energy
//   double total_energy = e1 + e2 + e3;
//   if (total_energy != four_momentum->get_energy())
//   {
//     std::cout << total_energy << std::endl;
//     std::cout << four_momentum->get_energy() << std::endl;
//     double scaling_factor = four_momentum->get_energy()/total_energy;
//     std::cout << scaling_factor << std::endl;
//     std::cout << px1 << std::endl;
//     px1 *= scaling_factor;
//     std::cout << px1 << std::endl;
//     px2 *= scaling_factor;
//     px3 *= scaling_factor;
//     py1 *= scaling_factor;
//     py2 *= scaling_factor;
//     py3 *= scaling_factor;
//     pz1 *= scaling_factor;
//     pz2 *= scaling_factor;
//     pz3 *= scaling_factor;

//     // Compute energies of particles from rest masses and momentum values
//     e1 = std::sqrt(px1 * px1 + py1 * py1 + pz1 * pz1 + rest_mass_1 * rest_mass_1);
//     e2 = std::sqrt(px2 * px2 + py2 * py2 + pz2 * pz2 + rest_mass_2 * rest_mass_2);
//     e3 = std::sqrt(px3 * px3 + py3 * py3 + pz3 * pz3 + rest_mass_3 * rest_mass_3);
//     total_energy = e1 + e2 + e3;
//     std::cout << total_energy << std::endl;
//     std::cout << four_momentum->get_energy() << std::endl;
//   }
// }

// Getters
std::string Particle::get_label() const
{
  return label;
}

int Particle::get_charge() const
{
  return charge;
}

double Particle::get_spin() const
{
  return spin;
}

double Particle::get_rest_mass() const
{
  return rest_mass;
}

std::string Particle::get_type() const
{
  return type;
}

const FourMomentum &Particle::get_four_momentum() const
{
  if (four_momentum->get_energy() == 0 && four_momentum->get_Px() == 0 && four_momentum->get_Py() == 0 && four_momentum->get_Pz() == 0)
  {
    throw std::runtime_error("FourMomentum has not been intitialised.");
  }
  return *four_momentum;
}

const std::vector<std::unique_ptr<Particle>> &Particle::get_decay_products() const
{
  return decay_products;
}


// Friend functions
FourMomentum sum_four_momentum(const Particle &a, const Particle &b)
{
  // Direct access to FourMomentum through Lepton's unique_ptr
  FourMomentum result(
      a.four_momentum->get_energy() + b.four_momentum->get_energy(),
      a.four_momentum->get_Px() + b.four_momentum->get_Px(),
      a.four_momentum->get_Py() + b.four_momentum->get_Py(),
      a.four_momentum->get_Pz() + b.four_momentum->get_Pz());
  return result;
}

double dot_product_four_momentum(const Particle &a, const Particle &b)
{
  // Directly utilize FourMomentum's members via Particles's unique_ptr
  return a.four_momentum->get_energy() * b.four_momentum->get_energy() -
         (a.four_momentum->get_Px() * b.four_momentum->get_Px() +
          a.four_momentum->get_Py() * b.four_momentum->get_Py() +
          a.four_momentum->get_Pz() * b.four_momentum->get_Pz());
}

// Lorentz boost functions
void Particle::lorentz_boost(double v_x, double v_y, double v_z)
{
  four_momentum->lorentz_boost(v_x, v_y, v_z);
}

void Particle::lorentz_boost(std::vector<double> v_xyz)
{
  four_momentum->lorentz_boost(v_xyz);
}

// Virtual print function
void Particle::print() const
{
  std::cout << "\033[1mType:\033[0m " << type << ", \033[1mLabel:\033[0m " << label << ", \033[1mCharge (e):\033[0m " << charge << ", \033[1mSpin:\033[0m " << spin << ", \033[1mFour Momentum (MeV): \033[0m[" << *four_momentum << "]" << std::endl;
  // Print decay products if there are any
  // if (!decay_products.empty()) {
  //   std::cout << "\033[1mDecay Products:\033[0m" << std::endl;
  //   for (const auto& product : decay_products) {
  //     product->print();
  //   }
  // }
}

// Implement the validity check method
void Particle::check_mass_validity() const
{
  if (four_momentum)
  {
    double invMass = four_momentum->invariant_mass();
    if (std::abs(invMass - rest_mass) > 1e-5)
    { // 1e-5 tolerance 
      throw std::invalid_argument("Rest mass does not match the invariant mass of the provided FourMomentum.");
    }
  }
}

// Decay product validity checker
bool Particle::validate_decay_products(const std::vector<std::unique_ptr<Particle>>& decay_products, DecayType decay_type) const
{
  // Checking four momentum conservation
  //////// NEED TO ADD SOME MORE CHECKS BUT CAN COME LATER ////////
  FourMomentum product_total_momentum; 
  int product_total_charge = 0;
  double product_total_spin = 0;
  int product_total_lepton_number = 0;
  double product_total_baryon_number = 0;
  for (const auto &product : decay_products)
  {
    product_total_momentum = product_total_momentum + product->get_four_momentum();
    product_total_charge = product_total_charge + product->get_charge();
    product_total_spin = product_total_spin + product->get_spin();
    product_total_lepton_number = product_total_lepton_number + product->get_lepton_number();
    product_total_baryon_number = product_total_baryon_number + product->get_baryon_number();
  }
  FourMomentum diff = product_total_momentum - *four_momentum;
  // Check if the difference in each component is within an acceptable range
  bool four_momentum_conserved = std::abs(diff.get_energy()) < 1e-5 &&
                                 std::abs(diff.get_Px()) < 1e-5 &&
                                 std::abs(diff.get_Py()) < 1e-5 &&
                                 std::abs(diff.get_Pz()) < 1e-5;
  bool charge_conserved = (charge == product_total_charge);
  bool spin_conserved = (spin == product_total_spin);
  bool lepton_number_conserved = (this->get_lepton_number() == product_total_lepton_number);
  bool baryon_number_conserved = (this->get_baryon_number() == product_total_baryon_number);
  return (four_momentum_conserved && charge_conserved && spin_conserved && lepton_number_conserved && baryon_number_conserved); 
}

