#include <ernstmhStarbucks.h>
#include <ernstmhStarbucks.cpp>
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include <iostream>
#include <fstream>
#include <string>
#include <node.cpp>
#include <math.h>
#include <Starbucks.h>

using namespace ci;
using namespace ci::app;
using namespace std;

//this code complets parts A, B and G
//Markus Ernst

class HW04_ernstmhApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );
	void update();
	void draw();
	/**set the three parts of a pixel using just the x and y value of and the color
	*/
	void setPixel(uint8_t* ar, int x,int y, Color8u c);
	/**get the color of a pizel
	*/
	Color8u pixelColor(uint8_t* ar, int x,int y);
	/**
	*draw a rectangle givent he top left corner and its width and hight
	*/
	void drawRect(uint8_t* ar, int x,int y, int w, int h, Color8u c);

	//node* insert(node* r, node* b, bool x);
	//node* neer(node* rr, node* c, float x, float y, bool xx);
	Entry* slow(Entry* a, float x, float y, int l);
private:
	Surface mySurface_;
	uint8_t* pixelArray;
	float cx, cy, lcx, lcy;
	int length,lc1,lc2;
	Entry* s;
	Entry* cen1;
	Entry* cen2;
	ernstmhStarbucks* test;
	Entry* wut;
	int p1[6][4];
	int p2[6][4];
	int nsb[6][4];
	int pcs[6][4];
	int sh[6][4];
	int xscale, yscale;
};

void HW04_ernstmhApp::setPixel(uint8_t* ar, int x,int y, Color8u c)
{
	//set all three of the colors individually using the cordinates of the pixel
	//1024
	ar[y * 574 * 3 + 3 * x] = c.r;
	ar[y * 574 * 3 + 3 * x + 1] = c.g;
	ar[y * 574 * 3 + 3 * x + 2] = c.b;

};

Color8u HW04_ernstmhApp::pixelColor(uint8_t* ar, int x,int y)
{
	Color8u c;
	//get all three of the colors individually using the cordinates of the pixel
	//1024
	c.r = ar[y * 574 * 3 + 3 * x];
	c.g = ar[y * 574 * 3 + 3 * x + 1];
	c.b = ar[y * 574 * 3 + 3 * x + 2];
	return c;
};


void HW04_ernstmhApp::drawRect(uint8_t* ar, int x,int y, int w, int h, Color8u c)
{
	//loop through all of the pixels in the rectangle and change their color
	for(int i = x; i < x + w; i++){
		for(int j = y; j < y + h; j++){
			setPixel(ar, i, j, c);
		};
	};

};

// this method computer the nearest starbucks by checking all of them
// i use this to check my answers
Entry* HW04_ernstmhApp::slow(Entry* r, float x, float y, int l){
	float dis = 2;
	float hold;
	Entry* sb;
	for(int i = 0; i < l; i++){
		hold = sqrt(pow(r[i].x - x, 2) + pow(r[i].y - y, 2));
		if(dis > hold){
			dis = hold;
			sb = &r[i];
		};
	};
	return sb;
};

void HW04_ernstmhApp::setup()
{
	// variables for the scaling of the starbucks coordinates
	xscale = 610;
	yscale = 340;
	//making the us picture the background
	mySurface_ = loadImage("fitmap.jpg");

uint8_t* pixelArray = (mySurface_).getData();
// this whole first block just goes through the file to find the length of it
ifstream file ( "Starbucks_2006.csv" );
string value;
string ap;
length = 0;
cy = .0001;
cx = .0001;
char c;
while ( file.good() )
{

     getline ( file, value, ',' );
	 getline ( file, value, ',' );
	 value = file.get();
	 ap = file.get();
	 value.append(ap);
	 for(int i = 0; i < 1;){
		c = file.get();
		if(c == '0' ||  c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9'){
			ap = c;
			value.append(ap);
		}
		else{
			i = 1;
		};
	};
	length++;
};


file.close();

float t;
s = new Entry[length];


// this is the second time i go through the file and it actually saves the entries
ifstream fl ( "Starbucks_2006.csv" );

length = 0;
while ( fl.good() )
{
	// gets the Identifier portion of the starbucks and saves it
     getline ( fl, value, ',' );
	 s[length].identifier = value;

	 // this gets the x cordinate and turns it into a float and saves it
	 getline ( fl, value, ',' );
	 t = (float)atof(value.c_str()); 
	 s[length].x = t;

	 // this code is more complicated as the getline function would not stop at the end of a line
	//add the first digit to value
	value = fl.get();
	//add the second digit of value
	ap = fl.get();
	value.append(ap);
	// continue adding the next digit untill the next charachter is not a number
	for(int i = 0; i < 1;){
		c = fl.get();
		if(c == '0' ||  c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9'){
			ap = c;
			value.append(ap);
		}
		else{
			i = 1;
		};
	};

	//convert that string of digits into a float and add it to the entry
	t = (float)atof(value.c_str()); 
	s[length].y = t;
	//increment the place in the array
	length++;
};

fl.close();

//check the number of entries in census 2000
ifstream c1 ( "Census_2000.csv" );
lc1 = 0;
float lat, lon;
float trash;
while ( c1.good() )
{
	for (int i =0; i <=3; i++){
					getline(c1, value, ',');
				}

				c1 >> trash;

				 c1.get();					
				 c1 >> trash;

				 c1.get();					 
				 c1 >> trash;
				 lc1++;
};
c1.close();
//creat the array of entries for census 2000
cen1 = new Entry[lc1];

lc1 = 0;

//fill the array of entries for census 2000
ifstream c11 ( "Census_2000.csv" );
lc1 = 0;
while ( c11.good() )
{
	//skip the first values
	for (int i =0; i <=3; i++){
					getline(c11, value, ',');
				}
				
				// get the population nunber
				c11 >> cen1[lc1].pop;

				//get rid of the comma
				 c11.get();
				 // get the x coordinate
				 c11 >> cen1[lc1].x;

				 //get rid of the comma
				 c11.get();
				 //get the y coordinate
				 c11 >> cen1[lc1].y;
				 lc1++;
};
c11.close();

// repeat the exact same thing for cnesus 2010
ifstream c2 ( "Census_2010.csv" );
lc2 = 0;
while ( c2.good() )
{
	for (int i =0; i <=3; i++){
					getline(c2, value, ',');
				}

				c2 >> trash;

				 c2.get();
				 c2 >> trash;

				 c2.get();
				 c2 >> trash;
				 lc2++;
};
c2.close();
cen2 = new Entry[lc2];

lc2 = 0;

ifstream c22 ( "Census_2010.csv" );
while ( c22.good() )
{
	for (int i =0; i <=3; i++){
					getline(c22, value, ',');
				}

				c22 >> cen2[lc2].pop;

				 c22.get();
				 c22 >> cen2[lc2].x;

				 c22.get();
				 c22 >> cen2[lc2].y;
				 lc2++;
};

c22.close();

// fill the arrays for fiding the change in population per starbucks in an area
for(int i = 0; i < 6; i++){
	for(int j = 0; j < 4; j++){
		p1[i][j] = 0;
		p2[i][j] = 0;
		nsb[i][j] = 0;
	};
};
// count the total population number in each of the regions from census 2000
for(int i = 0; i < lc1; i++){
	p1[(int)(cen1[i].x * xscale)/100][(int)((1-cen1[i].y) * yscale)/100] = p1[(int)(cen1[i].x * xscale)/100][(int)((1-cen1[i].y) * yscale)/100] + cen1[i].pop;
};

// count the total population number in each of the regions from census 2010
for(int i = 0; i < lc2; i++){
	p2[(int)(cen2[i].x * xscale)/100][(int)((1-cen2[i].y) * yscale)/100] = p2[(int)(cen2[i].x * xscale)/100][(int)((1-cen2[i].y) * yscale)/100] + cen2[i].pop;
};

//count the total number of starbucks in each region
for(int i = 0; i < length; i++){
	nsb[(int)(s[i].x * xscale)/100][(int)((1-s[i].y) * yscale)/100]++;
};

//find the ration of population change to number of starbucks in the area
for(int i = 0; i < 6; i++){
	for(int j = 0; j < 4; j++){
		if(nsb[i][j] != 0){
			pcs[i][j] = (p2[i][j]-p1[i][j])/nsb[i][j];
		}
		else{
			pcs[i][j] = 0;
		};
	};
};

// find the scale by wich to change the brightness of color to show the amount of change
double color = 0;
for(int i = 0; i < 6; i++){
	for(int j = 0; j < 4; j++){
		color = color + pcs[i][j];
	};
};

color = color/24;
color = color/150;

//set the color for each region
// the darker the color the less change occured
for(int i = 0; i < 6; i++){
	for(int j = 0; j < 4; j++){
		sh[i][j] = pcs[i][j]/color;
	};
};

// color each pixel the color if its region
for(int i = 0; i < 600; i++){
	for(int j = 0; j < 380; j = j++){
		// if the pixel is part of the us shape
		if(pixelColor(pixelArray,i,j) != Color8u(0,0,0)){
			//if the area hadpositive population change color it red
			if(sh[i/100][j/100] > 0){
			setPixel(pixelArray, i, j, Color8u(sh[i/100][j/100],0,0));
			}
			//if the area had negative change color it blue
			else{
				setPixel(pixelArray, i, j, Color8u(0,0,-1 * sh[i/100][j/100]));
			};
		};
	};
};

// draw the deviding lines
for(int i = 0; i < 600; i = i + 100){
	for(int j = 0; j < 380; j = j++){
		setPixel(pixelArray, i, j, Color8u(0,0,150));
	};
};
for(int i = 0; i < 400; i = i + 100){
	for(int j = 0; j < 570; j = j++){
		setPixel(pixelArray, j, i, Color8u(0,0,255));
	};
};


// draw the starbucks
for(int i = 0; i <= length; i++){
	setPixel(pixelArray, s[i].x * xscale, (1-s[i].y) * yscale, Color8u(50, 205, 50));
};

//construct the object
test = new ernstmhStarbucks;
//call the build function
test->build(s,length);

//float a = 0.484554;
//float b = 0.46761343;
//console() << (slow(s, a, b, length))->identifier << endl;
//call the getNearest function
//wut = test->getNearest(a,b);
//console() << wut->identifier << endl;
};

void HW04_ernstmhApp::mouseDown( MouseEvent event )
{
	//save the last and the current click
	lcx = cx;
	lcy = cy;
	cx = (float)event.getX()/(xscale * 1.0);
	cy = (float)(1 - event.getY()/(yscale * 1.0));

}

void HW04_ernstmhApp::update()
{
	uint8_t* pixelArray = (mySurface_).getData();

	//fill the color of each region
	for(int i = 0; i < 600; i++){
	for(int j = 0; j < 380; j = j++){
		if(pixelColor(pixelArray,i,j) != Color8u(0,0,0)){
			if(sh[i/100][j/100] > 0){
			setPixel(pixelArray, i, j, Color8u(sh[i/100][j/100],0,0));
			}
			else{
				setPixel(pixelArray, i, j, Color8u(0,0,-1 * sh[i/100][j/100]));
			};
		};
	};
};

//draw the deviding lines
for(int i = 0; i < 600; i = i + 100){
	for(int j = 0; j < 380; j = j++){
		setPixel(pixelArray, i, j, Color8u(0,0,150));
	};
};
for(int i = 0; i < 400; i = i + 100){
	for(int j = 0; j < 570; j = j++){
		setPixel(pixelArray, j, i, Color8u(0,0,255));
	};
};
	//draw the starbucks
	for(int i = 0; i <= length; i++){
		setPixel(pixelArray, s[i].x * xscale, (1-s[i].y) * yscale, Color8u(50, 205, 50));
	};

	//find and draw the neerest starbucks to the click
	wut = test->getNearest(cx,cy);
	drawRect(pixelArray, ((wut->x) * xscale)-1, ((1 - wut->y) * yscale) - 1, 3, 3, Color8u(255, 255, 0));
}

void HW04_ernstmhApp::draw()
{

	gl::draw(mySurface_);
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04_ernstmhApp, RendererGl )
