all: HuffmanCoding.x

HuffmanCoding.x: HuffmanCoding.cpp
	g++ -std=c++11 -fopenmp -o HuffmanCoding.x HuffmanCoding.cpp