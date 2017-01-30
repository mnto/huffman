#include "hnode.h"
#include <iostream>

using namespace std;

class heap
{
public:
	heap() {_size = 0;}
	size_t size() {return _size;} //POST: return the size of the heap
	void add(hnode *item) 
	{
		// POST: add an hnode in the min heap
		_data[_size++] = item;
		_reheap_up(_size - 1);
	}
	hnode * front() {return _data[0];} // POST: return the front hnode
	void remove() 
	{
		// POST: remove an hnode from the min heap
		_data[0] = _data[--_size];
		_reheap_down(0);
	}
	hnode * get(size_t pos)
	{
		return _data[pos];
	};

private:
	hnode *_data[500];
	size_t _size;
	void swap(size_t pos1, size_t pos2)
	{
		// POST: swap the two hnodes in position pos1 and position pos2
		hnode *temp = _data[pos1];
		_data[pos1] = _data[pos2];
		_data[pos2] = temp;
	}
	void _reheap_up(size_t pos) 
	{
		// POST: used when adding an hnode to remain the min heap structure
		if (pos == 0)	
			return;
		size_t par = (pos - 1) / 2; // position of the parent node
		if (_data[par]->count > _data[pos]->count) {
			swap(par, pos);
			_reheap_up(par);
		}
	}
	void _reheap_down(size_t pos)
	{
		// POST: used when removing an hnode to remain the min heap structure
		if (pos >= _size)	
			return;
		size_t left_child = 2 * pos + 1; // positiion of left child
		size_t right_child = 2 * pos + 2; // position of right child
		if (left_child >= _size)	
			return;
		size_t child = left_child;
		if (right_child < _size 
			and _data[right_child]->count < _data[left_child]->count) 
			// if right child is a better candidate
			child = right_child;
		if (_data[pos]->count > _data[child]->count) {
			swap(pos, child);
			_reheap_down(child);
		}
	}
};