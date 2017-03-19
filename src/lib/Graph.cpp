#define DEBUG	true
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

class Node{
private:
	int index;
	int value;
	// int upstream;
	// int downstream;
public:
	Node(int indexcode,int val){
		index = indexcode;
		value = val;
		// upstream = ups;
		// downstream = downs;
	}
};


#ifdef DEBUG

int main(int argc,char** argv){
	Node n(2);
	return 0;
}

#endif