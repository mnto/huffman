#include <iostream>
#include "hnode.h"
#include "heap.h"

class priqueue {
public:
	typedef hnode* element;
	priqueue(size_t (*pri)(const element &));
	void add(const element &);
	void remove();
	size_t size();
	element front();
	
private:
	struct node {
		element data;
		node *next;
		node(const element &, node *);
	};

	size_t (*pri)(const element &);  
	size_t _size;
	node * _front;
	void _add_helper(const element &, node * &); 
};