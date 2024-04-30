#include "user_interface.h"

// Function to get integer input within a given range
int get_integer_input(const std::string &prompt, int min_value, int max_value)
{  
  double number;
  std::string input;
  while (true)
  {
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

// Function to display the main menu
void display_main_menu()
{
  std::cout << "==== Main Menu ====\n";
  std::cout << "1. Default Program Showcase Menu\n";
  std::cout << "2. Custom Usage Menu\n";
  std::cout << "3. Help\n";
  std::cout << "4. Quit\n-";
}

// Function to display options to showcase program
void display_program_showcase_menu()
{
  std::cout << "  ==== Program Showcase ====\n";
  std::cout << "  1. Full Showcase\n";
  std::cout << "  2. Basic Class Hierachy\n";
  std::cout << "  3. Particle Attributes and Functionality\n";
  std::cout << "  4. Four Momentum\n";
  std::cout << "  5. Particle Catalogue\n";
  std::cout << "  6. Back\n -";
}

// Function to display the custom usage menu
void display_custom_usage_menu()
{
  std::cout << "  ==== Particle Catalogue Menu ====\n";
  std::cout << "  1. Add Particles\n";
  std::cout << "  2. Display Catalogue\n";
  std::cout << "  3. Perform Operations\n";
  std::cout << "  4. Back\n -";
}

// Function to display user catalogue operations
void display_user_Catalogue_operations_menu()
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

// Function to handle user input for custom usage menu
void custom_usage_menu_navigation(ParticleCatalogue<Particle> &user_catalogue)
{
  int choice;
  while (true)
  {
    choice = get_integer_input("Enter your choice: ", 1, 6);
    switch (choice)
    {
    case 1: // Add Particles
    case 2: // Display Catalogue
    case 3: // Perform operations
    case 4: // Back
      return;
    default:
      std::cout << "Invalid choice. Please try again.\n";
    }
  }
}

// Function to display program showcase options
void program_showcase_menu_navigation(ParticleCatalogue<Particle> &showcase_catalogue)
{
  int choice;
  while (true)
  {
    choice = get_integer_input("Enter your choice: ", 1, 6);
    switch (choice)
    {
    case 1: // Full showcase
    case 2: // Particle class hierarchy
    case 3: // Particle attributes and functionality
    case 4: // Four momentum
    case 5: // Particle catalogue
    case 6: // Back
      return;
    default:
      std::cout << "Invalid choice. Please try again.\n";
    }
  }
}

// Function to handle user input for main menu
void main_menu_navigation(ParticleCatalogue<Particle> &showcase_catalogue, ParticleCatalogue<Particle> &user_catalogue)
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
      display_program_showcase_menu();
      program_showcase_menu_navigation(showcase_catalogue);
      break;
    case 2:
      display_custom_usage_menu();
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
