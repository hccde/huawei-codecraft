#include <iostream>
#include "lib/utils.cpp"
int main(int argc,char**argv){
	vector<int*> input_lines = read_file("../case_example/case0.txt");
	cout<<input_lines.size();
    return 0;
}