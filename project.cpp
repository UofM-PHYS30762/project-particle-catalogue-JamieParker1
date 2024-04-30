#include "FourMomentum.h"
#include "Particle.h"
#include "ParticleCatalogue.h"

#include "showcase.h"
#include "user_interface.h"

#include "leptons/Lepton.h"
#include "leptons/Electron.h"
#include "leptons/Muon.h"
#include "leptons/Tau.h"
#include "leptons/Neutrino.h"

#include "bosons/Boson.h"
#include "bosons/Photon.h"
#include "bosons/Gluon.h"
#include "bosons/Z.h"
#include "bosons/W.h"
#include "bosons/Higgs.h"

#include "quarks/Quark.h"
#include "quarks/QuarkTemplate.h"
#include "quarks/IndividualQuarks.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>



int main()
{
  // ParticleCatalogue<Particle> catalogue;
  // Photon *p = new Photon();
  // Higgs *h = new Higgs();
  // Electron *e = new Electron();
  // e->set_label("HERE");
  // h->set_label("HERE");
  // catalogue.add_particle(p);
  // catalogue.add_particle(h);
  // catalogue.add_particle(e);

  // std::vector<Particle*> heres = catalogue.find_particles_by_label("HERE");
  // heres[0]->print();
  // size_t remove_index = 0;
  // catalogue.remove_particle(remove_index);
  // std::cout << "___________________________" << std::endl;
  // catalogue.print_all();
  // catalogue.remove_particle(e);
  // std::cout << "___________________________" << std::endl;
  // catalogue.print_all();
  // std::cout << "___________________________" << std::endl;
  // catalogue.remove_particle("HERE");
  // catalogue.print_all();

  // catalogue.apply_function_to_particles<void (Particle::*)(const std::string&), const char*>(&Particle::set_label, "random label", std::vector<std::string>{"HERE"});

  // catalogue.apply_function_to_particles<Lepton>(&Lepton::set_label, "1");
  // catalogue.print_all();

  ParticleCatalogue<Particle> user_catalogue;
  fill_catalogue(user_catalogue);
  main_menu_navigation(user_catalogue);



  // wait_for_enter("Hit Enter to continue to Class Hierachy Showcase:");
  // showcase_basic_class_hierarchy();
  // wait_for_enter();
  // showcase_four_momentum_class();
  // wait_for_enter();
  // showcase_particle_attributes();
  // wait_for_enter();
  // showcase_decay_product_functionality();
  // showcase_particle_catalogue();

  return 0;
}
