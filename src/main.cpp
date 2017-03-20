#include <iostream>
#include "lib/utils.cpp"
#include "lib/Graph.cpp"




int main(int argc,char**argv){
	GlobalInfo GLOBAL;
	vector<int*> input_lines = read_file("../case_example/case0.txt");
	
	//build graph using input file
	Graph graph(input_lines);

    return 0;
}