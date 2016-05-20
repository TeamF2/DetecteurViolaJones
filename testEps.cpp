#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include "CImg.h"
#include "ImageIntegrale.h"
#include <cmath>
#include <fstream>


void calcError(int& nTasks,int taskId, int& nPos, double& error,std::vector<classifier>& classf,
		std::vector<feature>& feats, std::vector<std::vector<std::vector<long>>>& tables){
	double y;
    error=0;
	for(int k=taskId;k<classf.size();k+=nTasks){
		for(int j=0;j<tables.size();j++){	
			y=(classf[k].calc(calcFeat(tables[j],feats[k])));
			if(j<nPos)
				y=y-1;
			else
				y=y+1;
            error+=std::abs(y)/2;
		}
	}
}

double parError(int& nTasks, int& nPos,std::vector<classifier>& classf,
		std::vector<feature>& feats, std::vector<std::vector<std::vector<long>>>& tables){
	std::vector<std::thread> threads;
	std::vector<double> err(nTasks,0);
	for(int i=0;i<nTasks;i++)
		threads.push_back(std::thread(calcError,std::ref(nTasks),i,std::ref(nPos),std::ref(err[i]),std::ref(classf),std::ref(feats),std::ref(tables)));
		
	for(int i=0;i<nTasks;i++)
		threads[i].join();

	for(int i=1;i<nTasks;i++)
		err[0]+=err[i];
	
	return err[0];
}

int main(int argc, char** argv) {
	using namespace std;
	using namespace cimg_library;
	ofstream myfile;
	myfile.open("TestResults.txt");
	cout << "Starting main..." << endl;

	std::vector<std::vector<std::vector<long> > > iiTrain,iiValidation,iiTest;
	std::vector<feature> feats;
	std::vector<double> clasFinal;
	std::string repository="ProjSrc/";
	int width=112,height=92;
	int trainPos=818,trainNeg=4415,validationPos=818,validationNeg=4415,testPos=818,testNeg=4415;
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

	for(double eps=0.05;eps<=1;eps+=.05){
		cout<<"Eps: "<<eps<<endl;
		classf.clear();
		classf = std::vector<classifier>(feats.size(), classifier::classifier());
		int K=1,KK=1;
		double error;
		parTrain(nTasks,trainPos,iiTrain,classf,feats,eps,K);
		error=parError(nTasks,trainPos,classf,feats,iiTrain);
		cout<<"Error: "<<error<<endl;
		myfile<<"Eps: "<<eps<<"; K: "<<K<<"; error: "<<error<<" \n";
		for(int k=1;k<=9;k++){
			parTrain(nTasks,trainPos,iiTrain,classf,feats,eps,KK);
			error=parError(nTasks,trainPos,classf,feats,iiTrain);
			cout<<"Error: "<<error<<endl;
			myfile<<"Eps: "<<eps<<"; K: "<<K+k*KK<<"; error: "<<error<<" \n";
		}
	}	
	myfile.close();
	return 0;
}