#pragma once
#include "Starbucks.h"
#include "node.h"

class ernstmhStarbucks : public Starbucks {

public:
	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
	node* r;

};