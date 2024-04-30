#ifndef PARTICLE_H
#define PARTICLE_H

#include <memory> // For std::unique_ptr
#include <vector> // For std::vector
#include <string> // For std::string

#include "FourMomentum.h"

namespace Mass
{
  constexpr double electron = 0.511;
  constexpr double muon = 105.7;
  constexpr double tau = 1777;
  constexpr double electron_neutrino = 2.2e-6;
  constexpr double muon_neutrino = 0.17;
  constexpr double tau_neutrino = 15.5;

  constexpr double w = 80400;
  constexpr double z = 91200;
  constexpr double higgs = 126000;

  constexpr double up = 2.3;
  constexpr double down = 4.8;
  constexpr double charm = 1275;
  constexpr double bottom = 4180;
  constexpr double top = 173070;
  constexpr double strange = 95;
}

enum class DecayType
{
  Weak,
  Strong,
  Electromagnetic,
  None
};

enum class Colour
{
  Red,
  Green,
  Blue,
  AntiRed,
  AntiGreen,
  AntiBlue,
  None
};

class Particle
{
private:
  std::string type;  // Type of particle e.g 'electron', 'muon' ...
  std::string label; // Optional label of particle
  double charge;     // Charge of the particle
  double spin;       // Spin of particle
  double rest_mass;  // Rest mass of particle
  bool is_virtual = false;   // If particle is virtual - don't have to make checks on invariant mass and rest mass

  std::vector<DecayType> possible_decay_types;
  DecayType current_decay_type;
  std::vector<std::unique_ptr<Particle>> decay_products;
  bool validate_decay_products(const std::vector<std::unique_ptr<Particle>> &decay_products, DecayType decay_type) const;
  void auto_set_decay_products_virtual(std::vector<std::unique_ptr<Particle>> decay_products, DecayType decay_type);

protected:
  // Protected attribute so that derived classes can access four momentum object
  std::unique_ptr<FourMomentum> four_momentum;
  // Constructor without label
  Particle(std::string type, double charge, double spin, double rest_mass, std::unique_ptr<FourMomentum> four_momentum, std::vector<DecayType> possible_decay_types = {DecayType::None});
  // Constructor with label
  Particle(std::string type, const std::string &label, double charge, double spin, double rest_mass, std::unique_ptr<FourMomentum> fourMomentum, std::vector<DecayType> possible_decay_types = {DecayType::None});
  // Function to check if invariant mass of four momentum matches rest mass
  bool is_invariant_mass_valid(double invariant_mass) const;

public:
  // Default constructor
  Particle();

  // Parameterized constructors
  // Constructor without label
  Particle(std::string type, double charge, double spin, double rest_mass, std::vector<DecayType> possible_decay_types = {DecayType::None});
  // Constructor with label
  Particle(std::string type, const std::string &label, double charge, double spin, double rest_mass, std::vector<DecayType> possible_decay_types = {DecayType::None});

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

  // Setters
  void set_label(const std::string &label);
  void set_decay_products(std::vector<std::unique_ptr<Particle>> decay_products, DecayType decay_type);
  void auto_set_decay_products(std::vector<std::unique_ptr<Particle>> decay_products, DecayType decay_type);
  void set_is_virtual(bool is_virtual);
  // void set_four_momentum(std::unique_ptr<FourMomentum> fourMomentum);
  virtual void set_four_momentum(std::unique_ptr<FourMomentum> fourMomentum);

  // Getters
  std::string get_label() const;
  double get_charge() const;
  double get_spin() const;
  double get_rest_mass() const;
  std::string get_type() const;
  const FourMomentum &get_four_momentum() const;
  const std::vector<std::unique_ptr<Particle>> &get_decay_products() const;
  bool get_is_virtual();

  // Virtual methods
  virtual int get_lepton_number() const { return 0; }
  virtual double get_baryon_number() const { return 0; }
  virtual Colour get_colour_charge() const { return Colour::None; }
  virtual std::string get_flavour() const { return "none"; }

  // Friend functions
  friend FourMomentum sum_four_momentum(const Particle &a, const Particle &b);
  friend double dot_product_four_momentum(const Particle &a, const Particle &b);

  // Lorentz boost functions
  void lorentz_boost(long double v_x, long double v_y, long double v_z);
  void lorentz_boost(std::vector<long double> v_xyz);

  // Virtual print function
  virtual void print() const;
};

#endif // PARTICLE_H