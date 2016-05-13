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
    //img must be int- or char-typed
    using namespace cimg_library;
    std::vector<std::vector<long>> sat;
    std::vector<long> row;
    long init=0;
    std::vector<std::vector<long>>::iterator it;
    std::vector<long>::iterator i,j;

    
    for(int y=0;y<img.height();y++){//init first row
        init+=img(0,y);
        row.push_back(init);
    }

    row.clear();
    it=sat.begin();
    for (int x=1; x<img.width(); x++,sat.push_back(row),it++,row.clear()) {
        // iterating through: it,x-> rows; i,y->columns in current row; j->columns previous row
       
        //initialization
        j=it->begin();
        row.push_back( *j++ + img(x,0));
        i=row.begin();
        
        //column iteration
        for (int y=1; y<img.height(); y++,i++,j++)
                row.push_back(img(x,y) + *j + *i - *(j-1));
    }
    return sat;
}

//Q1.2
void initAndScanRow(const cimg_library::CImg<long>& img,std::vector<long> row, int i){
    long init=0;
    for(int y=0;y<img.height();y++){//initialize (summed) i-th row
        init+=img(i,y);
        row.push_back(init);
    }
}

void scanCollumn(std::vector<std::vector<long>> sat,int i){
    long init=0;
    for(int x=0;x<img.width();x++){//sum i-th column
        init+=sat[x][i];
        sat[x][i]=init;
    }
}

std::vector<std::vector<long>> parSAT(const cimg_library::CImg<long>& img){
    std::vector<std::vector<long>> sat = new std::vector<std::vector<long>>(img.height(), std::vector<long>());
    std::vector<std::thread> rowSum, columnSum;

    for (int i=0; i<img.width(); i++)   //init and scan rows
        rowSum.push_back(std::thread(initAndScanRow(img,sat[i],i)));
    for (int i=0; i<img.width(); i++)
        rowSum[i].join();
    
    for (int i=0; i<img.height(); i++)  //scan columns
        columnSum.push_back(std::thread(scanCollumn(sat,i)));
    for (int i=0; i<img.height(); i++)
        columnSum[i].join();
    
    return sat;
}


