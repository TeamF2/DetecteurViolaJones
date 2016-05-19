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
	int width=112,height=92;
	int trainPos=818,trainNeg=4415,validationPos=400,validationNeg=400,testPos=818,testNeg=4415;
	int nTasks=std::thread::hardware_concurrency();

	if(argc==2)
		nTasks=std::atoi(argv[1]);

	cout << "Using "<<nTasks<<" threads." << endl;


	//1-Define features
	feats=distFeat(width,height);
	cout << "We have "<<feats.size()<<" features!" << endl;
	
	//2-Read "Train" (app) repository images
	iiTrain=distII(nTasks,trainPos,trainNeg,repository+"app");
	cout << "We loaded the "<<iiTrain.size()<<" train images!" << endl;

	//3-Create weak classifiers
	std::vector<classifier> classf(feats.size(), classifier::classifier());
	cout << "Created classifiers vector!" << endl;
	parTrain(nTasks,trainPos,iiTrain,classf,feats);
	cout << "We have the "<<classf.size()<<" weak classifiers!" << endl;

	//4-Read "Validation" (dev) repository images
	iiValidation=distII(nTasks,validationPos,validationNeg,repository+"dev");
	cout << "We loaded the "<<iiValidation.size()<<" validation images!" << endl;

	cout << "Let's (ada)boost!" << endl;
	//5-Boost weak classifiers
	clasFinal=boost(nTasks, validationPos, classf,iiValidation, feats);
	cout << "We have adaboost!" << endl;

	cout<<"Printing strong classifier weights:"<<endl;
	for(int i=0;i<clasFinal.size();i++)
		if(clasFinal[i])
			cout<<clasFinal[i];
	cout<<endl;

	/*
	//6-read "Test" (test) repository images
	iiTest=distII(nTasks,testPos,testNeg,repository+"test");
	cout << "We loaded the "<<iiTest.size()<<" test images!" << endl;


	//7-Vary theta (-1<=theta<=1)
	cout << "Testing strong classifier:" << endl;
	std::vector<std::vector<long>> fauxNP;
	for(double theta=-1;theta<=1;theta+=0.1){
		fauxNP.push_back(test(nTasks,clasFinal,feats,testPos,classf, iiTest, theta));
	}
	

	cout << "Let's print the results!" << endl;
	//print results
	int i;
	for(double theta=-1,i=0;theta<=1;theta+=0.1,i++)
		cout<<"Theta: "<<theta<<", f+: "<<(double)fauxNP[i][0]/(double)testPos<<", f-: "<<(double)fauxNP[i][1]/(double)testNeg<<endl;
	*/
	
	return 0;
 }
