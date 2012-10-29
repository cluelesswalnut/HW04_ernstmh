#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "Starbucks.h"

using namespace ci;
using namespace ci::app;
using namespace std;

node::node(){
	left = NULL;
	right = NULL;
	e.x = NULL;
	e.y = NULL;
	num = NULL;
};

node::node(Entry ee, int o){
	left = NULL;
	right = NULL;
	e = ee;
	num = o;
};

node* insert(node* r, node* b, bool x){
	// return the node to be inserted if the next place is empty
	if(r == NULL){
		return b;
	}
	else {
	};
	//if it is on an x level do this
	if(x){
		// go left or right in the tree depending on if the entry value is greater than or less than that of the current node
		if(b->e.x <= r->e.x){
			r->left = insert(r->left, b, !x);
		}
		else if(b->e.x > r->e.x){
			r->right = insert(r->right, b, !x);
		};
	}
	// same thing using y values if the code is on a y level
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

node* neer(node* r, node* cc, float x, float y, bool t){
	node* c = cc;
	// if last node hasn't been reached find the next node to go to
	if(r != NULL){
		//if the node is equal the the desired location return that node
		if(r->e.x == x && r->e.y == y){
			return r;
		}
		else if(c->e.x == x && c->e.y == y){
			return c;
		};
		// find the distance to the current nearest node and compare it to the distance to the current node
		// save the lesser one
		float dis = sqrt(pow(c->e.x - x, 2) + pow(c->e.y - y, 2));
		if(dis > sqrt(pow(r->e.x - x, 2) + pow(r->e.y - y, 2))){
			c = r;
		};
		// if on an x level
		if(t){
			// folow the tree down
			if(x <= r->e.x){
				// set the neerest starbucks to the nearest starbucks so far
				c = neer(r->left, c, x, y, !t);
			}
			else if(x > r->e.x){
				c = neer(r->right, c, x, y, !t);
			};
			//if the oposite side of the tree is in the range of the shortest distance so far, then also search that side of the tree
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
		// same thing for y values if on the y level
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
};