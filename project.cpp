#include "FourMomentum.h"
#include "Particle.h"
#include "Lepton.h"
#include "Electron.h"

int main()
{
  Particle p1 = Particle("Electron", 1, 1/2, 0.511);
  Particle p2 = Particle("Electron", 1, 1/2, 0.511);
  p1.set_four_momentum(std::make_unique<FourMomentum>(0.511,0,0,0));
  std::cout << p1.get_four_momentum() << std::endl;


  Electron electron = Electron("Electron 1", 
                               std::make_unique<FourMomentum>(0.511,0,0,0), 
                               std::vector<double>{0.1, 0.1, 0.2, 0.111});
  std::cout << electron.get_four_momentum() << std::endl;


  FourMomentum f = FourMomentum(1,0,0,0);
  FourMomentum t = FourMomentum(2,0,0,0);
  std::cout << f+t << std::endl << f-t << std::endl << f*t;
  return 0;
}
