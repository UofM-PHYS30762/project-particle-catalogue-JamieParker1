#ifndef FOURMOMENTUM_H
#define FOURMOMENTUM_H

#include <cmath>
#include <iostream>
#include <vector>

class FourMomentum 
{
private:
  // double energy;     // Energy component E
  long double energy;     // Energy component E

  // double px, py, pz; // Momentum components along the x, y, and z axes
  long double px, py, pz; // Momentum components along the x, y, and z axes

public:
  // Constructor to initialize the four-momentum components
  // FourMomentum(double energy = 0.0, double px = 0.0, double py = 0.0, double pz = 0.0, bool energy_is_rest_mass = false);
  FourMomentum(long double energy = 0.0, long double px = 0.0, long double py = 0.0, long double pz = 0.0, bool energy_is_rest_mass = false);

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
  double get_velocity_magnitude() const; // In units of C
  double get_velocity_x() const;
  double get_velocity_y() const;
  double get_velocity_z() const;
  std::vector<double> get_velocity_vector() const;

  // Function to calculate the invariant mass (magnitude) of the four-momentum
  double invariant_mass() const;
  // Function to perform Lorentz boost to four-momentum
  // void lorentz_boost(double v_x, double v_y, double v_z);
  void lorentz_boost(long double v_x, long double v_y, long double v_z);
  void lorentz_boost(std::vector<double> v_xyz);

  // Overloaded operators
  FourMomentum operator+(const FourMomentum& rhs) const; // Addition
  FourMomentum operator-(const FourMomentum& rhs) const; // Subtraction
  double operator*(const FourMomentum& rhs) const;       // Dot product
};

// Overloaded << operator declaration
std::ostream &operator<<(std::ostream &os, const FourMomentum &fm);

#endif // FOURMOMENTUM_H
