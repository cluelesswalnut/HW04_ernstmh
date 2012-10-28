#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include <fstream>
#include <string>
#include <node.cpp>
#include <math.h>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_ernstmhApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	node* insert(node* r, node* b, bool x);
	node* neer(node* rr, node* c, float x, float y, bool xx);
	int slow(float** a, float x, float y, int l);
};

node* HW04_ernstmhApp::insert(node* r, node* b, bool x){
	if(r == NULL){
		return b;
	}
	else {
		//return r;
	};
	if(x){
		if(b->x <= r->x){
			r->left = insert(r->left, b, !x);
		}
		else if(b->x > r->x){
			r->right = insert(r->right, b, !x);
		};
	}
	else{
		if(b->y <= r->y){
			r->left = insert(r->left, b, !x);
		}
		else if(b->y > r->y){
			r->right = insert(r->right, b, !x);
		};
	};
	return r;
};

node* HW04_ernstmhApp::neer(node* r, node* cc, float x, float y, bool t){
	node* c = cc;
	if(r != NULL){
		if(r->x == x && r->y == y){
			return r;
		}
		else if(c->x == x && c->y == y){
			return c;
		};
		float dis = sqrt(pow(c->x - x, 2) + pow(c->y - y, 2));
		if(dis > sqrt(pow(r->x - x, 2) + pow(r->y - y, 2))){
			c = r;
		};
		if(t){
			if(x <= r->x){
				c = neer(r->left, c, x, y, !t);
			}
			else if(x > r->x){
				c = neer(r->right, c, x, y, !t);
			};
			dis = sqrt(pow(c->x - x, 2) + pow(c->y - y, 2));
			if(dis > abs(x - r->x)){
				if(x <= r->x){
					c = neer(r->right, c, x, y, !t);
				}
				else if(x > r->x){
					c = neer(r->left, c, x, y, !t);
				};
			};
		}
		else{
			if(y <= r->y){
				c = neer(r->left, c, x, y, !t);
			}
			else if(y > r->y){
				c = neer(r->right, c, x, y, !t);
			};
			dis = sqrt(pow(c->x - x, 2) + pow(c->y - y, 2));
			if(dis > abs(y - r->y)){
				if(y <= r->y){
					c = neer(r->right, c, x, y, !t);
				}
				else if(y > r->y){
					c = neer(r->left, c, x, y, !t);
				};
			};
		};
	};
	return c;
};

int HW04_ernstmhApp::slow(float** r, float x, float y, int l){
	float dis = 2;
	float hold;
	int sb = -1;
	for(int i = 0; i < l; i++){
		hold = sqrt(pow(r[i][0] - x, 2) + pow(r[i][1] - y, 2));
		if(dis > hold){
			dis = hold;
			sb = i;
		};
	};
	return sb;
};

void HW04_ernstmhApp::setup()
{

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

float **sb = new float* [length];
for (int i = 0; i < length; i++)
{
    sb[i] = new float[2];
};
float wtf = 0.134;
sb[0][0] = wtf;

ifstream fl ( "Starbucks_2006.csv" );

length = 0;
while ( fl.good() )
{

     getline ( fl, value, ',' );
	 getline ( fl, value, ',' );
	 //console() << value << endl;
	 t = (float)atof(value.c_str()); 
	 sb[length][0] = t;

	value = fl.get();
	ap = fl.get();
	value.append(ap);
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

	//console() << value << endl;
	t = (float)atof(value.c_str()); 
	sb[length][1] = t;
	length++;
};

//console() << sb[0][0] << endl;
for(int i = 0; i < 20; i++){
	console() << sb[i][0] << endl;
	console() << sb[i][1] << endl;
	console() << i << endl;
};

// build tree
/*node* one = new node(sb[0][0], sb [0][1]);
node* two = new node(sb[0][0], sb [1][1]);
//console() << NULL << endl;
insert(one, two, true);

console() << one->left->x << endl;*/

node* one = new node(sb[0][0], sb [0][1], 0);
for(int i = 1; i < length; i++){
	insert(one,new node(sb[i][0], sb [i][1], i),true);
};

console() << one->left->x << endl;
console() << one->right->x << endl;
console() << one->left->right->left->x << endl;
console() << one->left->left->x << endl;

node* hope = neer(one,one,0.261317,0.233164,true);
console() << hope->num << endl;
console() << slow(sb, 0.261317, 0.233164, length) << endl;
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
