#define DEBUG	0
#ifdef DEBUG
#include <iostream>
#include <vector>
using namespace std;
#endif
typedef struct global_info {
	int nodeCount;
	int links;
	int costNode;
	int serverCost;
} GraphInfo;

GraphInfo get_info(vector<int*> input_lines){
	GraphInfo info;
	info.nodeCount = *input_lines.at(0);
	info.links = *(input_lines.at(0)+1);
	info.costNode = *(input_lines.at(0)+2);
	info.serverCost = *(input_lines.at(2));
	return info;
}

class Node{
private:
	vector<Node*> connectNodes;
public:
	int connectNodeCounts;
	int start;
	int end;
	int cost;
	int bandwidth;
	Node(int _start,int _end,int _bandwidth,int _cost){
		vector<Node*> nodes(0);
		start = _start;
		cost = _cost;
		end = _end;
		bandwidth = _bandwidth;
		connectNodes = nodes;
		connectNodeCounts=0;
	}

	Node(const Node &node){
		vector<Node*> nodes(node.connectNodes);
		start = node.start;
		cost = node.cost;
		end = node.end;
		bandwidth = node.bandwidth;
		connectNodes = nodes;
		connectNodeCounts=node.connectNodeCounts;
	}

	Node& operator =(const Node& node){
		if(this != &node){
			vector<Node*> nodes(node.connectNodes);
			start = node.start;
			cost = node.cost;
			end = node.end;
			bandwidth = node.bandwidth;
			connectNodes = nodes;
			connectNodeCounts=node.connectNodeCounts;
		}
		return *this;
	}

	int connect(Node* node){
		connectNodeCounts++;
		connectNodes.push_back(node);
		return connectNodeCounts;
	}
};

class Graph{
public:
	vector<Node*> graphList;
	GraphInfo graphInfo;
	Graph(vector<int*>input_lines){
		graphInfo = get_info(input_lines);

		Node* currentnode = NULL;
		int endline = graphInfo.nodeCount+4;
		for(int i = 4;i<endline;i++){
			int start = *input_lines.at(i);
			int end = *(input_lines.at(i)+1);
			int cost = *(input_lines.at(i)+2);
			int bandwidth = *(input_lines.at(i)+3);
			Node *node = new Node(start,end,bandwidth,cost);
			if(currentnode != NULL && currentnode->start == start){
				//connect
				currentnode->connect(node);
			}else{
				//new node
				currentnode = node;
				graphList.push_back(node);
			}
		}
	}
	// ~Graph(){

	// }
};

#ifdef DEBUG

int main(int argc,char** argv){
	Node n(0,1,1,2);
	Node m = n;
	return 0;
}

#endif