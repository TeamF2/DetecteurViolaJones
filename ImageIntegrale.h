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
void initAndScanRow(const cimg_library::CImg<long>& img,std::vector<long> row, int i); //aux1

void scanCollumn(std::vector<std::vector<long>> sat,int i); //aux2

std::vector<std::vector<long>> parSAT(const cimg_library::CImg<long>& img); //parALLEL SAT

#endif