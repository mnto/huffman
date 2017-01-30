all: hencode hdecode
hencode: hencode.o 
	g++ -o hencode hencode.o  
hdecode: hdecode.o 
	g++ -o hdecode hdecode.o 
hencode.o: hencode.cc 
	g++ -c hencode.cc
hdecode.o: hdecode.cc
	g++ -c hdecode.cc

