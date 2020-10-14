
//Due: 11:59PM, Thursday (9/12)

#include <iostream>
using namespace std;


class Node {
public:
	int value;
	Node* next;
	Node(int i) { value = i; next = nullptr; }
	Node() { next = nullptr; }
};

class LinkedList {
public:
	int numNodes;
	Node* head;
	LinkedList() { numNodes = 0; head = nullptr; }
	void makeRandomList(int m, int n);
	void printList();



	//Recursively merge sort i numbers starting at node pointed by p
	void mergeSort(Node* &p, int i);//in-place recursive merge sort


	//Merge i1 numbers starting at node pointed by p1 with i2 numbers
	//starting at node pointed by p2
	void merge(Node* &p1, int i1, Node* p2, int i2);
};

void LinkedList::makeRandomList(int m, int n) {

	for (int i = 0; i < m; i++) {
		Node* p1 = new Node(rand() % n);
		p1->next = head;
		head = p1;
		numNodes++;
	}
}

void LinkedList::printList() {
	cout << endl;
	Node* p1 = head;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void LinkedList::merge(Node* &p1, int i1, Node* p2, int i2) {
	if (p1 == nullptr) {  //if p1 is nullptr,we do not need to merge.
		p1 = p2;
		return;
	}
	if (p2 == nullptr) //if p2 is nullptr,we do not need to merge.
		return;
	Node* tmp = nullptr;//Use Node* tmp to find out the minimal node in every comparison

	//Find out the first node in the first comparison
	if (p1 != nullptr && p2 != nullptr) {
		if (p1->value <= p2->value) {
			tmp = p1;
			p1 = p1->next;
		}
		else {
			tmp = p2;
			p2 = p2->next;
		}
	}
	else {
		if (p1 == nullptr && p2 != nullptr) {
			tmp = p2;
			p2 = p2->next;
		}
		if (p2 == nullptr && p1 != nullptr) {
			tmp = p1;
			p1 = p2->next;
		}
		if (p1 == nullptr && p2 == nullptr) {
			return;
		}
	}
	Node* ori = tmp; //Node* ori store the original address of the first node.

	//The main process of merging two parts of nodes.
	while (p1 != nullptr && p2 != nullptr) {
		if (p1->value <= p2->value) {
			tmp->next = p1;
			p1 = p1->next;
			tmp = tmp->next;
		}
		else {
			tmp->next = p2;
			p2 = p2->next;
			tmp = tmp->next;
		}
	}
	while (p1 != nullptr) {
		tmp->next = p1;
		p1 = p1->next;
		tmp = tmp->next;
	}
	while (p2 != nullptr) {
		tmp->next = p2;
		p2 = p2->next;
		tmp = tmp->next;
	}
	tmp->next = nullptr;
	p1 = ori;
}

void LinkedList::mergeSort(Node* &p, int i) {

	if (!p || !(p->next)) return; //The linkedList contains 0 node or 1 node.
	Node* p1 = p, * p2 = p;
	int j = 1;
	for (j; j <= (i / 2); j++) {
		p1 = p2;
		p2 = p2->next;
	}
	p1->next = nullptr;
	p1 = p;
	mergeSort(p1, j - 1);
	mergeSort(p2, j);
	merge(p1, (j - 1), p2, j);
	p = p1;
}

int main() {

	LinkedList d1;


	d1.makeRandomList(40, 20);
	d1.printList();

	d1.mergeSort(d1.head, d1.numNodes);
	d1.printList();

	getchar();
	getchar();
	return 0;

}