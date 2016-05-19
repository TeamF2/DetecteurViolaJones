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
	int trainPos=818,trainNeg=4415,validationPos=818,validationNeg=4415,testPos=818,testNeg=4415;
	int nTasks=std::thread::hardware_concurrency();
	double eps=0.5;

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

	parTrain(nTasks,trainPos,iiTrain,classf,feats,eps);
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
			cout<<clasFinal[i]<<" ; ";
	cout<<endl;


	//6-read "Test" (test) repository images
	iiTest=distII(nTasks,testPos,testNeg,repository+"test");
	cout << "We loaded the "<<iiTest.size()<<" test images!" << endl;


	double thetaMin,thetaMax;
	//7-Vary theta (-1<=theta<=1)
	cout << "Test strong classifier:" << endl;
	while(1){

		cout << "Enter thetaMin:" << endl;
		cin >> thetaMin;
		cout << "Enter thetaMax:" << endl;
		cin>> thetaMax;

		if(thetaMin==thetaMax)
			break;
		std::vector<std::vector<long>> fauxNP;
		for(int i=0;i<11;i++){
			fauxNP.push_back(test(nTasks,clasFinal,feats,testPos,classf, iiTest, thetaMin +i*(thetaMax-thetaMin)/10));
		}
		cout << "Let's print the results!" << endl;
		//print results
		for(int i=0;i<11;i++){
			cout<<"Theta: "<< thetaMin +i*(thetaMax-thetaMin)/10 <<", f-: "<<fauxNP[i][0]<<", f+: "<<fauxNP[i][1]<<endl;
		}
	}
	

	return 0;
 }
