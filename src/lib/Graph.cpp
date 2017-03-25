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
	Node(int _start,int _end,int _bandwidth,int _cost){
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
	Node*** graphArray;
	vector<int*>inputLines;
	Node** costList;
	Graph(vector<int*>input_lines){
		graphInfo = get_info(input_lines);
		graphArray = matrixGraph(input_lines);
		inputLines = input_lines;
		costList = costNodeList(input_lines);

		int length = graphInfo.nodeCount;
		Node *currentnode = NULL;
		for(int i = 0;i<length;i++){
			bool isHead = true;
			currentnode = NULL;
			Node *node = NULL;
			for(int j = 0;j<length;j++){
				node  = *(*(graphArray+i)+j);
				if(node != NULL){
					if(isHead){
						graphList.push_back(node);
						isHead = false;
						currentnode = node;
					}else{
						currentnode->connect(node);
					}
				}
			}
		}
	}

	Graph(const Graph &graph){
		graphInfo = graph.graphInfo;
		inputLines = graph.inputLines;
		graphArray = matrixGraph(graph.inputLines);
		costList = costNodeList(graph.inputLines);
		graphList = vector<Node*>(graph.graphList);
	}

	Graph& operator =(const Graph &graph){
		if(this != &graph){
			graphInfo = graph.graphInfo;
			inputLines = graph.inputLines;
			graphArray = matrixGraph(graph.inputLines);
			costList = costNodeList(graph.inputLines);
			graphList = vector<Node*>(graph.graphList);

		}
		return *this;
	}

	~Graph(){
		int length = graphInfo.nodeCount;
		for(int i = 0;i<length;i++){
			for(int j = 0;j<length;j++){
				if(*(*(graphArray+i)+j) != NULL){
					delete *(*(graphArray+i)+j);
				}
			}
			delete *(graphArray+i);
		}
		delete graphArray;
		graphList.clear();

		delete []costList;
	}

	Node** costNodeList(vector<int*>input_lines){
		int startline = graphInfo.links+4+1;
		int costNode = graphInfo.costNode;
		int endline = startline+graphInfo.costNode;
		Node** costNodelist = new Node* [costNode];
		int _end=-1,_start=-1,_bandwidth=-1;
		int _index = startline;
		for(int i=0;i<costNode;i++){
			_index = i+startline;
			_end = *(input_lines.at(_index)+1);
			_start = *input_lines.at(_index);
			_bandwidth = *((input_lines.at(_index))+2);
			costNodelist[i] = new Node(_start,_end,_bandwidth,0);
		}
		return costNodelist;
	}

	Node*** matrixGraph(vector<int*>input_lines){
		int endline = graphInfo.links+4;
		int nodes = graphInfo.nodeCount;
		Node*** matrix = new Node** [nodes];

		for(int i =0;i<nodes;i++){
			Node** tem = new Node*[nodes];
			*(matrix+i) = tem;
			for(int j=0;j<nodes;j++){
				*(*(matrix+i)+j) = NULL;
			}
		}

		for(int i = 4;i<endline;i++){
			int start = *input_lines.at(i);
			int end = *(input_lines.at(i)+1);
			int cost = *(input_lines.at(i)+2);
			int bandwidth = *(input_lines.at(i)+3);
			Node *node = new Node(start,end,bandwidth,cost);
			Node *nodecopy = new Node(start,end,bandwidth,cost);
			*(*(matrix+start)+end) = node;
			*(*(matrix+end)+start) = nodecopy;
		}
		return matrix;
	}

	void showGraph(const Graph &graph){
		cout<<"net nodes: "<<graph.graphInfo.nodeCount<<" net links: "<<graph.graphInfo.links<<" net links: "<<graph.graphInfo.costNode<<endl;
		int length = graph.graphList.size();
		cout<<"array length: "<<length<<endl;
		for(int i = 0;i<length;i++){
			Node *tem = graph.graphList.at(i);
			cout<<"node start: "<<tem->start<<" node end: "<<tem->end<<" node cost"<<tem->cost<<
			" node bandwidth: "<<tem->bandwidth<<" node linkscount: "<<tem->connectNodeCounts<<endl;
		}

	}
	void showcostList(const Graph &graph){
		cout<<"costList:"<<graph.graphInfo.costNode<<endl;
		Node** list = graph.costList;
		for(int i = 0;i<graph.graphInfo.costNode;i++){
			cout<<"costnodeIndex: "<<list[i]->start<<" connect to graph index: "<<list[i]->end<<
			" bandwidth "<<list[i]->bandwidth<<endl;
		}
	}
};