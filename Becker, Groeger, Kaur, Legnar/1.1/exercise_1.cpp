//-------------group members--------------
//	Dennis Becker		3497351
//	Julian Gröger		3542588
//	Amrit  Kaur			3532964
//  Maximilian Legnar	3544557
//-----------------------------------------

#include <iostream>
#include <string>

#define PI 3.1415

int main()
{
	// Init
	std::string input = "";
	double radius = 0.0;
	double area = 0.0;
	std::cout << "Press 'q' to quit.\n\n";

	while (true) {
		// Prompting the user
		std::cout << "Please enter a circumference\n";
		std::cin >> input;

		//We're done
		if (input == "q") {
			return 0;
		}

		try{
			// try to cast the value
			radius = 0.5 * std::stod(input) / PI;
			area = PI * radius * radius;
			// Give an anser
			std::cout << "The area of a circle with r = " + std::to_string(radius) + " is " + std::to_string(area) + ".\n";

		}
		catch (const std::exception&){
			//Looks like the input was not okay
			// It was a invalid input
			std::cout << "Error: Invalid Input. \n\n";
		}

	}
}
