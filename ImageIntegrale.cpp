#include <iostream>
#include <vector>
#include <cstdlib>
#include "CImg.h"
#include "ImageIntegrale.h"

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
std::vector<std::vector<long>> SAT(const cimg_library::CImg<long>& img){//summed area table
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

    row.clear();
    it=sat.begin();
    for (int x=1; x<img.width(); x++,sat.push_back(row),it++,row.clear()) {
        // iterating through: it,x-> rows; i,y->columns in current row; j->columns previous row
       
        //initialization
        j=it->begin();
        row.push_back( *j++ + img(x,0,0));
        i=row.begin();
        
        //column iteration
        for (int y=1; y<img.height(); y++,i++,j++)
                row.push_back(img(x,y,0) + *j + *i - *(j-1));
    }
    return sat;
}

//Q1.2
class feature{
	feature(int xx, int yy, int ww,int hh,char c){
		x=xx;
		y=yy;
		w=ww;
		h=hh;
		type=c;
	}
};

long calcFeat(std::vector<std::vector<long>> sat, feature f){
	switch(f.type){
	case 'a':
		return 2*sat[f.x+f.w/2][f.y]-2*sat[f.x+f.w/2][f.y+f.h]-sat[f.x][f.y]+sat[f.x][f.y+f.h]-sat[f.x+f.w][f.y]+sat[f.x+f.w][f.y+f.h];

	case 'b':
		return 2*sat[f.x+f.w][f.y+f.h/2]-2*sat[f.x][f.y+f.h/2]+sat[f.x][f.y]+sat[f.x][f.y+f.h]-sat[f.x+f.w][f.y]-sat[f.x+f.w][f.y+f.h];

	case 'c': //////////TODO
		return -sat[f.x][f.y]+sat[f.x][f.y+f.h]+sat[f.x+f.w][f.y]-sat[f.x+f.w][f.y+f.h]+2*sat[f.x+f.w/3.0][f.y]-2*sat[f.x+f.w/3.0][f.y+f.h]-2*sat[f.x+2*f.w/3.0][f.y]+2*sat[f.x+2*f.w/3.0][f.y+f.h];

	case 'd':///////////TODO
		return 2*(sat[f.x+f.w/2][f.y]+sat[f.x+f.w/2][f.y+f.h]+sat[f.x][f.y+f.h/2]+sat[f.x+f.w][f.y+f.h/2])-4*sat[f.x+f.w/2][f.y+f.h/2]-sat[f.x][f.y]-sat[f.x+f.w][f.y+f.h]-sat[f.x+f.w][f.y]-sat[f.x][f.y+f.h];
	}
	return 0;
}

void featVect(std::vector<feature>& feats, char type,int wMax, int hMax){
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
					feats.push_back(new feature(x,y,w,h,type));
			}
		}
	}
}

std::vector<feature> distFeat(int widht, int height){
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

std::vector<std::vector<std::vector<long> > > distII(){

}

void train(int nTasks, int taskId,int nPos, std::vector<std::vector<std::vector<long>>> tables, std::vector<classifier> classf, std::vector<feature> feats ){
	srand(taskId);
	double r,h.xki;
	int rr,c;
	for(int i=taskId;i<tables.size());i+=nTasks){
		classf[i].w1=1;
		classf[i].w2=0;
		int K=100000;
		double eps=0.5;

		for(int k=0;k<K;k++){
			r=srand()/RAND_MAX;
			rr=((int)r*tables.size()-1);

			xki=calcFeat(tables[i],feats[i]);
			if(classf[i].w1*xki+classf[i].w2>=0)
				h=1;
			else
				h=-1;

			if(rr<nPos)
				c=1;
			else
				c=-1;

			classf[i].w1-=eps*(h-c)*xki;
			classf[i].w2-=eps*(h-c);
		}
	}
}

void parTrain(int nTasks,int nPos, std::vector<std::vector<std::vector<long>>> tables, std::vector<classifier> classf, std::vector<feature> feats ){
	std::vector<std::thread> threads;
	for(int i=0;i<nTasks;i++)
		threads.push_back(std::thread(train,nTasks,i,nPos,tables,classf,feats));

	for(int i=0;i<nTasks;i++)
		threads[i].join();
}


