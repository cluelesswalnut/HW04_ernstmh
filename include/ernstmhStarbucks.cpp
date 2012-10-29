#pragma once
#include "ernstmhStarbucks.h"


void ernstmhStarbucks::build(Entry* c, int n){
	//creat the root node of the tree
	r = new node(c[0], 0);
	//add all the nodes in c using the insert method
	for(int i = 1; i < n; i++){
		insert(r,new node(c[i], i),true);
	};
}

Entry* ernstmhStarbucks::getNearest(double x, double y){
	// call the neer method from node.cpp
	node* hope = neer(r,r,x,y,true);
	return &hope->e;

}