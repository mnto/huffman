#include <iostream>

struct hnode {
	unsigned char letter;
	size_t count;		
	hnode *left;
	hnode *right;
	hnode(unsigned char c, size_t num, hnode *l = NULL, hnode *r = NULL):
		letter(c), count(num), left(l), right(r) {}
};	