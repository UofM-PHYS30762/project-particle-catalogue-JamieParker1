#ifndef BOSON_H
#define BOSON_H

#include <memory> // For std::unique_ptr
#include <vector> // For std::vector
#include <string> // For std::string

#include "../Particle.h"

class Boson : public Particle
{
private:
  
protected:
  // Constructor without label
  Boson(std::string type, int charge, double rest_mass, int spin, std::unique_ptr<FourMomentum> fourMomentum, std::vector<DecayType> possible_decay_types = std::vector<DecayType>{DecayType::None});
  // Constructor with label
  Boson(std::string type, const std::string &label, int charge, double rest_mass, int spin, std::unique_ptr<FourMomentum> fourMomentum, std::vector<DecayType> possible_decay_types = std::vector<DecayType>{DecayType::None});

public:
  // Default constructor
  Boson();
  // Parameterized constructors
  // Constructor without label
  Boson(std::string type, int charge, double rest_mass, int spin, std::vector<DecayType> possible_decay_types = std::vector<DecayType>{DecayType::None});
  // Constructor with label
  Boson(std::string type, const std::string &label, int charge, double rest_mass, int spin, std::vector<DecayType> possible_decay_types = std::vector<DecayType>{DecayType::None});

  // Copy constructor
  Boson(const Boson &other);

  // Move constructor
  Boson(Boson &&other) noexcept;

  // Virtual destructor
  virtual ~Boson();

  // Copy assignment operator
  Boson &operator=(const Boson &other);

  // Move assignment operator
  Boson &operator=(Boson &&other) noexcept;

  // Virtual print function
  virtual void print() const override;

  // Lepton number getter
};

#endif // BOSON_H