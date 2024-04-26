#ifndef CHARM_H
#define CHARM_H

#include "Quark.h"
#include "../FourMomentum.h"
 
// Charm class 
class Charm : public Quark
{
public:
  // Constructors
  Charm(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum);
  Charm(const std::string &label, bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum);
  // Default constructor
  Charm(bool anti = false, Colour colour_charge = Colour::Red);

  // Special member functions
  Charm(const Charm &other);                // Copy constructor
  Charm(Charm &&other) noexcept;            // Move constructor
  ~Charm();                                    // Destructor
  Charm &operator=(const Charm &other);     // Copy assignment operator
  Charm &operator=(Charm &&other) noexcept; // Move assignment operator
};

#endif // CHARM_H


