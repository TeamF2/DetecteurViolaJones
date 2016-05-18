#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include "CImg.h"
#include "ImageIntegrale.h"
#include "math.h"

std::vector<std::vector<double> > IntegralImage(std::vector<std::vector<double> >& data) {
	using namespace std;
	int m = data.size();
	int n = data[0].size();
	
  vector<vector<double> > output(m, vector<double>(n));
  
  output[0][0] = data[0][0];
  
  // initialize the first row
  for(unsigned int i = 1; i < m; ++i)
  {
	  output[i][0] = data[i][0] + output[i-1][0];
  }
  // initialize the first column
  for(unsigned int j= 1; j < n; ++j)
  {
	  output[0][j] = data[0][j] + output[0][j-1];
  }
  // Compute all the other values
  for(unsigned int i = 1; i < m; ++i)
  {
	for(unsigned int j = 1; j < n; ++j)
	{
		output[i][j] = data[i][j] + output[i-1][j] + output[i][j-1] - output[i-1][j-1];
	}
  }

	return output;
}

std::vector<double> ReadData(const char *filepath) {
	using namespace std;
	using namespace cimg_library;
	CImg<unsigned char> image(filepath);
	
	int width = image.width();
	int height = image.height();
	int depth = image.depth();
	
	vector<double> out;
	
	for (CImg<unsigned char>::iterator it = image.begin(); it != image.end(); ++it) {
		out.push_back(((double)*it) / 255.0);
	  }
	  cout << endl;
	  cout << width << "x" << height << "x" << depth << endl;
	  
	  return out;
}

std::vector<std::vector<double> > DataToMatrix(const char *filepath) {
	using namespace std;
	using namespace cimg_library;
	CImg<unsigned char> image(filepath);
	
	int width = image.width();
	int height = image.height();
	int depth = image.depth();
	
	int i = 0;
	int j = 0;
	int k = 0;
	vector<vector<double> > out(width, vector<double>(height));
	
	for (CImg<unsigned char>::iterator it = image.begin(); it != image.end(); ++it) {
		out[i][j] = 0.2989 * ((double)*it);
		++it;
		out[i][j] += 0.5870 * ((double)*it);
		++it;
		out[i][j] += 0.1140 * ((double)*it);
		
		j++;
		j %= height;
		if(j==0) {
			i++;
		}
	  }
	  //cout << endl;
	  cout << width << "x" << height << "x" << depth << endl;
	  cout << out.size() << "x" << out[0].size() << "x" << endl;
	  
	  return out;
}

void printData(std::vector<std::vector<double> >& data) {
	using namespace std;
	
    for (vector<vector<double> >::iterator it = data.begin(); it != data.end();
         ++it) {
      // loop over columns
      for (vector<double>::iterator jt = it->begin(); jt != it->end(); ++jt) {
        // separate fields using spaces
        cout << " " << *jt;
      }
      cout << endl;
    }
}

//Q1.1
std::vector<std::vector<long>> SAT(const cimg_library::CImg<long>& img){//OK
    using namespace cimg_library;
    std::vector<std::vector<long>> sat;
    std::vector<long> row;
    long init=0;
    std::vector<std::vector<long>>::iterator it;
    std::vector<long>::iterator i,j;

    
    for(int y=0;y<img.height();y++){//init first row
        init+=img(0,y,0);
        row.push_back(init);
    }

    sat.push_back(row);
    row.clear();
    it=sat.begin();
    for (int x=1; x<img.width(); x++,sat.push_back(row),it++,row.clear()) {
        // iterating through: it,x-> rows; i,y->columns in current row; j->columns in previous row
       
        //row initialization
        j=it->begin();
        row.push_back( *j + img(x,0,0));
        j++;
        i=row.begin();
        
        //column iteration
        for (int y=1; y<img.height(); y++,i++,j++)
                row.push_back(img(x,y,0) + *j + *i - *(j-1));
    }
    return sat;
}

//Q1.2

feature::feature(int xx, int yy, int ww,int hh,char c){ // fix definition
	x=xx;
	y=yy;
	w=ww;
	h=hh;
	type=c;
}

long calcFeat(std::vector<std::vector<long>>& sat, feature& f){////TODO: conferir
	switch(f.type){
	case 'a':
		return 2*sat[f.x+f.w/2][f.y]-2*sat[f.x+f.w/2][f.y+f.h]-sat[f.x][f.y]+sat[f.x][f.y+f.h]-sat[f.x+f.w][f.y]+sat[f.x+f.w][f.y+f.h];

	case 'b':
		return 2*sat[f.x+f.w][f.y+f.h/2]-2*sat[f.x][f.y+f.h/2]+sat[f.x][f.y]+sat[f.x][f.y+f.h]-sat[f.x+f.w][f.y]-sat[f.x+f.w][f.y+f.h];

	case 'c':
		return -sat[f.x][f.y]+sat[f.x][f.y+f.h]+sat[f.x+f.w][f.y]-sat[f.x+f.w][f.y+f.h]+2*sat[f.x+f.w/3.0][f.y]-2*sat[f.x+f.w/3.0][f.y+f.h]-2*sat[f.x+2*f.w/3.0][f.y]+2*sat[f.x+2*f.w/3.0][f.y+f.h];

	case 'd':
		return 2*(sat[f.x+f.w/2][f.y]+sat[f.x+f.w/2][f.y+f.h]+sat[f.x][f.y+f.h/2]+sat[f.x+f.w][f.y+f.h/2])-4*sat[f.x+f.w/2][f.y+f.h/2]-sat[f.x][f.y]-sat[f.x+f.w][f.y+f.h]-sat[f.x+f.w][f.y]-sat[f.x][f.y+f.h];
	}
	return 0;
}

void featVect(std::vector<feature>& feats, char type,int& wMax, int& hMax){//OK
	int wMin,hMin, wInc,hInc;
	switch(type){
	case 'a':
		wMin=15;
		wInc=8;
		hMin=7;
		hInc=4;
		break;
	case 'b':
		wMin=7;
		wInc=4;
		hMin=15;
		hInc=8;
		break;
	case 'c':
		wMin=23;
		wInc=12;
		hMin=7;
		hInc=4;
		break;
	case 'd':
		wMin=15;
		wInc=8;
		hMin=15;
		hInc=8;
	}
	for(int w=wMin;w<wMax;w+=wInc){
		for(int h=hMin;h<hMax;h+=hInc){
			for(int x=0;x<wMax-w;x+=4){
				for(int y=0;y<hMax-h;y+=4)
					feats.push_back(feature(x,y,w,h,type)); // fix new gives a pointer
			}
		}
	}
}

std::vector<feature> distFeat(int& width, int& height){//OK // fix name widht -> width
	std::vector<feature> fA,fB,fC,fD;

	std::thread t1(featVect,fA,'a',width,height);
	std::thread t2(featVect,fB,'b',width,height);
	std::thread t3(featVect,fC,'c',width,height);
	std::thread t4(featVect,fD,'d',width,height);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	fA.insert(fA.end(),fB.begin(),fB.end());
	fA.insert(fA.end(),fC.begin(),fC.end());
	fA.insert(fA.end(),fD.begin(),fD.end());
	return fA;
}


//Q2.1
classifier::classifier(){ //fix definition
	w1=1;
	w2=0;
}

int classifier::calc(double x){ // fix definition
	if(w1*x+w2>=0)
		return 1;
	else
		return -1;
}

void readImgs(int& nTasks, int taskId,bool pos,int& nPos, std::vector<std::vector<std::vector<long>>>& iis ,std::string& rep){////TODO conferir
	using namespace cimg_library; // added to fix CImg call
	CImg<long> img;
	std::stringstream ss;
	if(pos){
		for(int i=taskId;i<nPos;i+=nTasks){
			ss<<rep<<"im"<<i<<".jpg";
			img.load(ss.str());
			iis[i]=SAT(img);
		}
	}
	else{
		for(int i=nPos+taskId;i<iis.size();i+=nTasks){
			ss<<rep<<"im"<<i<<".jpg";
			img.load(ss.str());
			iis[i]=SAT(img);
		}
	}

}


std::vector<std::vector<std::vector<long> > > distII(int& nPos,int& nNeg, std::string rep,int& nTasks){//TODO conferir
	std::vector<std::vector<std::vector<long> > > ii(nPos+nNeg); // semicolon fix
	std::vector<std::thread> pos,neg;
	for(int i=0;i<nTasks;i++)
			pos.push_back(std::thread(readImgs,nTasks,i,true,nPos,ii,rep+"/pos/"));

	for(int i=0;i<nTasks;i++){
			pos[i].join();
			neg.push_back(std::thread(readImgs,nTasks,i,false,nPos,ii,rep+"/neg/"));
	}

	for(int i=0;i<nTasks;i++)
			neg[i].join();

	return ii;
}

void train(int& nTasks, int taskId,int& nPos, std::vector<std::vector<std::vector<long>>>& tables, std::vector<classifier>& classf, std::vector<feature>& feats ){///TODO: Conferir o eps e o K
	srand(taskId);
	double r,xki;
	int rr,c,h;
	double eps=0.3; //0<eps<=1   /////////TODO
	int K=tables.size()/5;		///////////TODO

	for(int i=taskId;i<feats.size();i+=nTasks){
		for(int k=0;k<K;k++){
			r=rand()/RAND_MAX; // fix srand() -> rand()
			rr=((int)r*tables.size()-1);

			xki=calcFeat(tables[rr],feats[i]);
			h=classf[i].calc(xki);

			if(rr<nPos)
				c=1;
			else
				c=-1;

			classf[i].w1-=eps*(h-c)*xki;
			classf[i].w2-=eps*(h-c);
		}
	}
}

void parTrain(int& nTasks,int& nPos, std::vector<std::vector<std::vector<long>>>& tables, std::vector<classifier>& classf, std::vector<feature>& feats ){//OK
	std::vector<std::thread> threads;
	for(int i=0;i<nTasks;i++)
		threads.push_back(std::thread(train,nTasks,i,nPos,tables,classf,feats));

	for(int i=0;i<nTasks;i++)
		threads[i].join();
}


//Q2.2
bool error(classifier& classf, bool c,feature& feat,std::vector<std::vector<long>>& sat){ ////OK
	return classf.calc(calcFeat(sat,feat))!=c ;
}

void chooseClasf(int& nTasks, int taskId, int& nPos, double& currerr,int& ind,
std::vector<classifier>& classf, std::vector<double>& weights,
std::vector<feature>& feats, std::vector<std::vector<std::vector<long>>>& tables){
	//TODO
	// Added arguments:
	// weights, c, feats, tables
	// Modifies error and ind to the
	// min err and his index
	double locerr = 0;
	
	for(int i = taskId; i < classf.size(); i+=nTasks)
	{
		// Initialize the weighted error
		for(int j = 0; j < weights.size(); ++j)
		{
			if(error(classf[i], i<nPos , feats[i], tables[j]))
				locerr += weights[j];
		}
		
		
		if(i==0) { // Initialize error
			currerr = locerr;
			ind = 0;
		} else if(currerr < locerr) { // Take the min
			currerr = locerr;
			ind = i;			
		}
		
		// reinit
		locerr = 0;
	}
}

int parChooseClasf(int& nTasks, int& nPos, double& currerr,
std::vector<classifier>& classf, std::vector<double>& weights,
std::vector<feature>& feats, std::vector<std::vector<std::vector<long>>>& tables) {
	int ind=0;
	std::vector<std::thread> threads;
	std::vector<double> err(nTasks); // vector of min err for every task
	std::vector<int> indices(nTasks); // Vector of argmin (error)
	
	for(int i=0;i<nTasks;i++)
		threads.push_back(std::thread(chooseClasf,nTasks,i,nPos,err[i],indices[i],classf,weights,feats,tables));

	for(int i=0;i<nTasks;i++)
		threads[i].join();
	
	for(int i = 0; i < nTasks; ++i)
	{
		if(i==0) { // Init
			currerr = err[i];
			ind = indices[i];
		} else if(currerr < err[i]) { // Take the min
			currerr = err[i]; // Update error
			ind = indices[i]; // Update argmin(error)
		}
	}
	
	return ind;
}

void updateWeights(int& nTasks, int Taskid,std::vector<double>& weights,double& alfak,classifier& classf, std::vector<std::vector<std::vector<long>>>& tables, bool c, std::vector<feature>& feats, int clas){
	//TODO
	for(int i = Taskid; i < weights.size(); i+=nTasks)
	{
		if(c) weights[i] *= exp(alfak*classf.calc(calcFeat(tables[i],feats[clas]))); // Conferir, pas sur...
	}
}

void parUpdateWeights(std::vector<double>& weights,double& alfak,classifier& classf, std::vector<std::vector<std::vector<long>>>& tables, int& nTasks, int& Npos, int& clas){
	//TODO
	std::vector<std::thread> threads;
	
	for(int i=0;i<nTasks;i++)
		threads.push_back(std::thread(updateWeights,nTasks,i,weights,alfak,classf,tables, i<Npos, clas));
	
	for(int i=0;i<nTasks;i++)
		threads[i].join();
	
	double sum = 0; // compute sum to normalise
	for(int i = 0; i < weights.size(); ++i) // can be parallelized
	{
		sum+= weights[i];
	}
	
	for(int i = 0; i < weights.size(); ++i)
	{ // normalising weigths
		weights[i] /= sum;
	}
	
}

std::vector<double> boost(int& nTasks,int& nPos, std::vector<classifier>& classf,std::vector<std::vector<std::vector<long>>>& tables, std::vector<feature>& feats){//OK
	std::vector<double> weights(tables.size(),1.0/tables.size());
	std::vector<double> f(classf.size(),0);
	int clas=0;
	double error=0,alfak;
	int N=tables.size()/5;

	for(int k=0;k<N;k++){
		clas=parChooseClasf(nTasks,nPos,error,classf,weights,feats,tables);
		alfak=log((1-error)/error)/2;
		f[clas]+=alfak;
		parUpdateWeights(weights,alfak,classf[clas],tables, nTasks,nPos,clas);
	}
	return f;
}

int F(std::vector<double>& alfa, std::vector<feature>& feats,std::vector<classifier>& classf, std::vector<std::vector<long>>& sat,double theta){//OK
	double fNx=0,f=0,w=0,x;
	int h;

	for(int i=0;i<feats.size();i++){
		w=alfa[i];

		if(w){
			f+=w;
			x=calcFeat(sat,feats[i]);
			h=classf[i].calc(x);
			fNx+=w*h;
		}
	}

	if(fNx>=theta*f)
		return 1;
	else
		return -1;
}

void parF(int& nTasks, int taskId, int& nPos, std::vector<long>& fauxNP, std::vector<double>& weights,std::vector<feature>& feats,std::vector<classifier>& classf, std::vector<std::vector<std::vector<long>>>& sats,double theta){
	for(int i=taskId;i<sats.size();i+=nTasks){
		if(i<nPos){
			if(F(weights,feats,classf,sats[i],theta)<0)
				fauxNP[0]++;
		}
		else{
			if(F(weights,feats,classf,sats[i],theta)>0)
				fauxNP[1]++;
		}
	}
}

std::vector<long> test(int& nTasks, std::vector<double>& weights, std::vector<feature>& feats, int& nPos,
		std::vector<classifier>& classf, std::vector<std::vector<std::vector<long>>>& sats,double theta){
	std::vector<std::thread> threads;
	std::vector<std::vector<long>> fauxNP(nTasks,std::vector<long>(2,0));

	for(int i=0;i<nTasks;i++)
		threads.push_back(std::thread(parF,nTasks,i,nPos,fauxNP[i],weights,feats,classf,sats,theta));

	for(int i=0;i<nTasks;i++)
		threads[i].join();

	for(int i=1;i<nTasks;i++){
		fauxNP[0][0]+=fauxNP[i][0];
		fauxNP[0][1]+=fauxNP[i][1];
	}

	return fauxNP[0];
}




