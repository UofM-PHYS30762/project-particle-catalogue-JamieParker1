#include "FourMomentum.h"
#include "Particle.h"

int main()
{
  FourMomentum f = FourMomentum(1,0,0,0);
  FourMomentum t = FourMomentum(2,0,0,0);
  std::cout << f+t << std::endl << f-t << std::endl << f*t;
  return 0;
}