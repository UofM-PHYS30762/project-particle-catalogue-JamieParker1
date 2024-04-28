#ifndef QUARK_TEMPLATE_H
#define QUARK_TEMPLATE_H

#include "Quark.h"
#include "../FourMomentum.h"
#include "QuarkName.h"
#include <cstdint>

template<typename Derived, typename Name, std::intmax_t ChargeNum, std::intmax_t ChargeDen, std::intmax_t MassNum, std::intmax_t MassDen>
class QuarkTemplate : public Quark
{
public:
  // Constructors
  QuarkTemplate(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
      : Quark(Name::name, (anti) ? -static_cast<double>(ChargeNum) / static_cast<double>(ChargeDen) : static_cast<double>(ChargeNum) / static_cast<double>(ChargeDen), static_cast<double>(MassNum) / static_cast<double>(MassDen), std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

  QuarkTemplate(const std::string &label, bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
      : Quark(Name::name, label, (anti) ? -static_cast<double>(ChargeNum) / static_cast<double>(ChargeDen) : static_cast<double>(ChargeNum) / static_cast<double>(ChargeDen), static_cast<double>(MassNum) / static_cast<double>(MassDen), std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

  // Default constructor
  QuarkTemplate(bool anti = false, Colour colour_charge = Colour::Red)
      : Quark(Name::name, (anti) ? -static_cast<double>(ChargeNum) / static_cast<double>(ChargeDen) : static_cast<double>(ChargeNum) / static_cast<double>(ChargeDen), static_cast<double>(MassNum) / static_cast<double>(MassDen), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

  // Special member functions
  QuarkTemplate(const Derived &other) : Quark(other) {}
  QuarkTemplate(Derived &&other) noexcept : Quark(std::move(other)) {}
  ~QuarkTemplate() {}
  Derived &operator=(const Derived &other)
  {
    if (this != &other)
      Quark::operator=(other);
    return static_cast<Derived&>(*this);
  }
  Derived &operator=(Derived &&other) noexcept
  {
    if (this != &other)
      Quark::operator=(std::move(other));
    return static_cast<Derived&>(*this);
  }
};

#endif // QUARK_TEMPLATE_H