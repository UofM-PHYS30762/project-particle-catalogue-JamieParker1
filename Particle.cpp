// Lepton.cpp
#include "Particle.h"
#include "FourMomentum.h"
#include "helper_functions.h"
#include <iostream>  // For std::cout
#include <stdexcept> // For std::invalid_argument


// Default constructor
Particle::Particle() : charge(0), four_momentum(std::make_unique<FourMomentum>()), possible_decay_types(std::vector<DecayType>{DecayType::None}) {}

// Protected constructor without label with four-momentum
Particle::Particle(std::string type, int charge, double spin, double rest_mass, std::unique_ptr<FourMomentum> four_momentum, std::vector<DecayType> possible_decay_types)
    : type(type), charge(charge), spin(spin), rest_mass(rest_mass), four_momentum(std::move(four_momentum)), possible_decay_types(possible_decay_types)
{
  if (four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
  else if (is_invariant_mass_valid(four_momentum->invariant_mass()))
  {
    this->four_momentum = std::move(four_momentum);
  }
  else
  {
    throw std::invalid_argument("Rest mass does not match the invariant mass of the provided FourMomentum.");
  }
}

// Protected constructor with label with four-momentum
Particle::Particle(std::string type, const std::string &label, int charge, double spin, double rest_mass, std::unique_ptr<FourMomentum> fourMomentum, std::vector<DecayType> possible_decay_types)
    : type(type), label(label), spin(spin), charge(charge), rest_mass(rest_mass), possible_decay_types(possible_decay_types)
{
  if (four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
  else if (is_invariant_mass_valid(four_momentum->invariant_mass()))
  {
    this->four_momentum = std::move(four_momentum);
  }
  else
  {
    throw std::invalid_argument("Rest mass does not match the invariant mass of the provided FourMomentum.");
  }
}
// Constructor without label without four-momentum
Particle::Particle(std::string type, int charge, double spin, double rest_mass, std::vector<DecayType> possible_decay_types)
    : type(type), charge(charge), spin(spin), rest_mass(rest_mass), four_momentum((rest_mass > 0) ? std::make_unique<FourMomentum>(rest_mass, 0, 0, 0, true) : std::make_unique<FourMomentum>(1, 0, 0, 1)), possible_decay_types(possible_decay_types) {}

// Constructor with label without four-momentum
Particle::Particle(std::string type, const std::string &label, int charge, double spin, double rest_mass, std::vector<DecayType> possible_decay_types)
    : type(type), label(label), charge(charge), spin(spin), rest_mass(rest_mass), four_momentum((rest_mass > 0) ? std::make_unique<FourMomentum>(rest_mass, 0, 0, 0, true) : std::make_unique<FourMomentum>(1, 0, 0, 1)), possible_decay_types(possible_decay_types) {}

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

void Particle::set_four_momentum(std::unique_ptr<FourMomentum> four_momentum)
{
  if (four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
  else if (is_invariant_mass_valid(four_momentum->invariant_mass()))
  {
    this->four_momentum = std::move(four_momentum);
  }
  else
  {
    throw std::invalid_argument("Rest mass does not match the invariant mass of the provided FourMomentum.");
  }
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
  if (decay_products.size() == 2)
  {
    // Work in decaying particle's rest frame
    // Only energy in system is decaying particle's rest mass
    if (!(rest_mass > (decay_products[0]->get_rest_mass() + decay_products[1]->get_rest_mass())))
    {
      std::cerr << "Error: Rest masses of decay particles exceeds decaying particle's\n";
      return;
    }
    // Arbitrarily choose, in rest frame, decaying particles move along x axis
    // E1^2 = P1^2 + M1^2, E2^2 = P2^2 + M2^2 (P1^2 = P2^2 = P^2, E1+E2=M_particle)
    // sqrt(P^2 + M1^2) + sqrt(P^2 + M2^2) = M_particle
    double product1_rest_mass = decay_products[0]->get_rest_mass();
    double product2_rest_mass = decay_products[1]->get_rest_mass();

    double product_px_magnitude = find_momentum_of_products(product1_rest_mass, product2_rest_mass, rest_mass);
    double product1_energy = std::sqrt(product1_rest_mass*product1_rest_mass + product_px_magnitude*product_px_magnitude);
    double product2_energy = std::sqrt(product2_rest_mass*product2_rest_mass + product_px_magnitude*product_px_magnitude);
    
    // Have first particle move +ve along x axis
    std::unique_ptr<FourMomentum> product1_fm =  std::make_unique<FourMomentum>(product1_energy, product_px_magnitude,0,0); 
    // Have second particle move -ve along x axis
    std::unique_ptr<FourMomentum> product2_fm =  std::make_unique<FourMomentum>(product2_energy, -product_px_magnitude,0,0);

    // Find velocity of decaying particle to perform lorentz boost
    std::vector<double> decaying_particle_velocity = four_momentum->get_velocity_vector();
    // Perform lorentz boost on rest-frame four momentums
    std::cout << product1_fm->invariant_mass() << std::endl;
    std::cout << product2_fm->invariant_mass() << std::endl;
    
    product1_fm->lorentz_boost(decaying_particle_velocity);
    product2_fm->lorentz_boost(decaying_particle_velocity);

    std::cout << product1_fm->invariant_mass() << std::endl;
    std::cout << product2_fm->invariant_mass() << std::endl;
    // Give decay particles their four momenta
    decay_products[0]->set_four_momentum(std::move(product1_fm));
    decay_products[1]->set_four_momentum(std::move(product2_fm));
    // Validate these auto products
    if (validate_decay_products(decay_products, decay_type))
    {
      this->decay_products = std::move(decay_products);
    }
    else
    {
      std::cout << "Error: Auto-set decay products failed.\n";
      std::cout << "Father fm:" << *four_momentum << std::endl;
      std::cout << "Product1 fm:" << decay_products[0]->get_four_momentum() << std::endl;
      std::cout << "Product2 fm:" << decay_products[1]->get_four_momentum() << std::endl;
      return;
    }
  }
  return;
}

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
  std::cout << "\033[1mType:\033[0m " << type << ", \033[1mLabel:\033[0m " << label << ", \033[1mCharge (e):\033[0m " << charge << ", \033[1mSpin:\033[0m " << spin << ", \033[1mRest Mass (MeV): \033[0m" << rest_mass <<", \033[1mFour Momentum (MeV): \033[0m[" << *four_momentum << "]" << std::endl;
}

// Implement the validity check method
bool Particle::is_invariant_mass_valid(double invariant_mass) const
{
  if (std::abs(invariant_mass - rest_mass) > 1e-5)
  { // 1e-5 tolerance
    return false;
  }
  return true;
}

// Decay product validity checker
bool Particle::validate_decay_products(const std::vector<std::unique_ptr<Particle>> &decay_products, DecayType decay_type) const
{
  // Checking four momentum conservation
  //////// NEED TO ADD SOME MORE CHECKS BUT CAN COME LATER ////////
  FourMomentum product_total_momentum;
  int product_total_charge = 0;
  int product_total_lepton_number = 0;
  double product_total_baryon_number = 0;
  for (const auto &product : decay_products)
  {
    product_total_momentum = product_total_momentum + product->get_four_momentum();
    product_total_charge = product_total_charge + product->get_charge();
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
  bool lepton_number_conserved = (this->get_lepton_number() == product_total_lepton_number);
  bool baryon_number_conserved = (this->get_baryon_number() == product_total_baryon_number);
  return (four_momentum_conserved && charge_conserved && lepton_number_conserved && baryon_number_conserved);
}
