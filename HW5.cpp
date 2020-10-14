
//HW5  AVL Tree
//Due: Friday (Nov. 8) at 11:59PM
//55 points
//This homework requires more efforts. You should get started as soon as possible.

#include <iostream> //to use cout
#include <algorithm> //to use max function such as  i = max(a, b);
#include <stack>
using namespace std;

//You need to use the following node class for each node of the AVL tree
class node {
public:
	int value;
	int height;//this is tree height. Leaf node is 1; empty node (i.e., NIL) is 0
	node* parent;
	node* l_child;
	node* r_child;
	node() {}
	node(int i) { value = i; height = 1; parent = l_child = r_child = nullptr; }

};

class avl_tree {
public:
	node* root;
	avl_tree() {
		root = nullptr;
	}

	//************************************************************************************
	//Implement the following member functions
	void add_node(int i);
	//if case of a tie, add i to the last of existing nodes with value i in the in-order sequence

	void delete_node(int i);
	//Delete the node with value i.  in case of multiple nodes with value i, delete the first node with value i in the in-order traveral sequence


	void in_order_traversal(node* p); //such as 2 5 9 11 11 14 15 15 ...

	pair<node*, int> height_update(node* p);
	/*
	This function will be invoked by add_node and delete_node.
	p points to the first node that we need to check for possible height update.  We then need to check possible height update toward root.
	All nodes whose heights need to be updated will be performed in this function.
	The function returns a pair.  If no imbalance is detected, the first of the pair will be nullptr; otherwise it will be the address of the action node.
	The second of the pair will be 0 if no imbalance is detected; otherwise its value is 1,2,3,4 for RR RL, LL, and LR pattern, respectively.
	*/

	void L_Rotate(node* p);
	//p points to the node at which the rotation will be performed.

	void R_Rotate(node* p);
	//p points to the node at which the rotation will be performed.
};
pair<node*, int> f1(node* p, int res) {
	return { p,res };
}
void avl_tree::add_node(int i) {
	if (root == nullptr) {	//No AVL Tree existed.
		root = new node(i);
		return;
	}
	else {
		node* tmp = new node(i);
		node* t_root = root;
		node* t_root2 = t_root;
		while (t_root != nullptr) {
			t_root2 = t_root;
			if (tmp->value < t_root->value)
				t_root = t_root->l_child;
			else
				t_root = t_root->r_child;
		}
		if (tmp->value < t_root2->value) {
			t_root2->l_child = tmp;
			tmp->parent = t_root2;
		}
		else {
			t_root2->r_child = tmp;
			tmp->parent = t_root2;
		}
		pair<node*, int> result;
		result = height_update(tmp);
		if (result.second == 1) {//In this case,it is a RR pattern.
			L_Rotate(result.first);
		}
		if (result.second == 2) {//In this case,it is a RL pattern.
			R_Rotate(result.first->r_child);
			L_Rotate(result.first);
		}
		if (result.second == 3) {//In this case,it is a LL pattern.
			R_Rotate(result.first);
		}
		if (result.second == 4) {//In this case,it is a LR pattern.
			L_Rotate(result.first->l_child);
			R_Rotate(result.first);
		}
		return;
	}
}

void avl_tree::delete_node(int i) {
	if (root == nullptr)//if the avl_tree has no root.
		return;
	stack<node*> s1;
	node* tmp = root;
	while (true) {
		while (tmp != nullptr) {
			s1.push(tmp);
			tmp = tmp->l_child;
		}
		if (s1.empty() == true) {
			tmp = nullptr;
			break;
		}
		tmp = s1.top();
		s1.pop();
		if (tmp->value == i)
			break;
		tmp = tmp->r_child;
	}
	if (tmp == nullptr)//Can not find the item.
		return;
	node* tmp2 = tmp->parent;
	if (tmp->l_child == nullptr && tmp->r_child == nullptr) {//In this case,tmp is just a leaf node.
		pair<node*, int> result;
		int status = -1;
		if (tmp2 != nullptr) {
			if (tmp2->l_child != nullptr && tmp2->l_child == tmp)
				status = 0;
			if (tmp2->r_child != nullptr && tmp2->r_child == tmp)
				status = 1;
		}
		tmp->parent = nullptr;
		delete(tmp);
		if (tmp2 == nullptr)
			root = nullptr;
		if (status == 0)
			tmp2->l_child = nullptr;
		if (status == 1)
			tmp2->r_child = nullptr;
		result = height_update(tmp2);
		while (result.second != 0) {
			if (result.second == 1) {//In this case,it is a RR pattern.
				L_Rotate(result.first);
			}
			if (result.second == 2) {//In this case,it is a RL pattern.
				R_Rotate(result.first->r_child);
				L_Rotate(result.first);
			}
			if (result.second == 3) {//In this case,it is a LL pattern.
				R_Rotate(result.first);
			}
			if (result.second == 4) {//In this case,it is a LR pattern.
				L_Rotate(result.first->l_child);
				R_Rotate(result.first);
			}
			result = height_update(result.first);
		}
	}
	else {
		if ((tmp->l_child != nullptr && tmp->r_child == nullptr) || (tmp->l_child == nullptr && tmp->r_child != nullptr)) {//In this case,tmp is a parent of only leaf node.
			pair<node*, int> result;
			int status = -1;
			if (tmp->l_child != nullptr && tmp->r_child == nullptr)
				status = 0;	//In this case,tmp is a parent of l_child.
			if (tmp->l_child == nullptr && tmp->r_child != nullptr)
				status = 1;	//In this case,tmp is a parent of r_child.
			if (status == 0) {
				tmp->value = tmp->l_child->value;
				tmp->l_child->parent = nullptr;
				delete(tmp->l_child);
				tmp->l_child = nullptr;
			}
			if (status == 1) {
				tmp->value = tmp->r_child->value;
				tmp->r_child->parent = nullptr;
				delete(tmp->r_child);
				tmp->r_child = nullptr;
			}
			result = height_update(tmp);
			while (result.second != 0) {
				if (result.second == 1) {//In this case,it is a RR pattern.
					L_Rotate(result.first);
				}
				if (result.second == 2) {//In this case,it is a RL pattern.
					R_Rotate(result.first->r_child);
					L_Rotate(result.first);
				}
				if (result.second == 3) {//In this case,it is a LL pattern.
					R_Rotate(result.first);
				}
				if (result.second == 4) {//In this case,it is a LR pattern.
					L_Rotate(result.first->l_child);
					R_Rotate(result.first);
				}
				result = height_update(result.first);
			}
		}
		else {//For all other cases.
			pair<node*, int> result;
			node* predecessor = tmp;
			node* predecessor2 = predecessor;
			//if (predecessor->l_child != nullptr)
			if (tmp->l_child != nullptr && tmp->l_child->height >= tmp->r_child->height) {
				predecessor = predecessor->l_child;
				while (predecessor != nullptr) {
					predecessor2 = predecessor;
					if (predecessor->r_child != nullptr) {
						predecessor2 = predecessor;
						predecessor = predecessor->r_child;

					}
					else {
						predecessor = predecessor->r_child;
					}
				}
			}
			else if (tmp->r_child != nullptr && tmp->r_child->height > tmp->l_child->height) {
				predecessor = predecessor->r_child;
				while (predecessor != nullptr) {
					predecessor2 = predecessor;
					if (predecessor->l_child != nullptr) {
						predecessor2 = predecessor;
						predecessor = predecessor->l_child;
					}
					else {
						predecessor = predecessor->l_child;
					}
				}
			}
			tmp->value = predecessor2->value;
			node* predecessor3 = predecessor2->parent;
			int status = -1;
			if (predecessor3->l_child == predecessor2)
				status = 0;
			if (predecessor3->r_child == predecessor2)
				status = 1;
			if (status == 0) {
				predecessor3->l_child = predecessor2->l_child;
			}
			if (status == 1) {
				predecessor3->r_child = predecessor2->r_child;
			}
			predecessor2->parent = nullptr;
			delete(predecessor2);
			result = height_update(predecessor3);
			while (result.second != 0) {
				if (result.second == 1) {//In this case,it is a RR pattern.
					L_Rotate(result.first);
				}
				if (result.second == 2) {//In this case,it is a RL pattern.
					R_Rotate(result.first->r_child);
					L_Rotate(result.first);
				}
				if (result.second == 3) {//In this case,it is a LL pattern.
					R_Rotate(result.first);
				}
				if (result.second == 4) {//In this case,it is a LR pattern.
					L_Rotate(result.first->l_child);
					R_Rotate(result.first);
				}
				result = height_update(result.first);
			}
		}
	}

}

void avl_tree::in_order_traversal(node* p) {	//Recursively print out the val of the node.
	if (p) {
		if (p->l_child) {
			in_order_traversal(p->l_child);
		}
		cout << "(Value:" << p->value << " Height:" << p->height << ")" << endl;
		if (p->r_child) {
			in_order_traversal(p->r_child);
		}
	}
}

pair<node*, int> avl_tree::height_update(node* p) {
	if (p == nullptr)
		return f1(nullptr, 0);
	int left_Height = -1;
	int right_Height = -1;
	if (p->l_child == nullptr)//In this case,p do not have a left child.
		left_Height = 0;
	if (p->r_child == nullptr)//In this case,p do not have a right child.
		right_Height = 0;
	if (p->l_child != nullptr)//In this case,p do not have a left child.
		left_Height = p->l_child->height;
	if (p->r_child != nullptr)//In this case,p do not have a right child.
		right_Height = p->r_child->height;

	if (left_Height - right_Height == 2) {
		int left_Height2 = -1;
		int right_Height2 = -1;
		if (p->l_child->l_child == nullptr)
			left_Height2 = 0;
		if (p->l_child->r_child == nullptr)
			right_Height2 = 0;
		if (p->l_child->l_child != nullptr)
			left_Height2 = p->l_child->l_child->height;
		if (p->l_child->r_child != nullptr)
			right_Height2 = p->l_child->r_child->height;
		if (left_Height2 > right_Height2) {//This is LL pattern
			int result_second = 3;
			return f1(p, result_second);
		}
		else {//This is LR pattern
			int result_second = 4;
			return f1(p, result_second);
		}
	}
	else {
		if (right_Height - left_Height == 2) {
			int left_Height2 = -1;
			int right_Height2 = -1;
			if (p->r_child->l_child == nullptr)
				left_Height2 = 0;
			if (p->r_child->r_child == nullptr)
				right_Height2 = 0;
			if (p->r_child->l_child != nullptr)
				left_Height2 = p->r_child->l_child->height;
			if (p->r_child->r_child != nullptr)
				right_Height2 = p->r_child->r_child->height;
			if (left_Height2 > right_Height2) {//This is RL pattern
				int result_second = 2;
				return f1(p, result_second);
			}
			else {//This is RR pattern
				int result_second = 1;
				return f1(p, result_second);
			}
		}
		else
			p->height = (max(left_Height, right_Height) + 1);
	}
	return height_update(p->parent);
}


void avl_tree::R_Rotate(node* p) {//p points to the node at which the rotation will be performed.
	if (p == root) {//if action node is root.
		node* tmp = p->l_child;
		p->l_child = tmp->r_child;
		if (tmp->r_child != nullptr)
			tmp->r_child->parent = p;
		tmp->r_child = p;
		root = tmp;
		tmp->parent = nullptr;
		p->parent = tmp;
		int left_Height = -1;
		int right_Height = -1;
		if (p->l_child == nullptr)
			left_Height = 0;
		if (p->r_child == nullptr)
			right_Height = 0;
		if (p->l_child != nullptr)
			left_Height = p->l_child->height;
		if (p->r_child != nullptr)
			right_Height = p->r_child->height;
		p->height = (max(left_Height, right_Height) + 1);
		left_Height = -1;
		right_Height = -1;
		if (tmp->l_child == nullptr)
			left_Height = 0;
		if (tmp->l_child != nullptr)
			left_Height = tmp->l_child->height;
		tmp->height = (max(left_Height, p->height) + 1);
		return;
	}
	else {//In this case,the action node is not the root.
		int status = -1;
		node* pre = p->parent;
		node* tmp = p->l_child;
		if (pre->l_child == p)
			status = 0;
		if (pre->r_child == p)
			status = 1;
		p->l_child = tmp->r_child;
		if (tmp->r_child != nullptr)
			tmp->r_child->parent = p;
		tmp->r_child = p;
		p->parent = tmp;
		if (status == 0)
			pre->l_child = tmp;
		if (status == 1)
			pre->r_child = tmp;
		tmp->parent = pre;
		int left_Height = -1;
		int right_Height = -1;
		if (p->l_child == nullptr)
			left_Height = 0;
		if (p->r_child == nullptr)
			right_Height = 0;
		if (p->l_child != nullptr)
			left_Height = p->l_child->height;
		if (p->r_child != nullptr)
			right_Height = p->r_child->height;
		p->height = (max(left_Height, right_Height) + 1);
		left_Height = -1;
		right_Height = -1;
		if (tmp->l_child == nullptr)
			left_Height = 0;
		if (tmp->l_child != nullptr)
			left_Height = tmp->l_child->height;
		tmp->height = (max(left_Height, p->height) + 1);
		return;
	}
}

void avl_tree::L_Rotate(node* p) {//p points to the node at which the rotation will be performed.
	if (p == root) {//if action node is root.
		node* tmp = p->r_child;
		p->r_child = tmp->l_child;
		if (tmp->l_child != nullptr)
			tmp->l_child->parent = p;
		tmp->l_child = p;
		root = tmp;
		tmp->parent = nullptr;
		p->parent = tmp;
		int left_Height = -1;
		int right_Height = -1;
		if (p->l_child == nullptr)
			left_Height = 0;
		if (p->r_child == nullptr)
			right_Height = 0;
		if (p->l_child != nullptr)
			left_Height = p->l_child->height;
		if (p->r_child != nullptr)
			right_Height = p->r_child->height;
		p->height = (max(left_Height, right_Height) + 1);
		right_Height = -1;
		if (tmp->r_child == nullptr)
			right_Height = 0;
		if (tmp->r_child != nullptr)
			right_Height = tmp->r_child->height;
		tmp->height = (max(right_Height, p->height) + 1);
	}
	else {//In this case,the action node is not the root.
		int status = -1;
		node* pre = p->parent;
		node* tmp = p->r_child;
		if (pre->l_child == p)
			status = 0;
		if (pre->r_child == p)
			status = 1;
		p->r_child = tmp->l_child;
		if (tmp->l_child != nullptr)
			tmp->l_child->parent = p;
		tmp->l_child = p;
		p->parent = tmp;
		if (status == 0)
			pre->l_child = tmp;
		if (status == 1)
			pre->r_child = tmp;
		tmp->parent = pre;
		int left_Height = -1;
		int right_Height = -1;
		if (p->l_child == nullptr)
			left_Height = 0;
		if (p->r_child == nullptr)
			right_Height = 0;
		if (p->l_child != nullptr)
			left_Height = p->l_child->height;
		if (p->r_child != nullptr)
			right_Height = p->r_child->height;
		p->height = (max(left_Height, right_Height) + 1);
		right_Height = -1;
		if (tmp->r_child == nullptr)
			right_Height = 0;
		if (tmp->r_child != nullptr)
			right_Height = tmp->r_child->height;
		tmp->height = (max(right_Height, p->height) + 1);
		return;
	}
}


int main() {
	avl_tree t1;
	t1.add_node(75);
	t1.add_node(50);
	t1.add_node(25);
	t1.add_node(15);
	t1.add_node(30);
	t1.add_node(60);
	t1.add_node(80);
	t1.add_node(5);
	t1.add_node(10);
	cout << "\n Add 5 points" << endl;
	t1.in_order_traversal(t1.root);
	t1.add_node(27);
	t1.add_node(55);
	t1.add_node(1);
	cout << endl;
	t1.in_order_traversal(t1.root);
	t1.add_node(10);
	cout << "\n Add 5 points" << endl;
	t1.in_order_traversal(t1.root);
	t1.delete_node(75);
	cout << "\n Delete 15 points" << endl;
	t1.in_order_traversal(t1.root);
	t1.add_node(12);
	t1.add_node(12);
	cout << "\n Add 5 points" << endl;
	t1.in_order_traversal(t1.root);
	cout << endl;
	avl_tree t2;
	t2.add_node(75);
	t2.add_node(50);
	t2.add_node(25);
	t2.add_node(15);
	t2.add_node(30);
	t2.add_node(60);
	t2.add_node(80);
	t2.add_node(5);
	t2.add_node(10);
	t2.add_node(27);
	t2.add_node(55);
	t2.add_node(1);
	t2.delete_node(75);
	t2.delete_node(1);
	t2.in_order_traversal(t2.root);
	t2.delete_node(25);
	cout << "\n Delete 15 points" << endl;
	t2.in_order_traversal(t2.root);
	cout << endl;
	avl_tree t3;
	t3.add_node(1);
	t3.add_node(1);
	t3.add_node(1);
	t3.add_node(1);
	t3.add_node(1);
	cout << endl;
	t3.in_order_traversal(t3.root);
	t3.delete_node(1);
	cout << "\n Delete 10 points" << endl;
	t3.in_order_traversal(t3.root);

	getchar();
	getchar();
	return 0;
}

//The following is an example showing how to return a pair.
/*
#include <iostream>
using namespace std;

pair<int *, int> f1(){
	return { new int {10}, 10 };
}
int main() {
	cout << *f1().first << " " << f1().second << endl;
	getchar();
	getchar();
	return 0;
}
*/
