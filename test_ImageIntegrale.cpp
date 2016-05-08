/*
	Test for the integral image algorithm
*/
// RUN before in terminal
//ln -s /opt/X11/include/X11 /usr/local/include/X11
/******* user-configurable parameters *******/

// output some debug messages on cerr
bool debug = 1;

// we'll rescale all images to small squares in RGB colors
static int NEW_SIZE = 300;    // new size for horizontal/vertical
static int KEEP_SIZE = -100;  // don't change the depth (no 3D images)
static int NEW_COLORS = 3;    // make BW into colors

// infinity
double infinity = 1E+30;

// tolerance
double zero = 0;

/******* includes *******/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>

#include "CImg.h"
#include "ImageIntegrale.h"
#include "ImageIntegrale.cpp"

int main(int argc, char** argv) {
    // read in all symbols from STL and CImg library
    using namespace std;
    using namespace cimg_library;
		
    // this is the return code we pass back to the operating system on exit
    int ret = 0;
	
    // the data set X: images as (3 x #pixels)-dimensional vectors
    vector<vector<double> > X;
	
    // examine calling command line
    if (argc < 2) {
      cout << argv[0] << ": syntax error: syntax is:" << endl;
      cout << "   " << argv[0] << " imgfile1.jpg imgfile2.jpg ..." << endl;
      ret = 1;
      exit(ret);
    }

    // store the image vectors corresponding to filenames passed on command line
    for (int c = 1; c < argc; ++c) {
      try {
        // try reading the image
        CImg<unsigned char> img(argv[c]);
        // if we're here, reading was successful: resize
        img.resize(NEW_SIZE, NEW_SIZE, KEEP_SIZE, NEW_COLORS);
        // transform into vector of doubles
        vector<double> Xcol;
        for (CImg<unsigned char>::iterator pixIt = img.begin();
             pixIt != img.end(); ++pixIt) {
          Xcol.push_back(((double)*pixIt) / 255.0);
        }
        X.push_back(Xcol);
      } catch (CImgException& e) {
        // some errors in reading the image
        cerr << argv[0] << ": CImg error while reading " << argv[c] << endl;
        ret = 2;
        exit(ret);
      }
    }

    // output configuration
    cout << argv[0] << ": configuration for this run:" << endl;
    cout << "  images rescaled to " << NEW_SIZE << " x " << NEW_SIZE << endl;
	
	vector<vector<double> > Sum = IntegralImage(X);
	printData(X);
	cout << endl;
	printData(Sum);
	
	return ret;
}