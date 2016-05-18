#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include "CImg.h"
#include "ImageIntegrale.h"


int main(int argc, char** argv) {
	using namespace std;
	using namespace cimg_library;
	
	cout << "Starting main..." << endl;

	std::vector<std::vector<std::vector<long> > > iiTrain,iiValidation,iiTest;
	std::vector<feature> feats;
	std::vector<double> clasFinal;
	std::string repository="ProjSrc/";
	int width,height;
	int trainPos=818,trainNeg=4415,validationPos=818,validationNeg=4415,testPos=818,testNeg=1000;
	int nTasks=std::thread::hardware_concurrency();

	if(argc==2)
		nTasks=std::atoi(argv[1]);

	//1-Define features
	feats=distFeat(width,height);
	cout << "We have features!" << endl;
	
	//2-Read "Train" (app) repository images
	iiTrain=distII(nTasks,trainPos,trainNeg,repository+"app");
	cout << "We loaded the train images!" << endl;

	//3-Create weak classifiers
	std::vector<classifier> classf(feats.size(), classifier());
	parTrain(nTasks,trainPos,iiTrain,classf,feats);
	cout << "We have weak classifiers!" << endl;

	//4-Read "Validation" (dev) repository images
	iiValidation=distII(nTasks,validationPos,validationNeg,repository+"dev");
	cout << "We loaded the validation images!" << endl;

	//5-Boost weak classifiers
	clasFinal=boost(nTasks, validationPos, classf,iiValidation, feats);
	cout << "We have adaboost!" << endl;

	//6-read "Test" (test) repository images
	iiTest=distII(nTasks,testPos,testNeg,repository+"test");
	cout << "We test the images!" << endl;


	//7-Vary theta (-1<=theta<=1)
	double theta=-1;
	std::vector<std::vector<long>> fauxNP;
	for(int i=0;i<20;i++,theta+=0.1){
		fauxNP.push_back(test(nTasks,clasFinal,feats,testPos,classf, iiTest, theta));
	}
	
	cout << "Let's print the results!" << endl;
	//print results
	theta=-1;
	for(int i=0;i<20;i++,theta+=0.1)
		cout<<"Theta: "<<theta<<", faux positifs: "<<fauxNP[i][0]/testPos<<", faux negatifs: "<<fauxNP[i][1]<<endl;
	
	
	return 0;
 }
