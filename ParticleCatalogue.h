
#ifndef PARTICLE_CATALOGUE_H
#define PARTICLE_CATALOGUE_H

#include "Particle.h"
#include <vector>
#include <iostream>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <set>
#include <algorithm>
#include <numeric>

template <typename T>
class ParticleCatalogue
{
private:
  std::vector<T *> particles;
  std::set<T *> unique_particles;

public:
  ParticleCatalogue() = default;

  ~ParticleCatalogue()
  {
    for (auto &particle : particles)
    {
      delete particle;
    }
    particles.clear();
    unique_particles.clear();
  }

  void add_particle(T *particle)
  {
    // Check if the particle pointer is already added
    if (unique_particles.find(particle) == unique_particles.end())
    {
      particles.push_back(particle);
      unique_particles.insert(particle); // Add to the set of unique pointers
    }
    else
    {
      std::cout << "Warning: Attempt to add a duplicate particle pointer.\n";
    }
  }

  void print_all() const
  {
    std::for_each(particles.begin(), particles.end(), [](const T *particle)
                  { particle->print(); });
  }

  // Get the total number of particles
  size_t get_number_of_particles() const
  {
    return particles.size();
  }

  // Get number of particles of each type
  std::map<std::string, int> get_particle_count_by_type() const
  {
    std::map<std::string, int> counts;
    std::for_each(particles.begin(), particles.end(), [&counts](const T *particle)
                  {
      // Get the type name as a string
      std::string typeName = typeid(*particle).name();

      // Remove the prefix if it exists
      size_t pos = typeName.find_first_not_of("0123456789");
      if (pos != std::string::npos)
      {
        typeName = typeName.substr(pos);
      }

      // Increment the count for the type
      counts[typeName]++; });
    return counts;
  }

  // Sum the four-momentum of all particles
  FourMomentum sum_four_momenta() const
  {
    return std::accumulate(particles.begin(), particles.end(), FourMomentum(), [](const FourMomentum &sum, const T *particle)
                           { return sum + particle->get_four_momentum(); });
  }

  // Get a sub-container of pointers to particles of the same kind
  template <typename SubType>
  std::vector<SubType *> get_sub_container() const
  {
    std::vector<SubType *> sub_container;
    std::copy_if(particles.begin(), particles.end(), std::back_inserter(sub_container), [](const T *particle)
                 { return dynamic_cast<SubType *>(particle) != nullptr; });
    return sub_container;
  }

  // Print information about one or more particles of same type
  template <typename SubType>
  void print_info_by_type() const
  {
    std::for_each(particles.begin(), particles.end(), [](const T *particle)
                  {
      const SubType *casted = dynamic_cast<const SubType *>(const_cast<T *>(particle));
      if (casted)
      {
        casted->print();
      } });
  }

  template <typename SubType>
  void print_info_by_exact_type() const
  {
    std::for_each(particles.begin(), particles.end(), [](const T *particle)
                  {
          if (typeid(*particle) == typeid(SubType))
          {
              particle->print();
          } });
  }
};

#endif
