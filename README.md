# huffman

This is a program written in C++ that utilizes the min heap data structure to create a huffman tree. The program reads in a file, encodes it based on the occurrences of the letters in the file. The result file will be the encoded version of the input file that is compressed into a representation of bytes.

There is also a decode program here that undoes everything that hencode does. It deciphers each byte in the compressed version, generates a huffman tree, then figures out the frequency of each symbol. It can finally puts back together a decoded file that is identical to the original file before it was encoded.
