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

//Q2.1
class classifier{
	double w1,w2;
	classifier(double,double);
};

std::vector<std::vector<std::vector<long> > > distII();

void train(int nTasks, int taskId,int nPos, std::vector<std::vector<std::vector<long>>> tables, std::vector<classifier> classf, std::vector<feature> feats );

void parTrain(int nTasks,int nPos, std::vector<std::vector<std::vector<long>>> tables, std::vector<classifier> classf, std::vector<feature> feats );


//Q2.2
bool error(classifier c, bool clas,feature feat,std::vector<std::vector<long>> sat);

void chooseClasf(int& clas,double& error);

void boost();

int F(std::vector<double>weights,std::vector<classifier> classf, std::vector<std::vector<long>>sat,double theta);




#endif
