#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "node.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

node::node(){
	left = NULL;
	right = NULL;
	x = NULL;
	y = NULL;
};

node::node(float a, float b){
	left = NULL;
	right = NULL;
	x = a;
	y = b;
};