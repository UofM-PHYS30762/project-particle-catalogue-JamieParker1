#include "Top.h"
#include <utility>   // For std::move


// Constructor without label with validity check
Top::Top(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
    : Quark("top", (anti) ? -2.0/3.0 : 2.0/3.0, 173070, std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

// Constructor with label with validity check
Top::Top(const std::string &label, bool anti,  Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
    : Quark("top", label, (anti) ? -2.0/3.0 : 2.0/3.0, 173070, std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

//Default constructor
Top::Top(bool anti, Colour colour_charge) : Quark("top", (anti) ? -2.0/3.0 : 2.0/3.0, 173070, (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

// Copy constructor
Top::Top(const Top &other)
    : Quark(other) {}

// Move constructor 
Top::Top(Top &&other) noexcept
    : Quark(std::move(other)) {}

// Destructor
Top::~Top() {}

// Copy assignment operator
Top &Top::operator=(const Top &other)
{
  if(this != &other)
  {
    Quark::operator=(other);
  }
  return *this;
}

// Move assignment operator
Top &Top::operator=(Top &&other) noexcept
{
  if(this != &other)
  {
    Quark::operator=(std::move(other));
  }
  return *this;
} 








