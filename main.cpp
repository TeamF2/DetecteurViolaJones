#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include "CImg.h"
#include "ImageIntegrale.h"


int main(int argc, char** argv) {
	using namespace std;
	using namespace cimg_library;

	std::vector<std::vector<std::vector<long> > > iiTrain,iiValidation,iiTest;
	std::vector<feature> feats;
	std::vector<double> clasFinal;
	int width,height;
	int trainPos,validationPos;
	int nTasks=std::thread::hardware_concurrency();

	if(argc==2)
		nTasks=argv[1];

	//1-Define features
	feats=distFeat(width,height);
	
	//2-Read "Train" repertory images
	iiTrain=distII();

	//3-Create weak classifiers
	std::vector<classifier> classf(feats.size(),new classifier());
	parTrain(nTasks,trainPos,iiTrain,classf,feats);

	//4-Read "Validation" repertory images
	iiValidation=distII();

	//5-Boost weak classifiers
	clasFinal=boost(classf,iiValidation,nTasks);

	//6-Vary theta (-1<=theta<=1)


	//7-





	/*
	// Test IntegralImage  works
	vector<vector<double> > values(6, vector<double>(4));
	
	for(int i = 0; i < values.size(); ++i)
	{
		for(int j = 0; j < values[0].size(); ++j)
		{
			values[i][j] = 6;
		}
	}
							
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
