#include "Charm.h"
#include <utility>   // For std::move


// Constructor without label with validity check
Charm::Charm(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
    : Quark("charm", (anti) ? -2.0/3.0 : 2.0/3.0, 1275, std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

// Constructor with label with validity check
Charm::Charm(const std::string &label, bool anti,  Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
    : Quark("charm", label, (anti) ? -2.0/3.0 : 2.0/3.0, 1275, std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

//Default constructor
Charm::Charm(bool anti, Colour colour_charge) : Quark("charm", (anti) ? -2.0/3.0 : 2.0/3.0, 1275, (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

// Copy constructor
Charm::Charm(const Charm &other)
    : Quark(other) {}

// Move constructor 
Charm::Charm(Charm &&other) noexcept
    : Quark(std::move(other)) {}

// Destructor
Charm::~Charm() {}

// Copy assignment operator
Charm &Charm::operator=(const Charm &other)
{
  if(this != &other)
  {
    Quark::operator=(other);
  }
  return *this;
}

// Move assignment operator
Charm &Charm::operator=(Charm &&other) noexcept
{
  if(this != &other)
  {
    Quark::operator=(std::move(other));
  }
  return *this;
} 








