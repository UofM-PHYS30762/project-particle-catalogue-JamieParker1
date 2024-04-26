#include "Up.h"
#include <utility>   // For std::move


// Constructor without label with validity check
Up::Up(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
    : Quark("up", (anti) ? -2.0/3.0 : 2.0/3.0, 2.3, std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

// Constructor with label with validity check
Up::Up(const std::string &label, bool anti,  Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
    : Quark("up", label, (anti) ? -2.0/3.0 : 2.0/3.0, 2.3, std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

//Default constructor
Up::Up(bool anti, Colour colour_charge) : Quark("up", (anti) ? -2.0/3.0 : 2.0/3.0, 2.3, (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

// Copy constructor
Up::Up(const Up &other)
    : Quark(other) {}

// Move constructor 
Up::Up(Up &&other) noexcept
    : Quark(std::move(other)) {}

// Destructor
Up::~Up() {}

// Copy assignment operator
Up &Up::operator=(const Up &other)
{
  if(this != &other)
  {
    Quark::operator=(other);
  }
  return *this;
}

// Move assignment operator
Up &Up::operator=(Up &&other) noexcept
{
  if(this != &other)
  {
    Quark::operator=(std::move(other));
  }
  return *this;
} 








