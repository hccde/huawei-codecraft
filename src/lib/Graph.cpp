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
	int costIndex;
	int costBand;
	Node(int _start,int _end,int _bandwidth,int _cost):start(-1),end(-1),
	bandwidth(0),cost(0){
		vector<Node*> nodes(0);
		start = _start;
		cost = _cost;
		end = _end;
		bandwidth = _bandwidth;
		connectNodes = nodes;
		connectNodeCounts=0;
		costIndex = -1;
		costBand = 0;
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
			connectNodes = node.connectNodes;
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
		matrixGraph(input_lines);
		Node* currentnode = NULL;
		int endline = graphInfo.links+4;
		//net node
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

		//cost node should be considered as a special net node with setting nodeIndex >0
		// int startline = endline+1;
		// cout<<startline<<endl;
		// int atIndex = -1;
		// endline = startline+graphInfo.costNode;
		// for(int i = startline;i<endline;i++){
		// 	atIndex = *(input_lines.at(i)+1);
		// 	cout<<atIndex<<endl;
		// 	Node *tem = graphList.at(atIndex);
		// 	tem->costIndex = *input_lines.at(i);
		// 	tem->costBand = *((input_lines.at(i))+2);
		// }
		
	}

	Graph(const Graph &graph){
		graphInfo = graph.graphInfo;
		Node* currentnode = NULL;
		graphList = vector<Node*>(graph.graphList);
	}

	Graph& operator =(const Graph &graph){
		if(this != &graph){
			graphInfo = graph.graphInfo;
			Node* currentnode = NULL;
			graphList = vector<Node*>(graph.graphList);
		}
		return *this;
	}

	~Graph(){
		int size = graphList.size();
		for(int i = 0;i<size;i++){
			delete graphList.at(i);
		}
	}
	Node** matrixGraph(vector<int*>input_lines){

		int endline = graphInfo.links+4;
		int nodes = graphInfo.nodeCount;
		Node** matrix = new Node* [nodes];

		for(int i =0;i<nodes;i++){
			Node** tem = new Node*[nodes];
			*(matrix+i) = *tem;
		}

		// for(int i = 4;i<endline;i++){
		// 	int start = *input_lines.at(i);
		// 	int end = *(input_lines.at(i)+1);
		// 	int cost = *(input_lines.at(i)+2);
		// 	int bandwidth = *(input_lines.at(i)+3);
		// 	Node *node = new Node(start,end,bandwidth,cost);
		// 	cout<<start<<" "<<end<<endl;
		// 	*(*(matrix+start)+end) = *node;
		// }
		Node* tem = new Node(0,0,0,0);
		Node t(0,0,0,0);
		Node *m =&(**matrix);
		m = tem;
		cout<<m->start<<endl;
		return matrix;

	}
	// void showGraph(const Graph &graph){
	// 	cout<<"net nodes: "<<graph.graphInfo.nodeCount<<" net links: "<<graph.graphInfo.links<<" net links: "<<graph.graphInfo.costNode<<endl;
	// 	int length = graph.graphList.size();
	// 	for(int i = 0;i<length;i++){
	// 		Node *tem = graph.graphList.at(i);
	// 		cout<<"node start: "<<tem->start<<" node end: "<<tem->end<<" node cost"<<tem->cost<<
	// 		" node bandwidth: "<<tem->bandwidth<<" node linkscount: "<<tem->connectNodeCounts<<endl;
	// 	}

	// }
};

#ifdef DEBUG

// int main(int argc,char** argv){
// 	Node n(0,1,1,2);
// 	Node m = n;
// 	return 0;
// }

#endif