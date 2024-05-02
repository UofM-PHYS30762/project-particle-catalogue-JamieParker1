#include "user_interface.h"

// Gets a valid number from user
double get_valid_number(const std::string &prompt, double minVal, double maxVal)
{
  double number;
  std::string input;
  while (true)
  {
    std::cout << prompt;
    std::getline(std::cin, input); // Read the whole line into a string

    std::stringstream ss(input);
    ss >> number;

    // Check if the entire input string was numeric and no characters are left after parsing the number
    // Also check if the extracted number falls within the specified range
    if (ss.fail() || !ss.eof() || number <= 0 || number <= minVal || number >= maxVal)
    {
      std::cout << "Invalid input.\n";
      continue;
    }
    return number;
  }
}

// Function to get integer input within a given range
int get_integer_input(const std::string &prompt, int min_value, int max_value)
{
  double number;
  std::string input;
  while (true)
  {
    std::cout << prompt;
    std::getline(std::cin, input); // Read the whole line into a string

    std::stringstream ss(input);
    if (!(ss >> number) || !ss.eof())
    {
      // Extraction failed or there are characters left after parsing
      std::cout << "Invalid input. Please enter a valid integer.\n";
      continue;
    }

    // Check if the fractional part is zero
    if (number - static_cast<int>(number) != 0)
    {
      std::cout << "Number must be an integer.\n";
      continue;
    }

    if (number < min_value || number > max_value)
    {
      // Number is out of range
      std::cout << "Number must be between " << min_value << " and " << max_value << ".\n";
      continue;
    }

    // Input is valid
    return static_cast<int>(number);
  }
}

std::string input_particle_type()
{
  std::cout << "==== Particles ====\n";
  std::cout << "1. General Particle Types\n";
  std::cout << "2. Specific Particles\n";

  int choice = get_integer_input("Enter your choice: ", 1, 2);
  int general_choice;
  switch (choice)
  {
  case 1:
    std::cout << "==== General Particle Types ====\n";
    std::cout << "1. All Particles\n";
    std::cout << "2. Leptons\n";
    std::cout << "3. Quarks\n";
    std::cout << "4. Bosons\n";
    general_choice = get_integer_input("Enter the general type: ", 1, 4);
    switch (general_choice)
    {
    case 1:
      return "particle";
    case 2:
      return "lepton";
    case 3:
      return "quark"; // Assuming W plus and minus share the same class
    case 4:
      return "boson";
    }
    break;
  case 2:
    return input_specific_particle_type();
  }
  return "particle";
}
std::string input_specific_particle_type()
{
  std::cout << "==== Particle Types ====\n";
  std::cout << "1. Bosons\n";
  std::cout << "2. Quarks\n";
  std::cout << "3. Leptons\n";

  int particle_type_choice = get_integer_input("Enter the particle type: ", 1, 3);
  int quark_choice;
  int lepton_choice;
  int boson_choice;
  switch (particle_type_choice)
  {
  case 1: // Bosons
    std::cout << "  ==== Bosons ====\n";
    std::cout << "  1. Photon\n";
    std::cout << "  2. Gluon\n";
    std::cout << "  3. W\n";
    std::cout << "  4. Z\n";
    std::cout << "  5. Higgs\n";

    boson_choice = get_integer_input("Enter the boson type: ", 1, 5);
    switch (boson_choice)
    {
    case 1:
      return "photon";
    case 2:
      return "gluon";
    case 3:
      return "w"; // Assuming W plus and minus share the same class
    case 4:
      return "z";
    case 5:
      return "higgs";
    }
    break;
  case 2: // Quarks
    std::cout << "  ==== Quarks ====\n";
    std::cout << "  1. Up\n";
    std::cout << "  2. Charm\n";
    std::cout << "  3. Top\n";
    std::cout << "  4. Down\n";
    std::cout << "  5. Strange\n";
    std::cout << "  6. Bottom\n";
    quark_choice = get_integer_input("Enter the quark type: ", 1, 6);
    switch (quark_choice)
    {
    case 1:
      return "up";
    case 2:
      return "charm";
    case 3:
      return "top";
    case 4:
      return "down";
    case 5:
      return "strange";
    case 6:
      return "bottom";
    }
    break;
  case 3: // Leptons
    std::cout << "  ==== Leptons ====\n";
    std::cout << "  1. Electron\n";
    std::cout << "  2. Muon\n";
    std::cout << "  3. Tau\n";
    std::cout << "  4. Neutrino\n";
    lepton_choice = get_integer_input("Enter the lepton type: ", 1, 4);
    switch (lepton_choice)
    {
    case 1:
      return "electron";
    case 2:
      return "muon";
    case 3:
      return "tau";
    case 4:
      return "neutrino";
    }
    break;
  }
  return "particle";
}

// Function to display the main menu
void display_main_menu()
{
  std::cout << "==== Main Menu ====\n";
  std::cout << "1. Default Program Showcase Menu\n";
  std::cout << "2. Custom Usage Menu\n";
  std::cout << "3. Help\n";
  std::cout << "4. Quit\n";
}
// Function to display options to showcase program
void display_program_showcase_menu()
{
  std::cout << "  ==== Program Showcase ====\n";
  std::cout << "  1. Full Showcase\n";
  std::cout << "  2. Basic Class Hierachy\n";
  std::cout << "  3. Particle Attributes\n";
  std::cout << "  4. Decay Product functionality\n";
  std::cout << "  5. Four Momentum\n";
  std::cout << "  6. Particle Catalogue\n";
  std::cout << "  7. Back\n";
}
// Function to display the custom usage menu
void display_custom_usage_menu(int sub_num)
{
  for (int j = 0; j <= sub_num; j++)
  {
    std::string indent = "    ";
    for (int i = 0; i < j; i++)
    {
      indent += "    ";
    }

    std::string header = indent + "==== Particle ";
    std::string two = indent + "2. Display ";
    for (int i = 0; i < j; i++)
    {
      header += "Sub-";
      two += "Sub-";
    }
    header += "Catalogue Menu ====\n";
    two += "Catalogue\n";

    std::string three = indent + "3. Get ";
    for (int i = 0; i < j + 1; i++)
    {
      three += "Sub-";
    }
    three += "Catalogue by particle type\n";

    std::cout << header;
    std::cout << indent + "1. Add Particles\n";
    std::cout << two;
    std::cout << three;
    std::cout << indent + "4. Back\n";

    std::cout << "\n"; // Add a blank line between each output
  }
}
// Function to display user catalogue operations
void display_user_catalogue_operations_menu()
{
  std::cout << "==== Particle Catalogue Menu: Perform Operations ====\n";
  std::cout << "1. ";
}
// Function to display help menu
void display_help()
{
  std::cout << "  ==== Help Menu ====\n";
}
// Function to display the add particles submenu
void display_add_particles_menu()
{
  std::cout << "    ==== Add Particles Menu ====\n";
  std::cout << "    1. Add Leptons\n";
  std::cout << "    2. Add Quarks\n";
  std::cout << "    3. Add Bosons\n";
  std::cout << "    4. Back to Main Menu\n";
}
// Function to display the operations submenu
void display_operations_menu()
{
  std::cout << "    ==== Operations Menu ====\n";
  std::cout << "    1. Get Total Number of Particles\n";
  std::cout << "    2. Get Particle Count by Type\n";
  std::cout << "    3. Sum Four-Momenta\n";
  std::cout << "    4. Get Sub-Container by Type\n";
  std::cout << "    5. Back to Main Menu\n";
}

// Getting particle info from user
void get_label(std::string &label)
{
  std::cout << "Enter label (string): ";
  std::getline(std::cin, label);
}
void get_momentum_values(double &px, double &py, double &pz)
{
  px = get_valid_number("Enter momentum px (MeV): ");
  py = get_valid_number("Enter momentum py (MeV): ");
  pz = get_valid_number("Enter momentum pz (MeV): ");
  // Energy calculation will be done elsewhere
}
void get_is_anti(bool &is_anti)
{
  is_anti = get_integer_input("Is the particle an antiparticle? Enter 0 for No, 1 for Yes: ", 0, 1);
}
void get_bool(bool &value, std::string prompt)
{
  value = get_integer_input(prompt, 0, 1);
}
void get_quark_details(Colour &colour_charge, bool is_anti)
{
  std::cout << is_anti << std::endl;
  int choice = get_integer_input("Enter colour charge (0 for Red, 1 for Green, 2 for Blue)[Will be anti-colour for anti-quark]: ", 0, 2);
  switch (choice)
  {
  case 0:
    if (is_anti)
    {
      colour_charge = Colour::AntiRed;
    }
    else
    {
      colour_charge = Colour::Red;
    }
    break;
  case 1:
    if (is_anti)
    {
      colour_charge = Colour::AntiGreen;
    }
    else
    {
      colour_charge = Colour::Green;
    }
    break;
  case 2:
    if (is_anti)
    {
      colour_charge = Colour::AntiBlue;
    }
    else
    {
      colour_charge = Colour::Blue;
    }
    break;
  }
}
void get_gluon_details(std::vector<Colour> &colour_charges)
{
  colour_charges.clear();
  int choice = get_integer_input("Enter colour charge (0 for Red, 1 for Green, 2 for Blue)[Will be colour anti-colour pair]: ", 0, 2);
  switch (choice)
  {
  case 0:
    colour_charges = {Colour::Red, Colour::AntiRed};
    break;
  case 1:
    colour_charges = {Colour::Red, Colour::AntiRed};
    break;
  case 2:
    colour_charges = {Colour::Red, Colour::AntiRed};
    break;
  }
}
void get_electron_details(std::vector<double> &energy_deposited_in_layers, double energy)
{
  // Clear the vector and prepare to input new values
  energy_deposited_in_layers.clear();
  std::cout << "1. Enter energy levels manually\n";
  std::cout << "2. Autoset energy levels to match energy of electron\n";
  int choice = get_integer_input("Enter choice (1 or 2): ", 1, 2);
  if (choice == 1)
  {
    std::cout << "Enter 4 values of energy that sum to " << energy << std::endl;
    double sum = 0.0;
    double input;
    for (int i = 0; i < 4; ++i)
    {
      do
      {
        input = get_valid_number("Enter value: ", 0, energy - sum); // Ensure the sum does not exceed total energy
        if ((i == 3 && sum + input != energy))
        {
          std::cout << "Total must exactly match " << energy << ". Please re-enter all values.\n";
          sum = 0.0; // Reset sum and restart input
          energy_deposited_in_layers.clear();
          i = -1; // Reset loop to the first item
        }
        else
        {
          sum += input;
          energy_deposited_in_layers.push_back(input);
          break;
        }
      } while (true);
    }
  }
  else
  {
    energy_deposited_in_layers = {energy / 4, energy / 4, energy / 4, energy / 4};
    std::cout << "Energy has been automatically distributed among the layers." << std::endl;
  }
}
void get_neutrino_details(std::string &flavour, bool &has_interacted)
{
  std::cout << "Neutrino flavour:\n";
  std::cout << "1. Electron\n";
  std::cout << "2. Muon\n";
  std::cout << "3. Tau\n";
  int choice = get_integer_input("Enter choice:", 1, 3);
  switch (choice)
  {
  case 1:
    flavour = "electron";
    break;
  case 2:
    flavour = "muon";
    break;
  case 3:
    flavour = "tau";
    break;
  }
  get_bool(has_interacted, "Has the Neutrino interacted? (0 for no, 1 for yes):");
}
void get_w_details(int &charge)
{
  std::cout << "W boson charge\n";
  std::cout << "1. +1\n";
  std::cout << "2. -1\n";
  int choice = get_integer_input("Enter choice:", 1, 2);
  switch (choice)
  {
  case 1:
    charge = 1;
    break;
  case 2:
    charge = -1;
    break;
  }
}
void get_tau_decay_products(std::vector<std::unique_ptr<Particle>> &decay_products, DecayType &decay_type, bool is_anti)
{
  std::cout << "Choose Tau Decay Products\n";
  std::cout << "1. A lepton and an antineutrino of electron flavour and a tau antineutrino\n";
  std::cout << "2. A lepton and an antineutrino of muon flavour and a tau antineutrino\n";
  std::cout << "3. An Up type and Down type quark a d a tau neutrino\n";
  std::cout << "4. None\n";
  int choice = get_integer_input("Enter choice:", 1, 4);
  decay_products.clear();
  if (choice == 1)
  {
    if (is_anti)
    {
      decay_products.push_back(std::make_unique<Electron>(-1));
      decay_products.push_back(std::make_unique<Neutrino>("electron"));
      decay_products.push_back(std::make_unique<Neutrino>("tau", -1));
      decay_type = DecayType::Weak;
    }
    else
    {
      decay_products.push_back(std::make_unique<Electron>());
      decay_products.push_back(std::make_unique<Neutrino>("electron", -1));
      decay_products.push_back(std::make_unique<Neutrino>("tau"));
      decay_type = DecayType::Weak;
    }
  }
  else if (choice == 2)
  {
    if (is_anti)
    {
      decay_products.push_back(std::make_unique<Muon>(-1));
      decay_products.push_back(std::make_unique<Neutrino>("muon"));
      decay_products.push_back(std::make_unique<Neutrino>("tau", -1));
      decay_type = DecayType::Weak;
    }
    else
    {
      decay_products.push_back(std::make_unique<Muon>());
      decay_products.push_back(std::make_unique<Neutrino>("muon", -1));
      decay_products.push_back(std::make_unique<Neutrino>("tau"));
      decay_type = DecayType::Weak;
    }
  }
  else if (choice == 3)
  {
    if (is_anti)
    {
      decay_products.push_back(std::make_unique<Up>(true));
      decay_products.push_back(std::make_unique<Down>());
      decay_products.push_back(std::make_unique<Neutrino>("tau", -1));
      decay_type = DecayType::Weak;
    }
    else
    {
      decay_products.push_back(std::make_unique<Up>());
      decay_products.push_back(std::make_unique<Down>(true));
      decay_products.push_back(std::make_unique<Neutrino>("tau"));
      decay_type = DecayType::Weak;
    }
  }
  else
  {
    decay_type = DecayType::None;
  }
}
void get_higgs_decay_products(std::vector<std::unique_ptr<Particle>> &decay_products, DecayType &decay_type)
{
  std::cout << "Choose Higgs Decay Products\n";
  std::cout << "1. Two Z bosons\n";
  std::cout << "2. Two W bosons of opposite charges\n";
  std::cout << "3. Two photons\n";
  std::cout << "4. A b quark and a b antiquark\n";
  std::cout << "5. None\n";
  int choice = get_integer_input("Enter choice:", 1, 5);
  decay_products.clear();

  switch (choice)
  {
  case 1:
  {
    std::unique_ptr<Z> z1 = std::make_unique<Z>();
    std::unique_ptr<Z> z2 = std::make_unique<Z>();
    z1->set_is_virtual(true);
    z2->set_is_virtual(true);
    decay_products.push_back(std::move(z1));
    decay_products.push_back(std::move(z2));
    decay_type = DecayType::Weak;
    break;
  }
  case 2:
    decay_products.push_back(std::make_unique<W>(1));
    decay_products.push_back(std::make_unique<W>(-1));
    decay_type = DecayType::Weak;
    break;
  case 3:
    decay_products.push_back(std::make_unique<Photon>());
    decay_products.push_back(std::make_unique<Photon>());
    decay_type = DecayType::Electromagnetic;
    break;
  case 4:
    decay_products.push_back(std::make_unique<Bottom>());
    decay_products.push_back(std::make_unique<Bottom>(true));
    decay_type = DecayType::Weak;
    break;
  case 5:
    decay_type = DecayType::None;
  default:
    std::cout << "Invalid choice. No products recorded.\n";
    break;
  }
}
void get_z_decay_products(std::vector<std::unique_ptr<Particle>> &decay_products, DecayType &decay_type)
{
  std::cout << "Choose Z Decay Products\n";
  std::cout << "1. An Up quark and an anti Up quark\n";
  std::cout << "2. An electron and an electron\n";
  std::cout << "3. A muon and an muon\n";
  std::cout << "4. A tau and an tau\n";
  std::cout << "5. None\n";
  int choice = get_integer_input("Enter choice:", 1, 5);
  decay_products.clear();

  switch (choice)
  {
  case 1:
    decay_products.push_back(std::make_unique<Up>());
    decay_products.push_back(std::make_unique<Up>(true));
    decay_type = DecayType::Weak;
    break;
  case 2:
    decay_products.push_back(std::make_unique<Electron>());
    decay_products.push_back(std::make_unique<Electron>(-1));
    decay_type = DecayType::Weak;
    break;
  case 3:
    decay_products.push_back(std::make_unique<Muon>());
    decay_products.push_back(std::make_unique<Muon>(-1));
    decay_type = DecayType::Weak;
    break;
  case 4:
    decay_products.push_back(std::make_unique<Tau>());
    decay_products.push_back(std::make_unique<Tau>(-1));
    decay_type = DecayType::Weak;
    break;
  case 5:
    decay_type = DecayType::None;
  default:
    std::cout << "Invalid choice. No products recorded.\n";
    break;
  }
}
void get_w_decay_products(std::vector<std::unique_ptr<Particle>> &decay_products, DecayType &decay_type, int charge)
{
  std::cout << "Choose W Decay Products\n";
  std::cout << "1. An Up type and Down type quark\n";
  std::cout << "2. An Electron and an Electron neutrino\n";
  std::cout << "3. A Muon and an Muon neutrino\n";
  std::cout << "4. A Tau and an Tau neutrino\n";
  std::cout << "5. None\n";
  int choice = get_integer_input("Enter choice:", 1, 5);
  decay_products.clear();

  switch (choice)
  {
  case 1:
    if (charge == 1)
    {
      decay_products.push_back(std::make_unique<Up>());
      decay_products.push_back(std::make_unique<Down>(true));
    }
    else
    {
      decay_products.push_back(std::make_unique<Down>());
      decay_products.push_back(std::make_unique<Up>(true));
    }
    decay_type = DecayType::Weak;
    break;
  case 2:
    if (charge == -1)
    {
      decay_products.push_back(std::make_unique<Electron>());
      decay_products.push_back(std::make_unique<Neutrino>("electron", -1));
    }
    else
    {
      decay_products.push_back(std::make_unique<Electron>(-1));
      decay_products.push_back(std::make_unique<Neutrino>("electron"));
    }
    decay_type = DecayType::Weak;
    break;
  case 3:
    if (charge == -1)
    {
      decay_products.push_back(std::make_unique<Muon>());
      decay_products.push_back(std::make_unique<Neutrino>("muon", -1));
    }
    else
    {
      decay_products.push_back(std::make_unique<Muon>(-1));
      decay_products.push_back(std::make_unique<Neutrino>("muon"));
    }
    decay_type = DecayType::Weak;
    break;
  case 4:
    if (charge == -1)
    {
      decay_products.push_back(std::make_unique<Tau>());
      decay_products.push_back(std::make_unique<Neutrino>("tau", -1));
    }
    else
    {
      decay_products.push_back(std::make_unique<Tau>(-1));
      decay_products.push_back(std::make_unique<Neutrino>("tau"));
    }
    decay_type = DecayType::Weak;
    break;
  case 5:
    decay_type = DecayType::None;
  default:
    std::cout << "Invalid choice. No products recorded.\n";
    break;
  }
}

void print_information_by_type(ParticleCatalogue<Particle> &user_catalogue, bool exact)
{
  std::string particle_type_string = input_particle_type();
  if (!particle_type_string.empty())
  {

    if (particle_type_string == "up")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Up>();
      }
      else
      {
        user_catalogue.print_info_by_type<Up>();
      }
    }
    else if (particle_type_string == "charm")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Charm>();
      }
      else
      {
        user_catalogue.print_info_by_type<Charm>();
      }
    }
    else if (particle_type_string == "top")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Top>();
      }
      else
      {
        user_catalogue.print_info_by_type<Top>();
      }
    }

    else if (particle_type_string == "down")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Down>();
      }
      else
      {
        user_catalogue.print_info_by_type<Down>();
      }
    }
    else if (particle_type_string == "strange")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Strange>();
      }
      else
      {
        user_catalogue.print_info_by_type<Strange>();
      }
    }
    else if (particle_type_string == "bottom")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Bottom>();
      }
      else
      {
        user_catalogue.print_info_by_type<Bottom>();
      }
    }
    else if (particle_type_string == "electron")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Electron>();
      }
      else
      {
        user_catalogue.print_info_by_type<Electron>();
      }
    }
    else if (particle_type_string == "muon")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Muon>();
      }
      else
      {
        user_catalogue.print_info_by_type<Muon>();
      }
    }
    else if (particle_type_string == "tau")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Tau>();
      }
      else
      {
        user_catalogue.print_info_by_type<Tau>();
      }
    }
    else if (particle_type_string == "neutrino")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Neutrino>();
      }
      else
      {
        user_catalogue.print_info_by_type<Neutrino>();
      }
    }
    else if (particle_type_string == "gluon")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Gluon>();
      }
      else
      {
        user_catalogue.print_info_by_type<Gluon>();
      }
    }
    else if (particle_type_string == "photon")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Photon>();
      }
      else
      {
        user_catalogue.print_info_by_type<Photon>();
      }
    }
    else if (particle_type_string == "z")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Z>();
      }
      else
      {
        user_catalogue.print_info_by_type<Z>();
      }
    }
    else if (particle_type_string == "w")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<W>();
      }
      else
      {
        user_catalogue.print_info_by_type<W>();
      }
    }
    else if (particle_type_string == "higgs")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Higgs>();
      }
      else
      {
        user_catalogue.print_info_by_type<Higgs>();
      }
    }
    else if (particle_type_string == "lepton")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Lepton>();
      }
      else
      {
        user_catalogue.print_info_by_type<Lepton>();
      }
    }
    else if (particle_type_string == "particle")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Particle>();
      }
      else
      {
        user_catalogue.print_info_by_type<Particle>();
      }
    }
    else if (particle_type_string == "boson")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Boson>();
      }
      else
      {
        user_catalogue.print_info_by_type<Boson>();
      }
    }
    else if (particle_type_string == "quark")
    {
      if (exact)
      {
        user_catalogue.print_info_by_exact_type<Quark>();
      }
      else
      {
        user_catalogue.print_info_by_type<Quark>();
      }
    }
    else
    {
      throw std::invalid_argument("Error: Unknown particle - " + particle_type_string);
    }
  }
  else
  {
    throw std::runtime_error("Error: Particle Type not found");
  }
}

void add_particles_menu_navigation(ParticleCatalogue<Particle> &user_catalogue)
{
  int choice;
  while (true)
  {
    clear_screen();
    std::cout << "==== Add Particles Menu ====\n";
    std::cout << "1. Add All Particles with default properties\n";
    std::cout << "2. Add All Leptons with default properties\n";
    std::cout << "3. Add All Quarks with default properties\n";
    std::cout << "4. Add All Bosons with default properties\n";
    std::cout << "5. Add All Anti-Leptons with default properties\n";
    std::cout << "6. Add All Anti-Quarks with default properties\n";
    std::cout << "7. Add Specific Particle\n";
    std::cout << "8. Back to Main Menu\n";

    choice = get_integer_input("Enter your choice: ", 1, 8);

    switch (choice)
    {
    case 1: // Add All Particles
      fill_catalogue(user_catalogue);

      std::cout << "All particles added to the catalogue.\n";
      break;
    case 2: // Add All Leptons
      fill_leptons(user_catalogue);
      std::cout << "All leptons added to the catalogue.\n";
      break;
    case 3: // Add All Quarks
      fill_quarks(user_catalogue);
      std::cout << "All quarks added to the catalogue.\n";
      break;
    case 4: // Add All Bosons
      fill_bosons(user_catalogue);
      std::cout << "All bosons added to the catalogue.\n";
      break;
    case 5: // Add All Anti-Leptons
      fill_anti_leptons(user_catalogue);
      std::cout << "All anti-leptons added to the catalogue.\n";
      break;
    case 6: // Add All Anti-Quarks
      fill_anti_quarks(user_catalogue);
      std::cout << "All anti-quarks added to the catalogue.\n";
      break;
    case 7: // Add Specific Particle
    {
      std::string particle_type_string = input_specific_particle_type();
      if (!particle_type_string.empty())
      {

        double mass = Mass::string_to_mass(particle_type_string);
        double px, py, pz;
        bool is_anti;
        std::string label;
        std::vector<std::unique_ptr<Particle>> decay_products;
        DecayType decay_type;
        get_momentum_values(px, py, pz);
        
        get_label(label);
        std::unique_ptr<FourMomentum> four_momentum = std::make_unique<FourMomentum>(mass, px, py, pz, true);

        if (particle_type_string == "up" || particle_type_string == "charm" || particle_type_string == "top" || particle_type_string == "down" || particle_type_string == "strange" || particle_type_string == "bottom")
        {
          get_is_anti(is_anti);
          Colour colour_charge;
          get_quark_details(colour_charge, is_anti);

          if (particle_type_string == "up")
          {
            Up *quark_to_add = new Up(label, is_anti, colour_charge, std::move(four_momentum));
            user_catalogue.add_particle(quark_to_add);
          }
          if (particle_type_string == "charm")
          {
            Charm *quark_to_add = new Charm(label, is_anti, colour_charge, std::move(four_momentum));
            user_catalogue.add_particle(quark_to_add);
          }
          if (particle_type_string == "top")
          {
            Top *quark_to_add = new Top(label, is_anti, colour_charge, std::move(four_momentum));
            user_catalogue.add_particle(quark_to_add);
          }
          if (particle_type_string == "down")
          {
            Down *quark_to_add = new Down(label, is_anti, colour_charge, std::move(four_momentum));
            user_catalogue.add_particle(quark_to_add);
          }
          if (particle_type_string == "strange")
          {
            Strange *quark_to_add = new Strange(label, is_anti, colour_charge, std::move(four_momentum));
            user_catalogue.add_particle(quark_to_add);
          }
          if (particle_type_string == "bottom")
          {
            Bottom *quark_to_add = new Bottom(label, is_anti, colour_charge, std::move(four_momentum));
            user_catalogue.add_particle(quark_to_add);
          }
        }
        else if (particle_type_string == "electron" || particle_type_string == "muon" || particle_type_string == "tau" || particle_type_string == "neutrino")
        {
          get_is_anti(is_anti);
          int lepton_number = (is_anti) ? -1 : 1;
          if (particle_type_string == "electron")
          {
            std::vector<double> energy_deposited_in_layers;
            get_electron_details(energy_deposited_in_layers, four_momentum->get_energy());
            Electron *electron = new Electron(label, std::move(four_momentum), energy_deposited_in_layers, lepton_number);
            user_catalogue.add_particle(electron);
          }
          else if (particle_type_string == "muon")
          {
            bool is_isolated;
            get_bool(is_isolated, "Is the Muon isolated? (0 for no, 1 for yes):");
            Muon *muon = new Muon(label, std::move(four_momentum), is_isolated, lepton_number);
            user_catalogue.add_particle(muon);
          }
          else if (particle_type_string == "tau")
          {
            get_tau_decay_products(decay_products, decay_type, is_anti);
            Tau *tau = new Tau(lepton_number);
            tau->set_label(label);
            tau->set_four_momentum(std::move(four_momentum));
            tau->auto_set_decay_products(std::move(decay_products), decay_type);
            user_catalogue.add_particle(tau);
          }
          else if (particle_type_string == "neutrino")
          {
            std::string flavour;
            bool has_interacted;
            get_neutrino_details(flavour, has_interacted);
            mass = Mass::string_to_mass(flavour + "_" + "neutrino");
            std::unique_ptr<FourMomentum> four_momentum = std::make_unique<FourMomentum>(mass, px, py, pz, true);
            Neutrino *neutrino = new Neutrino(label, std::move(four_momentum), flavour, has_interacted, lepton_number);
            user_catalogue.add_particle(neutrino);
          }
        }
        else if (particle_type_string == "gluon")
        {
          std::vector<Colour> colour_charges;
          get_gluon_details(colour_charges);
          Gluon *gluon = new Gluon(label, std::move(four_momentum), colour_charges);
          user_catalogue.add_particle(gluon);
        }
        else if (particle_type_string == "photon")
        {
          Photon *photon = new Photon(label, std::move(four_momentum));
          user_catalogue.add_particle(photon);
        }
        else if (particle_type_string == "z")
        {
          get_z_decay_products(decay_products, decay_type);
          Z *z = new Z(label, std::move(four_momentum));
          z->auto_set_decay_products(std::move(decay_products), decay_type);
          user_catalogue.add_particle(z);
        }
        else if (particle_type_string == "w")
        {
          int charge;
          get_w_details(charge);
          get_w_decay_products(decay_products, decay_type, charge);
          W *w = new W(label, charge, std::move(four_momentum));
          w->auto_set_decay_products(std::move(decay_products), decay_type);
          user_catalogue.add_particle(w);
        }
        else if (particle_type_string == "higgs")
        {
          get_higgs_decay_products(decay_products, decay_type);
          Higgs *higgs = new Higgs(label, std::move(four_momentum));
          higgs->auto_set_decay_products(std::move(decay_products), decay_type);
          user_catalogue.add_particle(higgs);
        }
        else
        {
          throw std::invalid_argument("Error: Unknown particle - " + particle_type_string);
        }
      }
      else
      {
        throw std::runtime_error("Error: Particle Type not found");
      }
    }
    case 8: // Back to Main Menu
      return;
    default:
      std::cout << "Invalid choice. Please try again.\n";
    }

    wait_for_enter("\nPress Enter to continue...");
    clear_screen();
  }
}

void view_catalogue_menu_navigation(ParticleCatalogue<Particle> &user_catalogue, bool sub_catalogue)
{
  int choice;
  while (true)
  {
    if (sub_catalogue)
    {
      std::cout << "==== Viewing Particle Sub-Catalogue Menu ====\n";
    }
    else
    {
      std::cout << "==== Viewing Particle Catalogue Menu ====\n";
    }
    std::cout << "1. Get Total Number of Particles\n";
    std::cout << "2. Get Particle Count by Type\n";
    std::cout << "3. Sum Four-Momenta\n";
    std::cout << "4. Print All Information\n";
    std::cout << "5. Print Information by Type\n";
    std::cout << "6. Print Information by Exact Type\n";
    std::cout << "7. Find Particles by Label\n";
    std::cout << "8. Sort Particles by Property\n";
    if (sub_catalogue)
    {
      std::cout << "9. Back to Viewing Particle Catalogue Menu\n-";
    }
    else
    {
      std::cout << "9. Back to Particle Catalogue Menu\n-";
    }

    choice = get_integer_input("Enter your choice: ", 1, 9);

    switch (choice)
    {
    case 1: // Get Total Number of Particles
    {
      size_t total_particles = user_catalogue.get_number_of_particles();
      std::cout << "Total number of particles: " << total_particles << "\n";
      break;
    }
    case 2: // Get Particle Count by Type
    {
      std::map<std::string, int> particle_counts = user_catalogue.get_particle_count_by_type();
      std::cout << "Particle counts by type:\n";
      for (const auto &count : particle_counts)
      {
        std::cout << count.first << ": " << count.second << "\n";
      }
      break;
    }
    case 3: // Sum Four-Momenta
    {
      FourMomentum total_momentum = user_catalogue.sum_four_momenta();
      std::cout << "Sum of four-momenta:\n"
                << total_momentum << "\n";
      break;
    }
    case 4: // Print all information
    {
      user_catalogue.print_all();
      break;
    }
    case 5: // Print Information by Type
    {
      // Prompt the user to enter the particle type
      print_information_by_type(user_catalogue, false);
      break;
    }
    case 6: // Print Information by Exact Type
    {
      // Prompt the user to enter the particle type
      print_information_by_type(user_catalogue, true);
      break;
    }
    case 7: // Find Particles by Label
    {
      // Prompt the user to enter the label
      std::string label;
      std::cout << "Enter the particle label: ";
      std::getline(std::cin, label);

      // Find particles by label
      std::vector<Particle *> found_particles = user_catalogue.find_particles_by_label(label);
      std::cout << "Particles with label " << label << ":\n";
      for (const auto &particle : found_particles)
      {
        particle->print();
      }
      break;
    }
    case 8: // Sort Particles by Property
    {
      std::cout << "Sort particles by:\n";
      std::cout << "1. Rest Mass\n";
      std::cout << "2. Charge\n";
      std::cout << "3. Spin\n";
      std::cout << "4. Energy\n";
      std::cout << "5. Momentum\n";
      std::cout << "6. Velocity\n";

      int sort_choice = get_integer_input("Enter your choice: ", 1, 6);

      switch (sort_choice)
      {
      case 1:
        sort_by_rest_mass(user_catalogue);
        break;
      case 2:
        sort_by_charge(user_catalogue);
        break;
      case 3:
        sort_by_spin(user_catalogue);
        break;
      case 4:
        sort_by_energy(user_catalogue);
        break;
      case 5:
        sort_by_momentum(user_catalogue);
        break;
      case 6:
        sort_by_velocity(user_catalogue);
        break;
      default:
        std::cout << "Invalid choice. Sorting skipped.\n";
      }

      std::cout << "Sorted particle catalogue:\n";
      user_catalogue.print_all();
      break;
    }
    case 9: // Back to Main Menu
      return;
    default:
      std::cout << "Invalid choice. Please try again.\n";
    }

    wait_for_enter("\nPress Enter to continue:");
    clear_screen();
  }
}

ParticleCatalogue<Particle> get_sub_catalogue(ParticleCatalogue<Particle> &user_catalogue)
{
  clear_screen();
  std::string particle_type_string = input_particle_type();
  if (!particle_type_string.empty())
  {
    if (particle_type_string == "up")
    {
      return user_catalogue.get_sub_container<Up>();
    }
    else if (particle_type_string == "charm")
    {
      return user_catalogue.get_sub_container<Charm>();
    }
    else if (particle_type_string == "top")
    {
      return user_catalogue.get_sub_container<Top>();
    }
    else if (particle_type_string == "down")
    {
      return user_catalogue.get_sub_container<Down>();
    }
    else if (particle_type_string == "strange")
    {
      return user_catalogue.get_sub_container<Strange>();
    }
    else if (particle_type_string == "bottom")
    {
      return user_catalogue.get_sub_container<Bottom>();
    }
    else if (particle_type_string == "electron")
    {
      return user_catalogue.get_sub_container<Electron>();
    }
    else if (particle_type_string == "muon")
    {
      return user_catalogue.get_sub_container<Muon>();
    }
    else if (particle_type_string == "tau")
    {
      return user_catalogue.get_sub_container<Tau>();
    }
    else if (particle_type_string == "neutrino")
    {
      return user_catalogue.get_sub_container<Neutrino>();
    }
    else if (particle_type_string == "gluon")
    {
      return user_catalogue.get_sub_container<Gluon>();
    }
    else if (particle_type_string == "photon")
    {
      return user_catalogue.get_sub_container<Photon>();
    }
    else if (particle_type_string == "z")
    {
      return user_catalogue.get_sub_container<Z>();
    }
    else if (particle_type_string == "w")
    {
      return user_catalogue.get_sub_container<W>();
    }
    else if (particle_type_string == "higgs")
    {
      return user_catalogue.get_sub_container<Higgs>();
    }
    else if (particle_type_string == "lepton")
    {
      return user_catalogue.get_sub_container<Lepton>();
    }
    else if (particle_type_string == "particle")
    {
      return user_catalogue.get_sub_container<Particle>();
    }
    else if (particle_type_string == "boson")
    {
      return user_catalogue.get_sub_container<Boson>();
    }
    else if (particle_type_string == "quark")
    {
      return user_catalogue.get_sub_container<Quark>();
    }
    else
    {
      throw std::invalid_argument("Error: Unknown particle - " + particle_type_string);
    }
  }
  else
  {
    throw std::runtime_error("Error: Particle Type not found");
  }
}

void custom_usage_menu_navigation(ParticleCatalogue<Particle> &user_catalogue)
{
  while (true)
  {
    ParticleCatalogue<Particle> *current_catalogue = &user_catalogue;
    int sub_num = 0;

    while (true)
    {
      clear_screen();
      display_main_menu();
      display_custom_usage_menu(sub_num);
      int choice = get_integer_input("Enter your choice: ", 1, 4);

      switch (choice)
      {
      case 1: // Add Particles
        add_particles_menu_navigation(*current_catalogue);
        break;
      case 2: // Display Catalogue
        clear_screen();
        view_catalogue_menu_navigation(*current_catalogue);
        break;
      case 3: // Get sub-catalogue
        try
        {
          int current_num_of_particle = current_catalogue->get_number_of_particles();
          ParticleCatalogue<Particle> *sub_container = new ParticleCatalogue<Particle>(get_sub_catalogue(*current_catalogue));
          if (sub_container->get_number_of_particles() == current_num_of_particle)
          {
            std::cout << "No particles removed from current catalogue." << std::endl;
            wait_for_enter("Hit Enter to continue...");
          }
          else if (sub_container->get_number_of_particles() > 0)
          {
            current_catalogue = sub_container;
            sub_num++;
          }
          else
          {
            std::cout << "No particles of the selected type found in the current catalogue." << std::endl;
            wait_for_enter("Hit Enter to continue...");
          }
          break;
        }
        catch (const std::exception &e)
        {
          std::cout << e.what() << std::endl;
          std::cout << "Press any key to continue..." << std::endl;
          std::cin.ignore();
          std::cin.get();
        }
        break;
      case 4: // Back
        goto outer_loop;
      default:
        std::cout << "Invalid choice. Please try again.\n";
      }
    }

  outer_loop:;
    if (sub_num == 0)
    {
      return;
    }
  }
}

// Function to display program showcase options
void program_showcase_menu_navigation()
{
  int choice;
  while (true)
  {
    display_program_showcase_menu();
    choice = get_integer_input("Enter your choice: ", 1, 7);
    switch (choice)
    {
    case 1: // Full showcase
      clear_screen();
      showcase_basic_class_hierarchy();
      wait_for_enter("\n\x1b[33mHit Enter to move onto the next showcase:\x1b[0m");
      clear_screen();
      showcase_particle_attributes();
      wait_for_enter("\n\x1b[33mHit Enter to move onto the next showcase:\x1b[0m");
      clear_screen();
      showcase_decay_product_functionality();
      wait_for_enter("\n\x1b[33mHit Enter to move onto the next showcase:\x1b[0m");
      clear_screen();
      showcase_four_momentum_class();
      wait_for_enter("\n\x1b[33mHit Enter to move onto the next showcase:\x1b[0m");
      clear_screen();
      showcase_particle_catalogue();
      break;
    case 2: // Particle class hierarchy
      clear_screen();
      showcase_basic_class_hierarchy();
      break;
    case 3: // Particle attributes
      clear_screen();
      showcase_particle_attributes();
      break;
    case 4: // Decay products functionality
      clear_screen();
      showcase_decay_product_functionality();
      break;
    case 5: // Four momentum
      clear_screen();
      showcase_four_momentum_class();
      break;
    case 6: // Particle catalogue
      clear_screen();
      showcase_particle_catalogue();
      break;
    case 7: // Back
      clear_screen();
      return;
    default:
      std::cout << "Invalid choice. Please try again.\n";
    }
    clear_screen();
    display_main_menu();
  }
}
// Function to handle user input for main menu
void main_menu_navigation(ParticleCatalogue<Particle> &user_catalogue)
{
  int choice;
  while (true)
  {
    clear_screen();
    display_main_menu();
    choice = get_integer_input("Enter your choice: ", 1, 4);

    switch (choice)
    {
    case 1:
      program_showcase_menu_navigation();
      break;
    case 2:
      custom_usage_menu_navigation(user_catalogue);
      break;
    case 3:
      display_help();
      break;
    case 4:
      std::cout << "Exiting the program\n";
      return;
    default:
      std::cout << "Invalid choice. Please try again.\n";
    }
  }
}
