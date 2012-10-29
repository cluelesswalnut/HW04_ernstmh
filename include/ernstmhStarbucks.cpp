#pragma once
#include "ernstmhStarbucks.h"


void ernstmhStarbucks::build(Entry* c, int n){
	r = new node(c[0], 0);
	for(int i = 1; i < n; i++){
		insert(r,new node(c[i], i),true);
	};
}

Entry* ernstmhStarbucks::getNearest(double x, double y){
	
	node* hope = neer(r,r,x,y,true);
	return &hope->e;

}