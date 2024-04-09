#include "FourMomentum.h"

// Constructor
FourMomentum::FourMomentum(double energy, double px, double py, double pz)
    : energy(energy), px(px), py(py), pz(pz) {}


// Copy constructor
FourMomentum::FourMomentum(const FourMomentum &other)
    : energy(other.energy), px(other.px), py(other.py), pz(other.pz) {}

// Move constructor
FourMomentum::FourMomentum(FourMomentum &&other) noexcept
    : energy(std::move(other.energy)), px(std::move(other.px)), py(std::move(other.py)), pz(std::move(other.pz)) {}

// Copy assignment operator
FourMomentum &FourMomentum::operator=(const FourMomentum &other)
{
  if (this != &other)
  { // Protect against self-assignment
    energy = other.energy;
    px = other.px;
    py = other.py;
    pz = other.pz;
  }
  return *this;
}

// Move assignment operator
FourMomentum &FourMomentum::operator=(FourMomentum &&other) noexcept
{
  if (this != &other)
  {
    energy = std::move(other.energy);
    px = std::move(other.px);
    py = std::move(other.py);
    pz = std::move(other.pz);
    // Optionally, reset the moved-from object's state if needed
  }
  return *this;
}

// Destructor
FourMomentum::~FourMomentum() {}

// Setters
void FourMomentum::set_energy(double energy)
{
  this->energy = energy;
}

void FourMomentum::set_momentum(double px, double py, double pz)
{
  this->px = px;
  this->py = py;
  this->pz = pz;
}

// Getters
double FourMomentum::get_energy() const
{
  return energy;
}

double FourMomentum::get_Px() const
{
  return px;
}

double FourMomentum::get_Py() const
{
  return py;
}

double FourMomentum::get_Pz() const
{
  return pz;
}

// Function to calculate the invariant mass
double FourMomentum::invariant_mass() const
{
  return sqrt(std::max(0.0, energy * energy - (px * px + py * py + pz * pz)));
}

// Overloaded operator+ for addition
FourMomentum FourMomentum::operator+(const FourMomentum &rhs) const
{
  return FourMomentum(energy + rhs.energy, px + rhs.px, py + rhs.py, pz + rhs.pz);
}

// Overloaded operator- for subtraction
FourMomentum FourMomentum::operator-(const FourMomentum &rhs) const
{
  return FourMomentum(energy - rhs.energy, px - rhs.px, py - rhs.py, pz - rhs.pz);
}

// Overloaded operator* for dot product
double FourMomentum::operator*(const FourMomentum &rhs) const
{
  return energy * rhs.energy - (px * rhs.px + py * rhs.py + pz * rhs.pz);
}

// Overloaded << operator for printing
std::ostream &operator<<(std::ostream &os, const FourMomentum &fm)
{
  os << "Energy: " << fm.get_energy() << ", Px: " << fm.get_Px() << ", Py: " << fm.get_Py() << ", Pz: " << fm.get_Pz();
  return os;
}