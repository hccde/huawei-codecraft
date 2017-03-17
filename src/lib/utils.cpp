#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
vector<int*> read_file(string path);

vector<int*> read_file(string path){
	//low efficiency
	vector<int *> lines(0);
	ifstream fin(path);
	string line;
	while(getline(fin,line)){
		istringstream stream(line);
		int* line_arr = new int[4];
		int i(0);
		while(stream>>*(line_arr+i)){i++;}
		lines.push_back(line_arr);
	}
	// cout<<lines.size()<<endl;
	fin.close();
	return lines;
}