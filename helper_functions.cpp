#include "helper_functions.h"

std::string to_string(Colour colour)
{
  switch (colour)
  {
  case Colour::Red:
    return "Red";
  case Colour::Green:
    return "Green";
  case Colour::Blue:
    return "Blue";
  case Colour::AntiRed:
    return "AntiRed";
  case Colour::AntiGreen:
    return "AntiGreen";
  case Colour::AntiBlue:
    return "AntiBlue";
    case Colour::None:
    return "None";
  default:
    return "Unknown Colour";
  }
}

std::string to_string(DecayType decay_type)
{
  switch (decay_type)
  {
  case DecayType::Leptonic:
    return "Leptonic";
  case DecayType::Hadronic:
    return "Hadronic";
  case DecayType::Electromagnetic:
    return "Electromagnetic";
  case DecayType::None:
    return "None";
  default:
    return "Unknown Decay type";
  }
}

bool is_anti_colour(Colour colour)
{
  switch (colour)
  {
  case Colour::Red:
    return false;
  case Colour::Green:
    return false;
  case Colour::Blue:
    return false;
  case Colour::AntiRed:
    return true;
  case Colour::AntiGreen:
    return true;
  case Colour::AntiBlue:
    return true;
  case Colour::None:
    throw std::invalid_argument("Error: Cannot have AntiNone Colour");
  default:
    throw std::invalid_argument("Error: Unrecognised Colour");
  }
}

bool contains_decay_type(const std::vector<DecayType> &decay_types, DecayType type_to_find)
{
  // Iterate over the vector to check if the given type is present
  for (const auto &type : decay_types)
  {
    if (type == type_to_find)
    {
      return true;
    }
  }
  return false;
}

// Function to calculate the sum of energies of products 1 and 2 given a momentum 
double energy_sum(double momentum, double product1_rest_mass, double product2_rest_mass)
{
  double E1 = sqrt(product1_rest_mass * product1_rest_mass + momentum * momentum);
  double E2 = sqrt(product2_rest_mass * product2_rest_mass + momentum * momentum);
  return E1 + E2;
}

// Function to perform the bisection method to find the momentum of two decay particles
double find_momentum_of_products(double product1_rest_mass, double product2_rest_mass, double decay_particle_rest_mass, double tolerance)
{
  double low = 0.0;
  double high = decay_particle_rest_mass;
  double mid;

  while (high - low > tolerance)
  {
    mid = (low + high) / 2;
    double total_product_energy = energy_sum(mid, product1_rest_mass, product2_rest_mass);

    if (total_product_energy > decay_particle_rest_mass)
      high = mid;
    else
      low = mid;
  }
  return (low + high) / 2;
}