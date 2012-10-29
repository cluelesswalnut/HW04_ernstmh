#include <ernstmhStarbucks.h>
#include <ernstmhStarbucks.cpp>
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include <iostream>
#include <fstream>
#include <string>
#include <node.cpp>
#include <math.h>
#include <Starbucks.h>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_ernstmhApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );
	void update();
	void draw();
	//node* insert(node* r, node* b, bool x);
	//node* neer(node* rr, node* c, float x, float y, bool xx);
	Entry* slow(Entry* a, float x, float y, int l);
};

/*node* HW04_ernstmhApp::insert(node* r, node* b, bool x){
	if(r == NULL){
		return b;
	}
	else {
		//return r;
	};
	if(x){
		if(b->e.x <= r->e.x){
			r->left = insert(r->left, b, !x);
		}
		else if(b->e.x > r->e.x){
			r->right = insert(r->right, b, !x);
		};
	}
	else{
		if(b->e.y <= r->e.y){
			r->left = insert(r->left, b, !x);
		}
		else if(b->e.y > r->e.y){
			r->right = insert(r->right, b, !x);
		};
	};
	return r;
};

node* HW04_ernstmhApp::neer(node* r, node* cc, float x, float y, bool t){
	node* c = cc;
	if(r != NULL){
		if(r->e.x == x && r->e.y == y){
			return r;
		}
		else if(c->e.x == x && c->e.y == y){
			return c;
		};
		float dis = sqrt(pow(c->e.x - x, 2) + pow(c->e.y - y, 2));
		if(dis > sqrt(pow(r->e.x - x, 2) + pow(r->e.y - y, 2))){
			c = r;
		};
		if(t){
			if(x <= r->e.x){
				c = neer(r->left, c, x, y, !t);
			}
			else if(x > r->e.x){
				c = neer(r->right, c, x, y, !t);
			};
			dis = sqrt(pow(c->e.x - x, 2) + pow(c->e.y - y, 2));
			if(dis > abs(x - r->e.x)){
				if(x <= r->e.x){
					c = neer(r->right, c, x, y, !t);
				}
				else if(x > r->e.x){
					c = neer(r->left, c, x, y, !t);
				};
			};
		}
		else{
			if(y <= r->e.y){
				c = neer(r->left, c, x, y, !t);
			}
			else if(y > r->e.y){
				c = neer(r->right, c, x, y, !t);
			};
			dis = sqrt(pow(c->e.x - x, 2) + pow(c->e.y - y, 2));
			if(dis > abs(y - r->e.y)){
				if(y <= r->e.y){
					c = neer(r->right, c, x, y, !t);
				}
				else if(y > r->e.y){
					c = neer(r->left, c, x, y, !t);
				};
			};
		};
	};
	return c;
};*/

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

// this whole first block just goes through the file to find the length of it
ifstream file ( "Starbucks_2006.csv" );
string value;
string ap;
int length = 0;
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
Entry *s = new Entry[length];


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



//old code for making the tree
	/*node* one = new node(s[0], 0);
	for(int i = 1; i < length; i++){
		insert(one,new node(s[i], i),true);
	};*/

//construct the object
ernstmhStarbucks* test = new ernstmhStarbucks;
//call the build function
test->build(s,length);
Entry* wut;
//call the getNearest function
float a = 0.484554;
float b = 0.46761343;
wut = test->getNearest(a,b);
console() << wut->identifier << endl;
console() << (slow(s, a, b, length))->identifier << endl;
};

void HW04_ernstmhApp::mouseDown( MouseEvent event )
{
}

void HW04_ernstmhApp::update()
{
}

void HW04_ernstmhApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04_ernstmhApp, RendererGl )
