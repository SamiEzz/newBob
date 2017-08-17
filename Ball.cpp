/*
 * @file Ball.cpp
 * @brief Get the position of the ball
 * . Load calibration data
 * . Find all pixels with level > threshold
 * . Make the average of the position of these pixels
 * . Return the average position                 
 * @date august 2014
 * @version 1
 */ 

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <sys/time.h>
#include <stdlib.h>  
#include <math.h> 

#include "Ball.h"
#include "StartData.h"
#include "Ppm.h"
using namespace std;

unsigned long getmsofday() {
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return (long long)tv.tv_sec*1000 + tv.tv_usec/1000;
}

struct POS getPosBall(struct BUF b){
	struct POS position;
	int indice=0;
	int ball[2]={0,0};
	int max=0;
	int borders[4]={75,35,45,5};
	int somme = 0;
		for(int i=0;i<40;i++){
			for(int j=0;j<40;j++){	
				somme=0;
				for(int l=0;l<5;l++){
					for(int k=0;k<5;k++){
						indice=(borders[1]+l+j*5)*320+borders[2]+i*5+k;
						//cout << indice << " ";
						somme += (int)b.BUFFER[indice];
					}
					//cout << "," << endl;
				}
				//cout << "moyenne : " << somme/200 << endl;
				if(somme>max){max=somme;position.X=i;position.Y=j;}
				
			}
			//cout << ", " << endl;
		}
		cout << "\nball in : " << position.X << " , " << position.Y << endl;

		//cout << "max : " << moyenne << endl;
		//cin >> pause;
		position.DETECTIONOK=true;
		return position;
}
