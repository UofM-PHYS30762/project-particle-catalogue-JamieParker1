#ifndef FOURMOMENTUM_H
#define FOURMOMENTUM_H

#include <cmath>
#include <iostream>

class FourMomentum
{
private:
  double energy;     // Energy component E
  double px, py, pz; // Momentum components along the x, y, and z axes

public:
  // Constructor to initialize the four-momentum components
  FourMomentum(double energy = 0.0, double px = 0.0, double py = 0.0, double pz = 0.0);

  // Copy constructor, Move constructor, Copy assignment operator, Move assignment operator, and Destructor
  FourMomentum(const FourMomentum &other);                // Copy constructor
  FourMomentum(FourMomentum &&other) noexcept;            // Move constructor
  FourMomentum &operator=(const FourMomentum &other);     // Copy assignment operator
  FourMomentum &operator=(FourMomentum &&other) noexcept; // Move assignment operator
  ~FourMomentum();                                        // Destructor

  // Setters for the four-momentum components
  void set_energy(double energy);
  void set_momentum(double px, double py, double pz);

  // Getters for the four-momentum components
  double get_energy() const;
  double get_Px() const;
  double get_Py() const;
  double get_Pz() const;

  // Function to calculate the invariant mass (magnitude) of the four-momentum
  double invariant_mass() const;

  // Overloaded operators
  FourMomentum operator+(const FourMomentum& rhs) const; // Addition
  FourMomentum operator-(const FourMomentum& rhs) const; // Subtraction
  double operator*(const FourMomentum& rhs) const;       // Dot product
};

// Overloaded << operator declaration
std::ostream &operator<<(std::ostream &os, const FourMomentum &fm);

#endif // FOURMOMENTUM_H
