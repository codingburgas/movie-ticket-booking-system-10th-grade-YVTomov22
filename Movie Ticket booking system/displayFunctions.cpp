#include "precompiler.h"



void drawTopDesign()
{
std::cout << std::setw(80);
	for (int i = 0; i < 50; i++)
	{
		std::cout << '_';
	}
	std::cout << '\n' << std::setw(80) << "/" << std::setw(49) << "\\" << '\n';
}

void drawBottomDesign()
{

	std::cout << std::setw(80) << "\\";
	for (int i = 0; i < 48; i++)
	{
		std::cout << '_';
	}
	std::cout << "/\n";

}


void displayMenu()
{
	
	drawTopDesign();



	drawBottomDesign();
}