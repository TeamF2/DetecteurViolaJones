#ifndef IMAGEINTEGRALEH
#define IMAGEINTEGRALEH

#include <vector>
#include "CImg.h"


// IntegralImage of an array
std::vector<std::vector<double> > IntegralImage(std::vector<std::vector<double> >& data);

// Read an image
std::vector<double> ReadData(const char *filepath);

// Read an image outputs a grayscale matrix
std::vector<std::vector<double> > DataToMatrix(const char *filepath);

// Print a vector of vectors
void printData(std::vector<std::vector<double> >& data);

//Q1.1
std::vector<std::vector<long>> SAT(const cimg_library::CImg<long>& img);    //Summed Area Table

//Q1.2
class feature{
	int x,y,w,h;
	char type;

	feature();
};

long calcFeat(std::vector<std::vector<long>> sat, feature f);

void featVect(std::vector<feature>& feats, char type,int wMax, int hMax);

std::vector<feature> distFeat(int widht, int height);

//
struct classifier{
	double w1,w2;
};

void clasf(classifier c);

#endif
