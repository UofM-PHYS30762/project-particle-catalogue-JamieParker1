#include "Bottom.h"
#include <utility>   // For std::move


// Constructor without label with validity check
Bottom::Bottom(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
    : Quark("bottom", (anti) ? 1.0/3.0 : -1.0/3.0, 4180, std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

// Constructor with label with validity check
Bottom::Bottom(const std::string &label, bool anti,  Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
    : Quark("bottom", label, (anti) ? 1.0/3.0 : -1.0/3.0, 4180, std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

//Default constructor
Bottom::Bottom(bool anti, Colour colour_charge) : Quark("bottom", (anti) ? 1.0/3.0 : -1.0/3.0, 4180, (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

// Copy constructor
Bottom::Bottom(const Bottom &other)
    : Quark(other) {}

// Move constructor 
Bottom::Bottom(Bottom &&other) noexcept
    : Quark(std::move(other)) {}

// Destructor
Bottom::~Bottom() {}

// Copy assignment operator
Bottom &Bottom::operator=(const Bottom &other)
{
  if(this != &other)
  {
    Quark::operator=(other);
  }
  return *this;
}

// Move assignment operator
Bottom &Bottom::operator=(Bottom &&other) noexcept
{
  if(this != &other)
  {
    Quark::operator=(std::move(other));
  }
  return *this;
} 








