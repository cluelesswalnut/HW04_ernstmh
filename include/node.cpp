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

node* neer(node* r, node* cc, float x, float y, bool t){
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
};