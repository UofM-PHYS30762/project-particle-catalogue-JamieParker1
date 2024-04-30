#include "user_interface.h"

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
      std::cout << "Invalid input. Please enter a valid number.\n";
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

void input_particle_type()
{
  std::cout << "==== Particle Types ====\n";
  std::cout << "1. Bosons\n";
  std::cout << "2. Quarks\n";
  std::cout << "3. Leptons\n";

  int particle_type_choice = get_integer_input("Enter the particle type: ", 1, 3);

  switch (particle_type_choice)
  {
  case 1: // Bosons
    std::cout << "  ==== Bosons ====\n";
    std::cout << "  1. Photon\n";
    std::cout << "  2. Gluon\n";
    std::cout << "  3. W plus\n";
    std::cout << "  4. W minus\n";
    std::cout << "  5. Z\n";
    std::cout << "  6. Higgs\n";

    int boson_choice = get_integer_input("Enter the boson type: ", 1, 6);
    // Add code to create and add the chosen boson to the catalogue
    break;
  case 2: // Quarks
    std::cout << "  ==== Quarks ====\n";
    std::cout << "  1. Up\n";
    std::cout << "  2. Charm\n";
    std::cout << "  3. Top\n";
    std::cout << "  4. Down\n";
    std::cout << "  5. Strange\n";
    std::cout << "  6. Bottom\n";
    int quark_choice = get_integer_input("Enter the boson type: ", 1, 6);
    break;
  case 3: // Leptons
  {
    std::cout << "  ==== Leptons ====\n";
    std::cout << "  1. Electron\n";
    std::cout << "  2. Muon\n";
    std::cout << "  3. Tau\n";
    std::cout << "  4. Neutrino\n";

    int lepton_choice = get_integer_input("Enter the lepton type: ", 1, 4);

    switch (lepton_choice)
    {
    case 1: // Electron
      break;
    case 2: // Muon
      break;
    }
  break;
  }
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
void display_custom_usage_menu()
{
  std::cout << "  ==== Particle Catalogue Menu ====\n";
  std::cout << "  1. Add Particles\n";
  std::cout << "  2. Display Catalogue\n";
  std::cout << "  3. Perform Operations\n";
  std::cout << "  4. Back\n";
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

void display_catalogue_menu_navigation(ParticleCatalogue<Particle> &user_catalogue, bool sub_catalogue = false)
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
    std::cout << "4. Get Sub-Container by Type\n";
    std::cout << "5. Print All Information\n";
    std::cout << "6. Print Information by Type\n";
    std::cout << "7. Print Information by Exact Type\n";
    std::cout << "8. Find Particles by Label\n";
    std::cout << "9. Sort Particles by Property\n";
    std::cout << "10. Back to Particle Catalogue Menu\n-";

    choice = get_integer_input("Enter your choice: ", 1, 10);

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
    case 4: // Get Sub-Container by Type
    {
      // Prompt the user to enter the particle type
      std::string particle_type;
      std::cout << "Enter the particle type: ";
      std::getline(std::cin, particle_type);

      // Get the sub-container based on the particle type
      ParticleCatalogue<Particle> sub_container = user_catalogue.get_sub_container<Particle>();
      // Prompt the user if they want to perform operations on the sub-container
      std::cout << "Do you want to perform operations on the sub-container? (y/n): ";
      char perform_ops;
      std::cin >> perform_ops;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (perform_ops == 'y' || perform_ops == 'Y')
      {
        // Recursively call the function with the sub-container
        clear_screen();
        display_catalogue_menu_navigation(sub_container);
      }
      break;
    }
    case 5: // Print all information
    {
      user_catalogue.print_all();
      break;
    }
    case 6: // Print Information by Type
    {
      // Prompt the user to enter the particle type
      std::string particle_type;
      std::cout << "Enter the particle type: ";
      std::getline(std::cin, particle_type);

      // Print information by type
      std::cout << "Information for particle type " << particle_type << ":\n";
      user_catalogue.print_info_by_type<Particle>();
      break;
    }
    case 7: // Print Information by Exact Type
    {
      // Prompt the user to enter the particle type
      std::string particle_type;
      std::cout << "Enter the exact particle type: ";
      std::getline(std::cin, particle_type);

      // Print information by exact type
      std::cout << "Information for exact particle type " << particle_type << ":\n";
      user_catalogue.print_info_by_exact_type<Particle>();
      break;
    }
    case 8: // Find Particles by Label
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
    case 9: // Sort Particles by Property
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
    case 10: // Back to Main Menu
      return;
    default:
      std::cout << "Invalid choice. Please try again.\n";
    }

    wait_for_enter("\nPress Enter to perform another operation:");
    clear_screen();
  }
}

// void add_particles_menu_navigation(ParticleCatalogue<Particle> &user_catalogue)
// {
//   int choice;
//   while (true)
//   {
//     std::cout << "==== Add Particles Menu ====\n";
//     std::cout << "1. Add All Particles\n";
//     std::cout << "2. Add All Leptons\n";
//     std::cout << "3. Add All Quarks\n";
//     std::cout << "4. Add All Bosons\n";
//     std::cout << "5. Add All Anti-Leptons\n";
//     std::cout << "6. Add All Anti-Quarks\n";
//     std::cout << "7. Add Specific Particle\n";
//     std::cout << "8. Back to Main Menu\n";

//     choice = get_integer_input("Enter your choice: ", 1, 8);

//     switch (choice)
//     {
//     case 1: // Add All Particles
//       fill_particles(user_catalogue);
//       fill_anti_particles(user_catalogue);
//       std::cout << "All particles added to the catalogue.\n";
//       break;
//     case 2: // Add All Leptons
//       fill_leptons(user_catalogue);
//       std::cout << "All leptons added to the catalogue.\n";
//       break;
//     case 3: // Add All Quarks
//       fill_quarks(user_catalogue);
//       std::cout << "All quarks added to the catalogue.\n";
//       break;
//     case 4: // Add All Bosons
//       fill_bosons(user_catalogue);
//       std::cout << "All bosons added to the catalogue.\n";
//       break;
//     case 5: // Add All Anti-Leptons
//       fill_anti_leptons(user_catalogue);
//       std::cout << "All anti-leptons added to the catalogue.\n";
//       break;
//     case 6: // Add All Anti-Quarks
//       fill_anti_quarks(user_catalogue);
//       std::cout << "All anti-quarks added to the catalogue.\n";
//       break;
//     case 7: // Add Specific Particle
//     {
//       std::cout << "==== Particle Types ====\n";
//       std::cout << "1. Bosons\n";
//       std::cout << "2. Quarks\n";
//       std::cout << "3. Leptons\n";

//       int particle_type_choice = get_integer_input("Enter the particle type: ", 1, 3);

//       switch (particle_type_choice)
//       {
//       case 1: // Bosons
//         // Add code to display a list of bosons and prompt the user to choose a specific boson
//         // Example:
//         // std::cout << "==== Boson Types ====\n";
//         // std::cout << "1. Photon\n";
//         // std::cout << "2. Gluon\n";
//         // ...
//         // int boson_choice = get_integer_input("Enter the boson type: ", 1, num_of_bosons);
//         // Add code to create and add the chosen boson to the catalogue
//         break;
//       case 2: // Quarks
//         // Add code to display a list of quarks and prompt the user to choose a specific quark
//         // Example:
//         // std::cout << "==== Quark Types ====\n";
//         // std::cout << "1. Up\n";
//         // std::cout << "2. Down\n";
//         // ...
//         // int quark_choice = get_integer_input("Enter the quark type: ", 1, num_of_quarks);
//         // Add code to create and add the chosen quark to the catalogue
//         break;
//       case 3: // Leptons
//       {
//         std::cout << "==== Lepton Types ====\n";
//         std::cout << "1. Electron\n";
//         std::cout << "2. Muon\n";
//         // Add more lepton types as needed

//         int lepton_choice = get_integer_input("Enter the lepton type: ", 1, 2);

//         switch (lepton_choice)
//         {
//         case 1: // Electron
//         {
//           std::cout << "Do you want to specify properties for the Electron? (y/n): ";
//           char specify_properties;
//           std::cin >> specify_properties;
//           std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//           if (specify_properties == 'y' || specify_properties == 'Y')
//           {
//             std::cout << "Enter the energy (MeV): ";
//             double energy;
//             std::cin >> energy;
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//             std::cout << "Enter the momentum in x direction (MeV): ";
//             double px;
//             std::cin >> px;
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//             std::cout << "Enter the momentum in y direction (MeV): ";
//             double py;
//             std::cin >> py;
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//             std::cout << "Enter the momentum in z direction (MeV): ";
//             double pz;
//             std::cin >> pz;
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//             std::cout << "Enter the lepton number (1 for electron, -1 for positron): ";
//             int lepton_number;
//             std::cin >> lepton_number;
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//             std::unique_ptr<FourMomentum> four_momentum = std::make_unique<FourMomentum>(energy, px, py, pz);
//             Electron *electron = new Electron(four_momentum, std::vector<double>{energy / 4, energy / 4, energy / 4, energy / 4}, lepton_number);
//             user_catalogue.add_particle(electron);
//           }
//           else
//           {
//             Electron *electron = new Electron();
//             user_catalogue.add_particle(electron);
//           }
//           break;
//         }
//         case 2: // Muon
//         {
//           std::cout << "Do you want to specify properties for the Muon? (y/n): ";
//           char specify_properties;
//           std::cin >> specify_properties;
//           std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//           if (specify_properties == 'y' || specify_properties == 'Y')
//           {
//             std::cout << "Enter the energy (MeV): ";
//             double energy;
//             std::cin >> energy;
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//             std::cout << "Enter the momentum in x direction (MeV): ";
//             double px;
//             std::cin >> px;
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//             std::cout << "Enter the momentum in y direction (MeV): ";
//             double py;
//             std::cin >> py;
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//             std::cout << "Enter the momentum in z direction (MeV): ";
//             double pz;
//             std::cin >> pz;
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//             std::cout << "Enter the lepton number (1 for muon, -1 for antimuon): ";
//             int lepton_number;
//             std::cin >> lepton_number;
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//             std::cout << "Is the muon isolated? (1 for yes, 0 for no): ";
//             bool is_isolated;
//             std::cin >> is_isolated;
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//             std::unique_ptr<FourMomentum> four_momentum = std::make_unique<FourMomentum>(energy, px, py, pz);
//             Muon *muon = new Muon(four_momentum, is_isolated, lepton_number);
//             user_catalogue.add_particle(muon);
//           }
//           else
//           {
//             Muon *muon = new Muon();
//             user_catalogue.add_particle(muon);
//           }
//           break;
//         }
//         default:
//           std::cout << "Invalid lepton type choice.\n";
//         }
//         break;
//       }
//       default:
//         std::cout << "Invalid particle type choice.\n";
//       }
//       break;
//     }
//     case 8: // Back to Main Menu
//       return;
//     default:
//       std::cout << "Invalid choice. Please try again.\n";
//     }

//     wait_for_enter("\nPress Enter to continue...");
//     clear_screen();
//   }
// }

// Function to handle user input for custom usage menu
void custom_usage_menu_navigation(ParticleCatalogue<Particle> &user_catalogue)
{
  int choice;
  while (true)
  {
    clear_screen();
    display_main_menu();
    display_custom_usage_menu();
    choice = get_integer_input("Enter your choice: ", 1, 4);
    switch (choice)
    {
    case 1: // Add Particles
      break;
    case 2: // Display Catalogue
      clear_screen();
      display_catalogue_menu_navigation(user_catalogue);
      break;
    case 3: // Perform operations
    case 4: // Back
      return;
    default:
      std::cout << "Invalid choice. Please try again.\n";
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
