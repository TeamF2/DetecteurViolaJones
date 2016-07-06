#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include "CImg.h"
#include "ImageIntegrale.h"
/*
	Test to load and compute the integral image of a .jpg file
*/

int main(int argc, char** argv) {
	using namespace std;
	using namespace cimg_library;
	
	// Loading image
	CImg<long> image("ProjSrc/app/pos/im0.jpg");
	cout << "Loaded Image!!" << endl;
	
	// Computing the Integral Image
	std::vector<std::vector<long> > sat = SAT(image);
	cout << "Calculated SAT!!" << endl;
	
	// Show Integral Image dimentions
	std::cout << "Image dimensions"<< std::endl; 
	std::cout << sat.size()<< "x"<< sat[0].size() << std::endl;
	
	// Print the Integral Image
	printData(sat);
	cout << "Finished Print!!" << endl;
	
	return 0;
 }
	