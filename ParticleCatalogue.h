#ifndef PARTICLE_CATALOGUE_H
#define PARTICLE_CATALOGUE_H

#include "Particle.h"
#include <vector>
#include <iostream>
#include <map>
#include <typeinfo>
#include <typeindex>

template <typename T>
class ParticleCatalogue
{
private:
  std::vector<T *> particles;

public:
  ParticleCatalogue() = default;

  ~ParticleCatalogue()
  {
    for (auto &particle : particles)
    {
      delete particle;
    }
    particles.clear();
  }

  void addParticle(T *particle)
  {
    particles.push_back(particle);
  }

  void printAll() const
  {
    for (const auto &particle : particles)
    {
      particle->print();
    }
  }
  
  // Get the total number of particles
  size_t getTotalNumberOfParticles() const
  {
    return particles.size();
  }

  // Get number of particles of each type
  std::map<std::type_index, int> getParticleCountByType() const
  {
    std::map<std::type_index, int> counts;
    for (const auto &particle : particles)
    {
      counts[typeid(*particle)]++;
    }
    return counts;
  }

  // Sum the four-momentum of all particles
  FourMomentum sumFourMomenta() const
  {
    FourMomentum total;
    for (const auto &particle : particles)
    {
      total += particle->getFourMomentum();
    }
    return total;
  }

  // Get a sub-container of pointers to particles of the same kind
  template <typename SubType>
  std::vector<SubType *> getSubContainer() const
  {
    std::vector<SubType *> subContainer;
    for (auto &particle : particles)
    {
      SubType *casted = dynamic_cast<SubType *>(particle);
      if (casted)
      {
        subContainer.push_back(casted);
      }
    }
    return subContainer;
  }

  // Print information about one or more particles
  template <typename SubType>
  void printInfoByType() const
  {
    for (const auto &particle : particles)
    {
      SubType *casted = dynamic_cast<SubType *>(particle);
      if (casted)
      {
        casted->print();
      }
    }
  }
};

#endif
