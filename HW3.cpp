
//Use the following names for the structures.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class n_node { //stand for neighbor_node
public:
	int id;  //neighbor id
	int weight; //edge weight
	//Do your own constructor(s)
	n_node(int n1, int n2) { id = n1; weight = n2; }
	n_node() {}
};

class rt_node {
public:
	bool is_visited; //true if visited; else false
	int cost; //path cost
	int from; //from node
	int h_pos;//the positon of this node in heap
	//Do your own constructor(s)
	rt_node() { is_visited = false; cost = 0; from = -1; h_pos = -1; }
	rt_node(int n1) { is_visited = false; cost = 0; from = -1; h_pos = n1; }
};

ostream& operator<<(ostream& str, const rt_node& t) {
	str << "(" << t.is_visited << ", " << t.cost << ", " << t.from << ", " << t.h_pos << ")";
	return str;
}

ostream& operator<<(ostream& str, const n_node& t) {
	str << "(" << t.id << ", " << t.weight << ")";
	return str;
}

class h_node {
public:
	int id;//node id
	int cost; //cost to this node from source
	//Do your own constructor(s)
	h_node() {}
	h_node(int n1, int n2) { id = n1; cost = n2; }
};

void Heapify(vector <h_node>& Heap, int index, int end) {
	int i = index;
	h_node exc = Heap[i];
	int j = i * 2 + 1;
	while (j < end) {
		if (j + 1 < end && Heap[j].cost < Heap[j + 1].cost)
			j++;
		if (exc.cost > Heap[j].cost)
			break;
		Heap[i] = Heap[j];
		i = j;
		j = 2 * i + 1;
	}
	Heap[i] = exc;
}

void HeapSort(vector <h_node>& Heap) {
	int length = Heap.size();
	if (length == 0 || length == 1)
		return;
	for (int i = length / 2 - 1; i >= 0; i--) {
		Heapify(Heap, i, Heap.size());
	}
	for (int i = length - 1; i >= 0; i--) {
		//swap
		h_node exc = Heap[i];
		Heap[i] = Heap[0];
		Heap[0] = exc;

		Heapify(Heap, 0, i);
	}

	return;
}

void Update_hpos(vector <rt_node>& Routing_Table, vector <h_node>& Heap) {
	vector<h_node>::iterator it1 = Heap.begin();
	int num = 0;
	while (it1 != Heap.end()) {
		Routing_Table[it1->id].h_pos = num;
		num++;
		it1++;
	}
}

int main() {
	vector < vector<n_node>* > Graph;
	vector <rt_node> Routing_Table;
	vector <h_node> Heap;
	ifstream in("data1.txt");
	int i, j, k, source;
	in >> i >> j; // get the source node,number of nodes,number of directed edges in the txt.
	Graph.resize(j);
	source = i; //to store the source node
	int node_num = j;
	for (int num = 0; num < j; num++) {
		rt_node tmp = rt_node(num);
		Routing_Table.push_back(tmp);
		vector<n_node>* ptr = new vector<n_node>(0);
		Graph[num] = ptr;
	}

	int edge_num;
	in >> edge_num;
	for (int num = 0; num < edge_num; num++) {
		in >> i >> j >> k;
		n_node tmp = n_node(j, k);
		Graph[i]->push_back(tmp);

		n_node tmp2 = n_node(i, k);
		Graph[j]->push_back(tmp2);
	}

	for (int num = 0; num < node_num; num++) {
		h_node tmp = h_node(num, INT_MAX);
		Heap.push_back(tmp);
	}

	//start to find the minimal edge.
	Heap[source].cost = 0;
	Routing_Table[source].from = source;
	Routing_Table[source].h_pos = source;
	Routing_Table[source].cost = 0;
	Routing_Table[source].is_visited = true;
	h_node exc = Heap[source];
	vector<n_node>* ptr = Graph[source];
	vector<n_node>::iterator it1 = ptr->begin();
	int num1 = INT_MAX;
	while (it1 != ptr->end()) {
		if (Routing_Table[it1->id].is_visited != true && it1->weight <= Heap[Routing_Table[it1->id].h_pos].cost) {
			Heap[Routing_Table[it1->id].h_pos].cost = it1->weight;
			Routing_Table[it1->id].cost = it1->weight;
			Routing_Table[it1->id].from = exc.id;
		}
		it1++;
	}
	exc = Heap[source];
	Heap[source] = Heap.back();
	Heap.back() = exc;
	Routing_Table[source].h_pos = Heap.size() - 1;
	Routing_Table[Heap[source].id].h_pos = source;
	Update_hpos(Routing_Table, Heap);
	Heap.pop_back();

	HeapSort(Heap);
	Update_hpos(Routing_Table, Heap);
	//the main loop
	while (!Heap.empty()) {
		h_node exc2 = Heap.front();
		ptr = Graph[exc2.id];
		it1 = ptr->begin();
		Routing_Table[exc2.id].is_visited = true;
		while (it1 != ptr->end()) {
			if (Routing_Table[it1->id].is_visited != true && it1->weight <= Heap[Routing_Table[it1->id].h_pos].cost) {
				Heap[Routing_Table[it1->id].h_pos].cost = it1->weight;
				Routing_Table[it1->id].cost = it1->weight;
				Routing_Table[it1->id].from = exc2.id;
			}
			it1++;
		}
		h_node tmp2 = Heap[0];
		Heap[0] = Heap.back();
		Heap.back() = tmp2;
		Update_hpos(Routing_Table, Heap);
		Heap.pop_back();
		Update_hpos(Routing_Table, Heap);
		HeapSort(Heap);
		Update_hpos(Routing_Table, Heap);
	}

	int sum = 0;
	for (size_t i = 0; i < Routing_Table.size(); i++) { //print the cost in Routing_Table.
		if (i != source) {
			cout << Routing_Table[i].from << " " << i << " " << Routing_Table[i].cost << endl;
			sum += Routing_Table[i].cost;
		}
	}

	cout << "The overall cost of the minimum spanning tree is " << sum << "." << endl;

}

