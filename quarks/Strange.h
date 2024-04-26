#ifndef STRANGE_H
#define STRANGE_H

#include "Quark.h"
#include "../FourMomentum.h"
 
// Strange class 
class Strange : public Quark
{
public:
  // Constructors
  Strange(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum);
  Strange(const std::string &label, bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum);
  // Default constructor
  Strange(bool anti = false, Colour colour_charge = Colour::Red);

  // Special member functions
  Strange(const Strange &other);                // Copy constructor
  Strange(Strange &&other) noexcept;            // Move constructor
  ~Strange();                                    // Destructor
  Strange &operator=(const Strange &other);     // Copy assignment operator
  Strange &operator=(Strange &&other) noexcept; // Move assignment operator
};

#endif // DOWN_H


