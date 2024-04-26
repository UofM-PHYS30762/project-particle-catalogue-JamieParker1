#ifndef DOWN_H
#define DOWN_H

#include "Quark.h"
#include "../FourMomentum.h"
 
// Down class 
class Down : public Quark
{
public:
  // Constructors
  Down(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum);
  Down(const std::string &label, bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum);
  // Default constructor
  Down(bool anti = false, Colour colour_charge = Colour::Red);

  // Special member functions
  Down(const Down &other);                // Copy constructor
  Down(Down &&other) noexcept;            // Move constructor
  ~Down();                                    // Destructor
  Down &operator=(const Down &other);     // Copy assignment operator
  Down &operator=(Down &&other) noexcept; // Move assignment operator
};

#endif // DOWN_H


