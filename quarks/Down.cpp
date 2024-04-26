#include "Down.h"
#include <utility>   // For std::move


// Constructor without label with validity check
Down::Down(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
    : Quark("down", (anti) ? 1.0/3.0 : -1.0/3.0, 4.8, std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

// Constructor with label with validity check
Down::Down(const std::string &label, bool anti,  Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
    : Quark("down", label, (anti) ? 1.0/3.0 : -1.0/3.0, 4.8, std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

//Default constructor
Down::Down(bool anti, Colour colour_charge) : Quark("down", (anti) ? 1.0/3.0 : -1.0/3.0, 4.8, (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

// Copy constructor
Down::Down(const Down &other)
    : Quark(other) {}

// Move constructor 
Down::Down(Down &&other) noexcept
    : Quark(std::move(other)) {}

// Destructor
Down::~Down() {}

// Copy assignment operator
Down &Down::operator=(const Down &other)
{
  if(this != &other)
  {
    Quark::operator=(other);
  }
  return *this;
}

// Move assignment operator
Down &Down::operator=(Down &&other) noexcept
{
  if(this != &other)
  {
    Quark::operator=(std::move(other));
  }
  return *this;
} 








