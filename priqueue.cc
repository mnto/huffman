#include "priqueue.h"

priqueue::priqueue(size_t (*p)(const element &)) : 
	pri(p), _size(0), _front(NULL) {}

void priqueue::add(const element & item)
{
	_add_helper(item, _front);
	_size++;
}

void priqueue::_add_helper(const element & item, node * & p)
{
	if (p == NULL or pri(item) < pri(p->data))
		p = new node(item, p);  // insert on the front.
	else
		_add_helper(item, p->next);
}

size_t priqueue::size()
{
	return _size;
}

void priqueue::remove()
{
	node * p = _front->next;
	delete _front;
	_front = p;
	_size--;
}

priqueue::element priqueue::front()
{
	return _front->data;
}

priqueue::node::node(const element & item, node * n):
	data(item), next(n) {}



