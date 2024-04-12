// Lepton.cpp
#include "Particle.h"
#include "FourMomentum.h"
#include <iostream>  // For std::cout
#include <stdexcept> // For std::invalid_argument

// Default constructor
Particle::Particle() : charge(0), four_momentum(nullptr) {}

// Protected constructor without label with validity check
Particle::Particle(std::string type, int charge, double spin, double rest_mass, std::unique_ptr<FourMomentum> fourMomentum)
    : type(type), charge(charge), spin(spin), rest_mass(rest_mass), four_momentum(std::move(fourMomentum))
{
  if (this->four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
  check_mass_validity();
}

// Protected constructor with label with validity check
Particle::Particle(std::string type, const std::string &label, int charge, double spin, double rest_mass, std::unique_ptr<FourMomentum> fourMomentum)
    : type(type), label(label), spin(spin), charge(charge), rest_mass(rest_mass), four_momentum(std::move(fourMomentum))
{
  if (this->four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
  check_mass_validity();
}

// Constructor without label with validity check
Particle::Particle(std::string type, int charge, double spin, double rest_mass)
    : type(type), charge(charge), spin(spin), rest_mass(rest_mass), four_momentum(std::make_unique<FourMomentum>()) {}


// Constructor with label with validity check
Particle::Particle(std::string type, const std::string &label, int charge, double spin, double rest_mass)
    : type(type), label(label), charge(charge), spin(spin), rest_mass(rest_mass), four_momentum(std::make_unique<FourMomentum>()) {}

// Copy constructor
Particle::Particle(const Particle &other)
    : label(other.label), charge(other.charge), spin(other.spin),
      four_momentum(other.four_momentum ? std::make_unique<FourMomentum>(*other.four_momentum) : nullptr) {}

// Move constructor
Particle::Particle(Particle &&other) noexcept
    : label(std::move(other.label)), charge(other.charge), spin(other.spin), four_momentum(std::move(other.four_momentum)) {}

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

// Getters
std::string Particle::get_label() const
{
  return label;
}

int Particle::get_charge() const
{
  return charge;
}

std::string Particle::get_type() const
{
  return type;
}

const FourMomentum &Particle::get_four_momentum() const
{
  if (!four_momentum)
  {
    throw std::runtime_error("FourMomentum is not initialized.");
  }
  return *four_momentum;
}

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
  // Directly utilize FourMomentum's members via Lepton's unique_ptr
  return a.four_momentum->get_energy() * b.four_momentum->get_energy() -
         (a.four_momentum->get_Px() * b.four_momentum->get_Px() +
          a.four_momentum->get_Py() * b.four_momentum->get_Py() +
          a.four_momentum->get_Pz() * b.four_momentum->get_Pz());
}

// Virtual print function
void Particle::print() const
{
  std::cout << "\033[1mType:\033[0m " << type << ", \033[1mLabel:\033[0m " << label << ", \033[1mCharge (e):\033[0m " << charge << ", \033[1mSpin (ℏ):\033[0m " << spin << ", \033[1mFour Momentum (MeV): \033[0m[" << *four_momentum << "]" << std::endl;
}

// Implement the validity check method
void Particle::check_mass_validity() const
{
  if (four_momentum)
  {
    double invMass = four_momentum->invariant_mass();
    if (std::abs(invMass - rest_mass) > 1e-5)
    { // 1e-5 tolerance for floating-point comparison
      throw std::invalid_argument("Rest mass does not match the invariant mass of the provided FourMomentum.");
    }
  }
}