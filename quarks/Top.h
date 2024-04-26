#ifndef TOP_H
#define TOP_H

#include "Quark.h"
#include "../FourMomentum.h"
 
// Top class 
class Top : public Quark
{
public:
  // Constructors
  Top(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum);
  Top(const std::string &label, bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum);
  // Default constructor
  Top(bool anti = false, Colour colour_charge = Colour::Red);

  // Special member functions
  Top(const Top &other);                // Copy constructor
  Top(Top &&other) noexcept;            // Move constructor
  ~Top();                                    // Destructor
  Top &operator=(const Top &other);     // Copy assignment operator
  Top &operator=(Top &&other) noexcept; // Move assignment operator
};

#endif // DOWN_H


