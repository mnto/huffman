#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "heap.h"

using namespace std;

const size_t _size = 256;
size_t counts[_size];
string codes[_size];

void print_tree(hnode *tree, size_t depth)
{
	// POST: print a tree horizontally with each node's data
	if (tree == NULL)
		return;
	print_tree(tree->right, depth +1);
	for (size_t i = 0; i < depth; i++)
		cout << "   ";
	cout << tree->letter << tree->count << endl;
	print_tree(tree->left, depth+1);
}

bool is_leaf(hnode *tree)
{
	// POST: return true if an hnode is a leaf, false otherwise
	return !tree->left;
}

void build_tree(heap & mheap)
{
	// PRE: the min heap is not empty and has at least two elements
	// POST: generate a tree using the given min heap
	while (mheap.size() != 1) {
		hnode *left = mheap.front();
		mheap.remove();
		hnode *right = mheap.front();
		mheap.remove();
		hnode *tree = new hnode((unsigned char)('*'), 
						left->count + right->count, left, right);
		mheap.add(tree);
	}
}

void encode(hnode *tree, string code, string ary[])
{
	// PRE: hnode *tree is not empty
	// POST: follow the path from the root to each leaf
	//       encode each path so that the left direction corresponds to 0,
	//       the right direction corresponds to 1. The code to each 
	//       character c is stored in ary[c]
	if (is_leaf(tree)) {
		ary[tree->letter] = code;
		return;
	}
	if (tree->left)
		encode(tree->left, code + '0', ary);
	if (tree->right) 
		encode(tree->right, code + '1', ary);
}

void writeTree (hnode *tree, ostream & ostr)
{
	// PRE: hnode *tree is not empty
	// POST: write the overhead to the out file by traversiing the tree 
	//       and representing the tree with ordinary characters
	//       L represents a leaf, followed by the character in that leaf
	//       I represents an internal node
	if (is_leaf(tree))
		ostr << 'L' << tree->letter;
	else{
		ostr << 'I';
		writeTree(tree->left, ostr);
		writeTree(tree->right, ostr);
	}
}

unsigned char bits_to_char(string bits)
{
	// PRE: bits is a string of 8 0's and 1's
	// POST: convert 8 bits to a character
	size_t i;
	unsigned char v;
	unsigned char sum = 0;
	for (i = 0, v = 128; v > 0; i++, v /= 2) {
		if (bits[i] == '1')
			sum += v;
	}
	return sum;
}

int main(int argc, char const *argv[])
{
	string infile = argv[1];
	ifstream in(infile.c_str());
	string outfile = infile + ".huf";
	ofstream out(outfile.c_str());
	char c;
	size_t fileSize = 0;
	string text;
	heap min;
	for (size_t i = 0; i < _size; i++) // assign 0 to all characters in counts
		counts[i] = 0;
	while (in.get(c)) {
		text += c;
		counts[(unsigned char)(c)]++; // store the occurence in counts
		fileSize++;
	}
	for (size_t i = 0; i < _size; i++) { // create a min heap of hnodes
		if (counts[i] != 0) {
			hnode *_h = new hnode((unsigned char)(i), counts[i]);
			min.add(_h); 
		}
	}
	build_tree(min); // build tree from the min heap
	hnode *tree = min.front();
	encode(tree, "", codes);	
	string bits = "";
	out << fileSize;
	writeTree(tree, out);
	for (size_t j = 0; j < text.length(); j++)  // represent text in bits
		bits += codes[(unsigned char)(text[j])]; 
	while (bits.length() > 0) {
		if (bits.length() % 8 == 0) { // convert every 8 bits to a character
			out << bits_to_char(bits.substr(0, 8));
			bits = bits.substr(8);		
		}
		else // padding 0's to the end if lenght of bits is not divisible by 8
			bits += '0';
	}
	return 0;
}