#ifndef PARTICLE_H
#define PARTICLE_H

#include <memory> // For std::unique_ptr
#include <vector> // For std::vector
#include <string> // For std::string

#include "FourMomentum.h"

class Particle
{
private:
  std::string type;           // Type of particle e.g 'electron', 'muon' ...
  std::string label = "None"; // Optional label of particle
  int charge = 0;             // Charge of the particle
  double spin = 0.0;          // Spin of particle
  double rest_mass = 0.0;     // Rest mass of particle

  void check_mass_validity() const;

protected:
  // Protected attribute so that derived classes can access four momentum object
  std::unique_ptr<FourMomentum> four_momentum;
  // Constructor without label
  Particle(std::string type, int charge, double spin, double rest_mass, std::unique_ptr<FourMomentum> fourMomentum);
  // Constructor with label
  Particle(std::string type, const std::string &label, int charge, double spin, double rest_mass, std::unique_ptr<FourMomentum> fourMomentum);

public:
  // Default constructor
  Particle();

  // Parameterized constructors
  // Constructor without label
  Particle(std::string type, int charge, double spin, double rest_mass);
  // Constructor with label
  Particle(std::string type, const std::string &label, int charge, double spin, double rest_mass);

  // Copy constructor
  Particle(const Particle &other);

  // Move constructor
  Particle(Particle &&other) noexcept;

  // Virtual destructor
  virtual ~Particle();

  // Copy assignment operator
  Particle &operator=(const Particle &other);

  // Move assignment operator
  Particle &operator=(Particle &&other) noexcept;

  // Setters and getters
  void set_label(const std::string &label);
  std::string get_label() const;

  int get_charge() const;

  double get_spin() const;

  double get_rest_mass() const;

  std::string get_type() const;

  void set_four_momentum(std::unique_ptr<FourMomentum> fourMomentum);
  const FourMomentum &get_four_momentum() const;

  // Friend functions
  friend FourMomentum sum_four_momentum(const Particle &a, const Particle &b);
  friend double dot_product_four_momentum(const Particle &a, const Particle &b);

  // Virtual print function
  virtual void print() const;
};

#endif // LEPTON_H