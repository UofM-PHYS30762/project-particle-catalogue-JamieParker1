#include "Strange.h"
#include <utility>   // For std::move


// Constructor without label with validity check
Strange::Strange(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
    : Quark("strange", (anti) ? 1.0/3.0 : -1.0/3.0, 95, std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

// Constructor with label with validity check
Strange::Strange(const std::string &label, bool anti,  Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
    : Quark("strange", label, (anti) ? 1.0/3.0 : -1.0/3.0, 95, std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

//Default constructor
Strange::Strange(bool anti, Colour colour_charge) : Quark("strange", (anti) ? 1.0/3.0 : -1.0/3.0, 95, (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

// Copy constructor
Strange::Strange(const Strange &other)
    : Quark(other) {}

// Move constructor 
Strange::Strange(Strange &&other) noexcept
    : Quark(std::move(other)) {}

// Destructor
Strange::~Strange() {}

// Copy assignment operator
Strange &Strange::operator=(const Strange &other)
{
  if(this != &other)
  {
    Quark::operator=(other);
  }
  return *this;
}

// Move assignment operator
Strange &Strange::operator=(Strange &&other) noexcept
{
  if(this != &other)
  {
    Quark::operator=(std::move(other));
  }
  return *this;
} 








