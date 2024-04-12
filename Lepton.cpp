// Lepton.cpp
#include "Lepton.h"
#include "FourMomentum.h" 
#include <iostream>  // For std::cout
#include <stdexcept> // For std::invalid_argument

// Default constructor
Lepton::Lepton() : Particle(), lepton_number(0) {}

// Protected constructor without label with validity check
Lepton::Lepton(std::string type, int charge, double rest_mass, std::unique_ptr<FourMomentum> four_momentum, int lepton_number)
    : Particle(type, charge, 1/2, rest_mass, std::move(four_momentum)), lepton_number(lepton_number) {}

// Protected constructor with label with validity check
Lepton::Lepton(std::string type, const std::string &label, int charge,  double rest_mass, std::unique_ptr<FourMomentum> four_momentum, int lepton_number)
    : Particle(type, charge, 1/2, rest_mass, std::move(four_momentum)), lepton_number(lepton_number) {}

// Constructor without label with validity check
Lepton::Lepton(std::string type, int charge, double rest_mass, int lepton_number)
    : Particle(type, charge, 1/2, rest_mass), lepton_number(lepton_number) {}

// Constructor with label with validity check
Lepton::Lepton(std::string type, const std::string &label, int charge, double rest_mass, int lepton_number)
    : Particle(type, label, charge, 1/2, rest_mass), lepton_number(lepton_number) {}

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