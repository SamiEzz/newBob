/*
 * @file Ppm.cpp
 * @brief Write or Open a PPM image                
 * @date august 2014
 * @version 1
 */ 

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>

#include "Ppm.h"
#include "StartData.h"

using namespace std;

int WriteImage(const char fname[], struct BUF b){
	ofstream ofp;
	ofp.open(fname, ios::out | ios::binary);
	if (!ofp) {
		cout << "Can't open file: " << fname << endl;
       		exit(1);
	}
 
	ofp << "P5" << endl;
	ofp << b.WIDTH << " " << b.HEIGHT << endl;
	ofp << "255 "<< endl;

	long l = b.WIDTH*b.HEIGHT;
	for(long k = 0; k < l; k=k+1) {
		ofp.write( (char *)b.BUFFER +k+1, 1);
		if (ofp.fail()){
		cout << "Can't write image " << fname << endl;
		exit(0);
		}
	}
	ofp.close();
	return(1);
}


struct BUF OpenImage(const char fname[]) {
	struct BUF b;
	ifstream ifp(fname, ios::in | ios::binary);
        std::string line;
        // Read the p5
        getline(ifp, line);
        // Read width and height;
        getline(ifp, line);
        std::istringstream iss(line);
      
        if (!(iss >> b.WIDTH >> b.HEIGHT)) { 
           cerr << "Unreadable image " << fname << endl; 
           exit(-1);
        }
        getline(ifp, line);
        b.BUFFER = (unsigned char *)malloc( b.HEIGHT*b.WIDTH );
	ifp.read((char *)b.BUFFER,b.HEIGHT*b.WIDTH);
 	ifp.close();
        return b;
}




