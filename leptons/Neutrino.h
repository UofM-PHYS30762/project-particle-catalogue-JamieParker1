#ifndef NEUTRINO_H
#define NEUTRINO_H

#include "Lepton.h"
#include "../FourMomentum.h"
#include <vector>
#include <string>

// Neutrino class
class Neutrino : public Lepton
{
private:
  std::string flavour; 
  bool has_interacted; 

public:
  // Constructors
  Neutrino(std::unique_ptr<FourMomentum> four_momentum, std::string flavour, bool has_interacted, int lepton_number);
  Neutrino(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, std::string flavour, bool has_interacted, int lepton_number);
  // Default constructor
  Neutrino();

  // Special member functions
  Neutrino(const Neutrino &other);                // Copy constructor
  Neutrino(Neutrino &&other) noexcept;            // Move constructor
  ~Neutrino();                                    // Destructor
  Neutrino &operator=(const Neutrino &other);     // Copy assignment operator
  Neutrino &operator=(Neutrino &&other) noexcept; // Move assignment operator

  // Getters and Setters
  void set_has_interacted(bool has_interacted);
  void set_flavour(std::string flavour);

  std::string get_flavour() const;
  bool get_has_interacted() const;

  // Virtual function overrides
  virtual void print() const override;
};

#endif // NEUTRINO_H
 