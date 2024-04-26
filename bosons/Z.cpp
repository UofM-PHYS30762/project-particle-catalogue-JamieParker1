#include "Z.h"
#include "../helper_functions.h"
#include <utility>   // For std::move

// Constructor without label 
Z::Z(std::unique_ptr<FourMomentum> four_momentum)
    : Boson("z", 0, 91200, 1, std::move(four_momentum), std::vector<DecayType>{DecayType::Hadronic, DecayType::Leptonic}) {}

// Constructor with label 
Z::Z(const std::string &label, std::unique_ptr<FourMomentum> four_momentum)
    : Boson("z", label, 0, 91200, 1, std::move(four_momentum), std::vector<DecayType>{DecayType::Hadronic, DecayType::Leptonic}) {}

// Default constructor
Z::Z() : Boson("z", 0, 91200, 1, std::vector<DecayType>{DecayType::Hadronic, DecayType::Leptonic}) {}

// Copy constructor
Z::Z(const Z &other)
    : Boson(other) {}

// Move constructor
Z::Z(Z &&other) noexcept
    : Boson(std::move(other)) {}

// Destructor
Z::~Z() {}

// Copy assignment operator
Z &Z::operator=(const Z &other)
{
  if (this != &other)
  {
    Boson::operator=(other);
  }
  return *this;
}

// Move assignment operator
Z &Z::operator=(Z &&other) noexcept
{
  if (this != &other)
  {
    Boson::operator=(std::move(other));
  }
  return *this;
}

// Override the print function
void Z::print() const
{
  Boson::print(); // Print the base class attributes
  if (!this->get_decay_products().empty())
  {
    std::cout << "\033[1mDecay Products:\033[0m" << std::endl;
    for (const auto& product : this->get_decay_products()) 
    {
      product->print();
    }
  }
  else
  {
    std::cout << "\033[1mNo Decay Products\033[0m" << std::endl;
  }
}

