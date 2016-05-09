#include <iostream>
#include <vector>
#include <cstdlib>
#include "CImg.h"
#include "ImageIntegrale.h"

int main(void) {
	using namespace std;
	using namespace cimg_library;
	
	vector<vector<double> > values(6, vector<double>(4));
	
	for(int i = 0; i < values.size(); ++i)
	{
		for(int j = 0; j < values[0].size(); ++j)
		{
			values[i][j] = 6;
		}
	}
		
	/*							
	std::vector<std::vector<double> > Sum = IntegralImage(values);
	printData(values);
	std::cout << std::endl;
	printData(Sum);
	*/
	vector<vector<double> > X = DataToMatrix("boy.jpg");
	vector<vector<double> > Sum = IntegralImage(X);
	//printData(Sum);
	
	return 0;
 }