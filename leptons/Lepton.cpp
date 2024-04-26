// Lepton.cpp
#include "Lepton.h"
#include "../FourMomentum.h" 
#include <iostream>  // For std::cout
#include <stdexcept> // For std::invalid_argument

// Default constructor
Lepton::Lepton(int lepton_number) : Particle((lepton_number == 1) ? "lepton" : "antilepton", (lepton_number == 1) ? -1 : 1, 0.5, 0, std::vector<DecayType>{DecayType::None}), lepton_number(lepton_number) {}
 
// Protected constructor without label with four momentum
Lepton::Lepton(std::string type, int charge, double rest_mass, std::unique_ptr<FourMomentum> four_momentum, int lepton_number, std::vector<DecayType> possible_decay_types)
    : Particle((lepton_number == 1) ? type : "anti" + type, charge, 0.5, rest_mass, std::move(four_momentum), possible_decay_types), lepton_number(lepton_number) {}

// Protected constructor with label with four momentum
Lepton::Lepton(std::string type, const std::string &label, int charge,  double rest_mass, std::unique_ptr<FourMomentum> four_momentum, int lepton_number, std::vector<DecayType> possible_decay_types)
    : Particle((lepton_number == 1) ? type : "anti" + type, label, charge, 0.5, rest_mass, std::move(four_momentum), possible_decay_types), lepton_number(lepton_number) {}

// Constructor without label without four momentum
Lepton::Lepton(std::string type, int charge, double rest_mass, int lepton_number, std::vector<DecayType> possible_decay_types)
    : Particle((lepton_number == 1) ? type : "anti" + type, charge, 0.5, rest_mass, possible_decay_types), lepton_number(lepton_number) {}

// Constructor with label without four momentum
Lepton::Lepton(std::string type, const std::string &label, int charge, double rest_mass, int lepton_number, std::vector<DecayType> possible_decay_types)
    : Particle((lepton_number == 1) ? type : "anti" + type, label, charge, 0.5, rest_mass, possible_decay_types), lepton_number(lepton_number) {}

// Copy constructor
Lepton::Lepton(const Lepton &other)
    : Particle(other), lepton_number(other.lepton_number) {}

// Move constructor
Lepton::Lepton(Lepton &&other) noexcept
    : Particle(std::move(other)), lepton_number(other.lepton_number) {} 

// Virtual destructor
Lepton::~Lepton() {}

// Copy assignment operator
Lepton &Lepton::operator=(const Lepton &other)
{
  if(this != &other)
  {
    Particle::operator=(other); // Call the base class copy assignment operator
    lepton_number = other.lepton_number;
  }
  return *this;
}

// Move assignment operator
Lepton &Lepton::operator=(Lepton &&other) noexcept
{
  if(this != &other)
  {
    Particle::operator=(std::move(other)); // Call the base class move assignment operator
    lepton_number = other.lepton_number;    
  }
  return *this;
}

// Virtual print function
void Lepton::print() const
{
  Particle::print();
  std::cout << "\033[1mLepton number:\033[0m " << lepton_number << std::endl;
}