#ifndef BOTTOM_H
#define BOTTOM_H

#include "Quark.h"
#include "../FourMomentum.h"
 
// Bottom class 
class Bottom : public Quark
{
public:
  // Constructors
  Bottom(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum);
  Bottom(const std::string &label, bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum);
  // Default constructor
  Bottom(bool anti = false, Colour colour_charge = Colour::Red);

  // Special member functions
  Bottom(const Bottom &other);                // Copy constructor
  Bottom(Bottom &&other) noexcept;            // Move constructor
  ~Bottom();                                    // Destructor
  Bottom &operator=(const Bottom &other);     // Copy assignment operator
  Bottom &operator=(Bottom &&other) noexcept; // Move assignment operator
};

#endif // DOWN_H


