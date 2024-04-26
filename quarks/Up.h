#ifndef UP_H
#define UP_H

#include "Quark.h"
#include "../FourMomentum.h"
 
// Up class 
class Up : public Quark
{
public:
  // Constructors
  Up(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum);
  Up(const std::string &label, bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum);
  // Default constructor
  Up(bool anti = false, Colour colour_charge = Colour::Red);

  // Special member functions
  Up(const Up &other);                // Copy constructor
  Up(Up &&other) noexcept;            // Move constructor
  ~Up();                                    // Destructor
  Up &operator=(const Up &other);     // Copy assignment operator
  Up &operator=(Up &&other) noexcept; // Move assignment operator
};

#endif // DOWN_H


