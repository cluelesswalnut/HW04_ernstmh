

class node{
public:
	node();
	node(Entry ee, int o);
	node* left;
	node* right;
	Entry e;
	int num;
};

node* insert(node* r, node* b, bool x);
node* neer(node* rr, node* c, float x, float y, bool xx);