#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "hnode.h"

using namespace std;

bool is_leaf(hnode *tree)
{
	// POST: return if a hnode is a leaf, false otherwise
	return !tree->left;
}

hnode * readTree(istream & in)
{
	// POST: read the overhead from the input file and 
	//       recreate a tree similar to the original one
	char type = in.get();
	if (type == 'L')
		return new hnode(in.get(), 0);
	else {
		hnode *left = readTree(in);
		hnode *right = readTree(in);
		return new hnode('0', 0, left, right);
	}
}

void print_tree(hnode *tree, size_t depth)
{
	// POST: print a tree horizontally with each node's data
	if (tree == NULL)
		return;
	print_tree(tree->right, depth +1);
	for (size_t i = 0; i < depth; i++)
		cout << "   ";
	cout << tree->letter << endl;
	print_tree(tree->left, depth+1);
}

string char_to_bits(unsigned char sum)
{
	// POST: convert a character into a string of 8 bits of 0's and 1's 
	string bits = "";
	for (size_t i = 0; i < 8; i++) {
		bits = (sum % 2? "1" : "0") + bits;
		sum /= 2;
	}
	return bits;
}

string decode(hnode *tree, string bits, size_t fileSize) {
	// POST: use the gvien string of bits to traverse the tree
	//       until reach a leaf. Repeat the process until the number of 
	//       decoded characters equals the size of the original file
	string text = "";
	size_t count = 0;
	hnode *temp = tree;
	while (count != fileSize and bits.size() > 0) { 
		size_t i = 0;
		while (i < bits.size() and not is_leaf(tree)) {
			if (bits[i] == '0')
				tree = tree->left;
			else 
				tree = tree->right;
			i++;
		}
		text += tree->letter;
		bits = bits.substr(i);
		tree = temp;
		count++;
	}
	return text;
}

int main(int argc, char const *argv[]) {
	string infile = (argv[1]);
	ifstream in (infile.c_str());
	string outfile = infile.substr(0, infile.length() -4); // remove ".huf"
	ofstream out(outfile.c_str());
	char c;
	string bits = "";
	string text = "";
	size_t fileSize;	
	in >> fileSize;
	hnode *tree = readTree(in); // recreate tree
	while (in.get(c)) // create a string of bits
		bits += char_to_bits(c);
	text = decode(tree, bits, fileSize); // decode bits 
	out << text; 
	remove(infile.c_str());
} 
