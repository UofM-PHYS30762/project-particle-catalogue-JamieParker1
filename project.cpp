#include "FourMomentum.h"
#include "Particle.h"
#include "Lepton.h"
#include "Electron.h"
#include "Muon.h"

int main()
{
  Particle p1 = Particle("Electron", 1, 1 / 2, 0.511);
  Particle p2 = Particle("Electron", 1, 1 / 2, 0.511);
  p1.set_four_momentum(std::make_unique<FourMomentum>(0.511, 0, 0, 0));
  std::cout << p1.get_four_momentum() << std::endl;

  Lepton lep = Lepton("Electron", "Electron 1", -1, 0.511, 1);
  try
  {
    const FourMomentum &fm = p2.get_four_momentum();
    // Use the four momentum for further calculations or display
    std::cout << "Four momentum retrieved successfully." << std::endl;
    std::cout << "Energy: " << fm.get_energy() << ", Px: " << fm.get_Px() << ", Py: " << fm.get_Py() << ", Pz: " << fm.get_Pz() << std::endl;
  }
  catch (const std::runtime_error& e) {
    std::cerr << "Runtime error: " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "An unknown error occurred." << std::endl;
  }


  FourMomentum f = FourMomentum(1, 0, 0, 0);
  FourMomentum t = FourMomentum(2, 0, 0, 0);
  std::cout << f + t << std::endl
            << f - t << std::endl
            << f * t;
  return 0;
}
