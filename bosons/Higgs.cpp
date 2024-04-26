#include "Higgs.h"
#include "../helper_functions.h"
#include <utility>   // For std::move

// Constructor without label 
Higgs::Higgs(std::unique_ptr<FourMomentum> four_momentum)
    : Boson("higgs", 0, 126000, 0, std::move(four_momentum), std::vector<DecayType>{DecayType::Hadronic, DecayType::Leptonic, DecayType::Electromagnetic}) {}

// Constructor with label 
Higgs::Higgs(const std::string &label, std::unique_ptr<FourMomentum> four_momentum)
    : Boson("higgs", label, 0, 126000, 0, std::move(four_momentum), std::vector<DecayType>{DecayType::Hadronic, DecayType::Leptonic, DecayType::Electromagnetic}) {}

// Default constructor
Higgs::Higgs() : Boson("higgs", 0, 126000, 0, std::vector<DecayType>{DecayType::Hadronic, DecayType::Leptonic, DecayType::Electromagnetic}) {}

// Copy constructor
Higgs::Higgs(const Higgs &other)
    : Boson(other) {}

// Move constructor
Higgs::Higgs(Higgs &&other) noexcept
    : Boson(std::move(other)) {}

// Destructor
Higgs::~Higgs() {}

// Copy assignment operator
Higgs &Higgs::operator=(const Higgs &other)
{
  if (this != &other)
  {
    Boson::operator=(other);
  }
  return *this;
}

// Move assignment operator
Higgs &Higgs::operator=(Higgs &&other) noexcept
{
  if (this != &other)
  {
    Boson::operator=(std::move(other));
  }
  return *this;
}

// Override the print function
void Higgs::print() const
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

