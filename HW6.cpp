
#include <iostream>
#include <stack>	//I use stack only to help me find the first of nodes with the same value in the order of inorder traversal.
using namespace std;

class node {
public:
	node* p_parent;
	node* p_Lchild;
	node* p_Rchild;
	int value;
	bool color; //true: red, false: black
	node() { p_parent = p_Lchild = p_Rchild = nullptr; }
	node(int i) { value = i; p_parent = p_Lchild = p_Rchild = nullptr; }
};

class tree {
public:
	node* root;
	tree() { root = nullptr; }

	//For insert, the new node should be the last of nodes with the same value in the order of
	//inorder traversal.  (The same as HW5.)
	void insert_node(int i);
	void insert_R_rotate(node* p);//For insert_node, R-rotate at node pointed by p
	void insert_L_rotate(node* p);//for insert_node, L-rotate at node pointed by p
	//All other siutions of insert_node should be directly implemented inside add_node


	//For delete, the deleted node shoud be the first of nodes with the same value in the order of
	//inorder traversal. (The same as HW5).
	//For replacement, always recursively replace it with predecessor, unless there is no predecessor. (In this
	//case, replace it with sucessor.)


	void delete_node(int i);
	void delete_1(node* p); //case 1 of delete_node; p points to the parent of double black node
	void delete_1_R_rotate(node* p);//R_totate used in case 1 of delete_node; p points to the parent of double black node
	void delete_1_L_rotate(node* p);//L_totate used in case 1 of delete_node; p points to the parent of double black node
	void delete_2A(node* p); //case 2A of delete_node; p points to the parent of double black node
	void delete_2B(node* p);//case 2B of delete_node; p points to the parent of double black node
	void delete_3(node* p);//case 3 of delete_node; p points to the parent of double black node
	//All other cases of delete_node should be directly implemented inside the delete_node.

	//For the following, during traveral, print (value, color) of each node.
	void InorderPrint(node* p);
	void PostorderPrint(node* p);
	void PreorderPrint(node* p);
};

void tree::insert_node(int i) {//Finished.
	if (root == nullptr) {	//No root existed.
		root = new node(i);
		root->color = false;
		return;
	}
	else {//We already have a existed root.
		node* tmp = new node(i);
		tmp->color = true;
		node* t_root = root;
		node* t_root2 = t_root;
		while (t_root != nullptr) {
			t_root2 = t_root;
			if (tmp->value < t_root->value)
				t_root = t_root->p_Lchild;
			else
				t_root = t_root->p_Rchild;
		}
		if (tmp->value < t_root2->value) {
			t_root2->p_Lchild = tmp;
			tmp->p_parent = t_root2;
		}
		else {
			t_root2->p_Rchild = tmp;
			tmp->p_parent = t_root2;
		}
		while (tmp->p_parent && tmp->p_parent->color == true) {//If tmp's parent is existed and its color is red.
			int status = -1;//status help us to find the uncle node.
			node* parent = tmp->p_parent;
			node* pparent = parent->p_parent;
			if (pparent->p_Lchild == parent)
				status = 0;//Parent is the left child.
			if (pparent->p_Rchild == parent)
				status = 1;//Parent is the right child.
			if (status == 0) {//Parent is the left child.
				node* uncle = nullptr;
				if (pparent->p_Rchild == nullptr)
					uncle = nullptr;//uncle node's color is black.
				if (pparent->p_Rchild != nullptr)
					uncle = pparent->p_Rchild;
				if (uncle != nullptr && uncle->color == true) {//The case for uncle node's color is red.
					parent->color = false;
					uncle->color = false;
					pparent->color = true;
					tmp = pparent;
					continue;
				}
				if (uncle == nullptr || uncle->color == false) {//The case for uncle node's color is black.
					if (parent->p_Rchild == tmp) {//Tmp is the rchild node,we need to implement a L rotate.
						node* exc = parent;
						insert_L_rotate(parent);
						exc = tmp;
						tmp = parent;
						parent = exc;
					}
					//Tmp is the Lchild node,we need to implement a L rotate.
					parent->color = false;
					pparent->color = true;
					insert_R_rotate(pparent);
				}
			}
			if (status == 1) {//Parent is the right child.
				node* uncle = nullptr;
				if (pparent->p_Lchild == nullptr)
					uncle = nullptr;//uncle node's color is black.
				if (pparent->p_Lchild != nullptr)
					uncle = pparent->p_Lchild;
				if (uncle != nullptr && uncle->color == true) {//The case for uncle node's color is red.
					parent->color = false;
					uncle->color = false;
					pparent->color = true;
					tmp = pparent;
					continue;
				}
				if (uncle == nullptr || uncle->color == false) {//The case for uncle node's color is black.
					if (parent->p_Lchild == tmp) {//Tmp is the Lchild node,we need to implement a L rotate.
						node* exc = parent;
						insert_R_rotate(parent);
						exc = tmp;
						tmp = parent;
						parent = exc;
					}
					//Tmp is the rchild node,we need to implement a L rotate.
					parent->color = false;
					pparent->color = true;
					insert_L_rotate(pparent);
				}
			}
		}
		root->color = false;
	}
}

void tree::insert_R_rotate(node* p) {//Finished
	if (p == root) {//if action node is root.
		node* tmp = p->p_Lchild;
		p->p_Lchild = tmp->p_Rchild;
		if (tmp->p_Rchild != nullptr)
			tmp->p_Rchild->p_parent = p;
		tmp->p_Rchild = p;
		root = tmp;
		tmp->p_parent = nullptr;
		p->p_parent = tmp;
		return;
	}
	else {//In this case,the action node is not the root.
		int status = -1;
		node* pre = p->p_parent;
		node* tmp = p->p_Lchild;
		if (pre->p_Lchild == p)
			status = 0;
		if (pre->p_Rchild == p)
			status = 1;
		p->p_Lchild = tmp->p_Rchild;
		if (tmp->p_Rchild != nullptr)
			tmp->p_Rchild->p_parent = p;
		tmp->p_Rchild = p;
		p->p_parent = tmp;
		if (status == 0)
			pre->p_Lchild = tmp;
		if (status == 1)
			pre->p_Rchild = tmp;
		tmp->p_parent = pre;
		return;
	}
}

void tree::insert_L_rotate(node* p) {//Finished
	if (p == root) {//if action node is root.
		node* tmp = p->p_Rchild;
		p->p_Rchild = tmp->p_Lchild;
		if (tmp->p_Lchild != nullptr)
			tmp->p_Lchild->p_parent = p;
		tmp->p_Lchild = p;
		root = tmp;
		tmp->p_parent = nullptr;
		p->p_parent = tmp;
	}
	else {//In this case,the action node is not the root.
		int status = -1;
		node* pre = p->p_parent;
		node* tmp = p->p_Rchild;
		if (pre->p_Lchild == p)
			status = 0;
		if (pre->p_Rchild == p)
			status = 1;
		p->p_Rchild = tmp->p_Lchild;
		if (tmp->p_Lchild != nullptr)
			tmp->p_Lchild->p_parent = p;
		tmp->p_Lchild = p;
		p->p_parent = tmp;
		if (status == 0)
			pre->p_Lchild = tmp;
		if (status == 1)
			pre->p_Rchild = tmp;
		tmp->p_parent = pre;
		return;
	}
}
void tree::delete_node(int i) {
	if (root == nullptr)//if the tree has no root.
		return;
	node* tmp = root;
	while (tmp != nullptr && tmp->value != i) {//find the node;
		if (i < tmp->value)
			tmp = tmp->p_Lchild;
		else
			tmp = tmp->p_Rchild;
	}
	if (tmp == nullptr)//Can not find the node.
		return;
	node* tmp2 = nullptr;
	if (tmp->p_Lchild != nullptr)
		tmp2 = tmp->p_Lchild;
	stack<node*> s1;
	while (true) {
		while (tmp2 != nullptr) {
			s1.push(tmp2);
			tmp2 = tmp2->p_Lchild;
		}
		if (s1.empty() == true)
			break;
		node* tmp2 = s1.top();
		s1.pop();
		if (tmp2->value == tmp->value)
			break;
		tmp2 = tmp2->p_Rchild;
	}
	if (tmp2 != nullptr && tmp2->value == tmp->value)
		tmp = tmp2;

	if ((tmp->p_Lchild != nullptr) && (tmp->p_Rchild != nullptr)) {//The node has lchild and rchild.
		node* exc = tmp->p_Lchild;
		while (exc->p_Rchild != nullptr)//To find the predecessor.
			exc = exc->p_Rchild;
		tmp->value = exc->value;
		tmp = exc;//The actual node we need to delete.
	}
	if (tmp->p_Lchild == nullptr && tmp->p_Rchild == nullptr && tmp->color == true) {//In this case,The node we want to delete is just a red leaf node.
		node* parent = tmp->p_parent;
		if (parent->p_Lchild == tmp)
			parent->p_Lchild = nullptr;
		if (parent->p_Rchild == tmp)
			parent->p_Rchild = nullptr;
		delete(tmp);
		return;
	}
	if ((tmp->p_Lchild != nullptr && tmp->p_Rchild == nullptr) || (tmp->p_Lchild == nullptr && tmp->p_Rchild != nullptr)) {//In this case,The node we want to delete only has a single leaf node.
		if (tmp->color == true) {//The deleted node's color is red.
			if (tmp->p_Lchild != nullptr) {
				node* del = tmp->p_Lchild;
				tmp->value = del->value;
				del->p_parent = nullptr;
				tmp->p_Lchild = nullptr;
				tmp->color = false;
				delete(del);
				return;
			}
			if (tmp->p_Rchild != nullptr) {
				node* del = tmp->p_Rchild;
				tmp->value = del->value;
				del->p_parent = nullptr;
				tmp->p_Lchild = nullptr;
				tmp->color = false;
				delete(del);
				return;
			}
		}
		if (tmp->color == false) {//The deleted node's color is black.
			if (tmp->p_Lchild != nullptr) {
				node* del = tmp->p_Lchild;
				tmp->value = del->value;
				del->p_parent = nullptr;
				tmp->p_Lchild = nullptr;
				delete(del);
				return;
			}
			if (tmp->p_Rchild != nullptr) {
				node* del = tmp->p_Rchild;
				tmp->value = del->value;
				del->p_parent = nullptr;
				tmp->p_Rchild = nullptr;
				delete(del);
				return;
			}
		}
	}
	if (tmp == root && tmp->p_Lchild == nullptr && tmp->p_Rchild == nullptr && tmp->color == false) {//The node to be deleted is a black leaf node,and it is a root.
		delete(tmp);
		root = nullptr;
		return;
	}
	if ((tmp->p_Lchild == nullptr && tmp->p_Rchild != nullptr && tmp->color == false && tmp->p_Rchild->color == false) || (tmp->p_Lchild != nullptr && tmp->p_Rchild == nullptr && tmp->color == false && tmp->p_Lchild->color == false)) {
		if (tmp == root) {
			if (tmp->p_Lchild != nullptr) {
				node* del = tmp->p_Lchild;
				tmp->value = del->value;
				tmp->p_Lchild = nullptr;
				del->p_parent = nullptr;
				delete(del);
				return;
			}
			if (tmp->p_Rchild != nullptr) {
				node* del = tmp->p_Rchild;
				tmp->value = del->value;
				tmp->p_Rchild = nullptr;
				del->p_parent = nullptr;
				delete(del);
				return;
			}
		}
	}

	node* spec = tmp->p_parent;
	if (tmp != nullptr && tmp != root && tmp->p_Lchild == nullptr && tmp->p_Rchild == nullptr && tmp->color == false) {
		if (spec->color != true && spec->p_Lchild == tmp) {
			if (spec->p_Rchild != nullptr && spec->p_Rchild->color == false && spec->p_Rchild->p_Lchild == nullptr && spec->p_Rchild->p_Rchild == nullptr) {
				spec->p_Lchild = nullptr;
				tmp->p_parent = nullptr;
				spec->p_Rchild->color = true;
				spec = spec->p_parent;
			}
		}
		else {
			if (spec->color != true && spec->p_Rchild == tmp) {
				if (spec->p_Lchild != nullptr && spec->p_Lchild->color == false && spec->p_Lchild->p_Lchild == nullptr && spec->p_Lchild->p_Rchild == nullptr) {
					spec->p_Rchild = nullptr;
					tmp->p_parent = nullptr;
					spec->p_Lchild->color = true;
					spec = spec->p_parent;
				}
			}
		}
	}
	while (true) {
		//!!case1
		if (spec != nullptr && spec->p_Rchild != nullptr && spec->p_Rchild != tmp && spec->p_Rchild->color == false && (((spec->p_Rchild->p_Lchild != nullptr && spec->p_Rchild->p_Lchild->color == true) || (spec->p_Rchild->p_Rchild != nullptr && spec->p_Rchild->p_Rchild->color == true)))) {
			node* tmp_parent = spec;
			if (spec->p_Lchild == tmp) {
				spec->p_Lchild = nullptr;
				tmp->p_parent = nullptr;
			}
			delete(tmp);
			delete_1(tmp_parent);
			if (spec->p_Rchild != nullptr && spec->p_Lchild != nullptr && spec->p_Lchild->color == true) {
				tmp = spec->p_Rchild;
				continue;
			}
			return;
		}
		if (spec != nullptr && spec->p_Lchild != nullptr && spec->p_Lchild != tmp && spec->p_Lchild->color == false && ((spec->p_Lchild->p_Lchild != nullptr && spec->p_Lchild->p_Lchild->color == true) || (spec->p_Lchild->p_Rchild != nullptr && spec->p_Lchild->p_Rchild->color == true))) {
			node* tmp_parent = spec;
			if (spec->p_Rchild == tmp) {
				spec->p_Rchild = nullptr;
				tmp->p_parent = nullptr;
			}
			delete(tmp);
			delete_1(tmp_parent);
			return;
		}

		//!!case2a
		if (spec != nullptr && spec->color == false && spec->p_Rchild != nullptr && spec->p_Rchild != tmp && spec->p_Rchild->color == false && ((spec->p_Rchild->p_Lchild != nullptr && spec->p_Rchild->p_Lchild->color == false) && (spec->p_Rchild->p_Rchild != nullptr && spec->p_Rchild->p_Rchild->color == false))) {
			node* del = spec->p_Lchild;
			del->p_parent = nullptr;
			spec->p_Lchild = nullptr;
			delete(del);
			delete_2A(spec);
			tmp = spec;
			spec = spec->p_parent;
			continue;
		}
		if (spec != nullptr && spec->color == false && spec->p_Lchild != nullptr && spec->p_Lchild != tmp && spec->p_Lchild->color == false && ((spec->p_Lchild->p_Lchild != nullptr && spec->p_Lchild->p_Lchild->color == false) && (spec->p_Lchild->p_Rchild != nullptr && spec->p_Lchild->p_Rchild->color == false))) {
			node* del = spec->p_Rchild;
			del->p_parent = nullptr;
			spec->p_Rchild = nullptr;
			delete(del);
			delete_2A(spec);
			tmp = spec;
			spec = spec->p_parent;
			continue;
		}
		//!!case2b
		if (spec != nullptr && spec->color == true && spec->p_Rchild != nullptr && spec->p_Rchild != tmp && spec->p_Rchild->color == false && (((spec->p_Rchild->p_Lchild != nullptr && spec->p_Rchild->p_Lchild->color == false) && (spec->p_Rchild->p_Rchild != nullptr && spec->p_Rchild->p_Rchild->color == false)) || (spec->p_Rchild->p_Lchild == nullptr && spec->p_Rchild->p_Rchild == nullptr))) {
			node* del = spec->p_Lchild;
			if (del->p_Lchild == nullptr && del->p_Rchild == nullptr) {
				del->p_parent = nullptr;
				spec->p_Lchild = nullptr;
				delete(del);
			}
			delete_2B(spec);
			return;
		}
		if (spec != nullptr && spec->color == true && spec->p_Lchild != nullptr && spec->p_Lchild != tmp && spec->p_Lchild->color == false && (((spec->p_Lchild->p_Lchild != nullptr && spec->p_Lchild->p_Lchild->color == false) && (spec->p_Lchild->p_Rchild != nullptr && spec->p_Lchild->p_Rchild->color == false)) || (spec->p_Lchild->p_Lchild == nullptr && spec->p_Lchild->p_Rchild == nullptr))) {
			node* del = spec->p_Rchild;
			if (del->p_Lchild == nullptr && del->p_Rchild == nullptr) {
				del->p_parent = nullptr;
				spec->p_Rchild = nullptr;
				delete(del);
			}
			delete_2B(spec);
			return;
		}

		//!!case3
		if (spec != nullptr && spec->p_Rchild != nullptr && spec->p_Rchild != tmp && spec->p_Rchild->color == true) {
			bool exc_color = spec->color;
			spec->color = spec->p_Rchild->color;
			node* mark = spec->p_Rchild;
			delete_3(spec);
			mark->color = exc_color;
			continue;
		}
		if (spec != nullptr && spec->p_Lchild != nullptr && spec->p_Lchild != tmp && spec->p_Lchild->color == true) {
			bool exc_color = spec->color;
			spec->color = spec->p_Lchild->color;
			node* mark = spec->p_Lchild;
			delete_3(spec);
			mark->color = exc_color;
			continue;
		}
	}
}
void tree::delete_1(node* p) {//case 1 of delete_node; p points to the parent of double black node
	if (p->p_Lchild == nullptr || (p->p_Lchild != nullptr && p->p_Lchild->p_Rchild == nullptr)) {//double black node is the left child.
		if (p->p_Rchild != nullptr && p->p_Rchild->p_Rchild != nullptr && p->p_Rchild->p_Rchild->color == true) {//The childs of sibling are both red. 
			delete_1_L_rotate(p);
			return;
		}
		if (p->p_Rchild != nullptr && p->p_Rchild->p_Lchild != nullptr && p->p_Rchild->p_Lchild->color == true && ((p->p_Rchild->p_Rchild != nullptr && p->p_Rchild->p_Rchild->color == false) || (p->p_Rchild->p_Rchild == nullptr))) {
			node* temp = p->p_Rchild;
			node* temp2 = p->p_Rchild->p_Lchild;
			temp2->p_parent = p;
			p->p_Rchild = temp2;
			temp->p_parent = temp2;
			if (temp2->p_Rchild != nullptr) {
				temp->p_Lchild = temp2->p_Rchild;
				temp2->p_Rchild->p_parent = temp;
			}
			else
				temp->p_Rchild = nullptr;
			temp2->p_Rchild = temp;
			temp2->color = false;
			temp->color = true;
			delete_1_L_rotate(p);
			return;
		}
		if (p->color == true && p->p_Rchild != nullptr && p->p_Rchild->color == false  && p->p_Rchild->p_Rchild != nullptr && p->p_Rchild->p_Rchild->color == false && p->p_Rchild->p_Lchild != nullptr && p->p_Rchild->p_Lchild->color == false) {
			p->color = false;
			p->p_Rchild->color = true;
			return;
		}
	}
	if (p->p_Rchild == nullptr || (p->p_Rchild != nullptr && p->p_Rchild->p_Rchild == nullptr)) {//double black node is the right child.
		if (p->p_Lchild != nullptr && p->p_Lchild->p_Lchild != nullptr && p->p_Lchild->p_Lchild->color == true) {//The childs of sibling are both red. 
			delete_1_R_rotate(p);
			return;
		}
		if (p->p_Lchild->p_Rchild != nullptr && p->p_Lchild->p_Rchild->color == true && ((p->p_Lchild->p_Lchild != nullptr && p->p_Lchild->p_Lchild->color == false) || (p->p_Lchild->p_Lchild == nullptr))) {
			node* temp = p->p_Lchild;
			node* temp2 = p->p_Lchild->p_Rchild;
			temp2->p_parent = p;
			p->p_Lchild = temp2;
			temp->p_parent = temp2;
			if (temp2->p_Lchild != nullptr) {
				temp->p_Rchild = temp2->p_Lchild;
				temp2->p_Lchild->p_parent = temp;
			}
			else
				temp->p_Rchild = nullptr;
			temp2->p_Lchild = temp;
			temp2->color = false;
			temp->color = true;
			delete_1_R_rotate(p);
			return;
		}
		if (p->color == true && p->p_Lchild != nullptr && p->p_Lchild->color == false && p->p_Lchild->p_Rchild != nullptr && p->p_Lchild->p_Rchild->color == false && p->p_Lchild->p_Lchild != nullptr && p->p_Lchild->p_Lchild->color == false) {
			p->color = false;
			p->p_Lchild->color = true;
			return;
		}
	}
}
void tree::delete_1_R_rotate(node* p) {//R_totate used in case 1 of delete_node; p points to the parent of double black node
	bool tmp_color = p->color;
	p->color = false;
	p->p_Lchild->p_Lchild->color = false;
	if (p == root) {//if action node is root.
		node* tmp = p->p_Lchild;
		p->p_Lchild = tmp->p_Rchild;
		if (tmp->p_Rchild != nullptr)
			tmp->p_Rchild->p_parent = p;
		tmp->p_Rchild = p;
		root = tmp;
		tmp->p_parent = nullptr;
		p->p_parent = tmp;
	}
	else {//In this case,the action node is not the root.
		int status = -1;
		node* pre = p->p_parent;
		node* tmp = p->p_Lchild;
		if (pre->p_Lchild == p)
			status = 0;
		if (pre->p_Rchild == p)
			status = 1;
		p->p_Lchild = tmp->p_Rchild;
		if (tmp->p_Rchild != nullptr)
			tmp->p_Rchild->p_parent = p;
		tmp->p_Rchild = p;
		p->p_parent = tmp;
		if (status == 0)
			pre->p_Lchild = tmp;
		if (status == 1)
			pre->p_Rchild = tmp;
		tmp->p_parent = pre;
	}
	p->p_parent->color = tmp_color;
}
void tree::delete_1_L_rotate(node* p) {//L_totate used in case 1 of delete_node; p points to the parent of double black node}
	bool tmp_color = p->color;
	p->color = false;
	p->p_Rchild->p_Rchild->color = false;
	if (p == root) {//if action node is root.
		node* tmp = p->p_Rchild;
		p->p_Rchild = tmp->p_Lchild;
		if (tmp->p_Lchild != nullptr)
			tmp->p_Lchild->p_parent = p;
		tmp->p_Lchild = p;
		root = tmp;
		tmp->p_parent = nullptr;
		p->p_parent = tmp;
	}
	else {//In this case,the action node is not the root.
		int status = -1;
		node* pre = p->p_parent;
		node* tmp = p->p_Rchild;
		if (pre->p_Lchild == p)
			status = 0;
		if (pre->p_Rchild == p)
			status = 1;
		p->p_Rchild = tmp->p_Lchild;
		if (tmp->p_Lchild != nullptr)
			tmp->p_Lchild->p_parent = p;
		tmp->p_Lchild = p;
		p->p_parent = tmp;
		if (status == 0)
			pre->p_Lchild = tmp;
		if (status == 1)
			pre->p_Rchild = tmp;
		tmp->p_parent = pre;
	}
	p->p_parent->color = tmp_color;
}
void tree::delete_2A(node* p) {//case 2A of delete_node; p points to the parent of double black node
	if (p->p_Lchild == nullptr)
		p->p_Rchild->color = true;
	if (p->p_Rchild == nullptr)
		p->p_Lchild->color = true;
}
void tree::delete_2B(node* p) {//case 2B of delete_node; p points to the parent of double black node
	if (p->p_Lchild == nullptr || (p->p_Lchild != nullptr && p->p_Lchild->p_Rchild == nullptr && p->p_Lchild->p_Lchild != nullptr && p->p_Lchild->p_Lchild->color == true)) {
		p->p_Rchild->color = true;
		p->color = false;
	}
	if (p->p_Rchild == nullptr || (p->p_Rchild != nullptr && p->p_Rchild->p_Lchild == nullptr && p->p_Rchild->p_Rchild != nullptr && p->p_Rchild->p_Rchild->color == true)) {
		p->p_Lchild->color = true;
		p->color = false;
	}
}
void tree::delete_3(node* p) {//case 3 of delete_node; p points to the parent of double black node
	if (p->p_Rchild->color == true) {//To perform a L-rotate
		insert_L_rotate(p);
		return;
	}
	if (p->p_Lchild->color == true) {//To perform a R-rotate
		insert_R_rotate(p);
		return;
	}
}
void tree::InorderPrint(node* p) {
	if (p) {
		if (p->p_Lchild) {
			InorderPrint(p->p_Lchild);
		}
		cout << "(Value:" << p->value;
		if (p->color == true)
			cout << " Color: red)" << endl;
		if (p->color == false)
			cout << " Color: black)" << endl;
		if (p->p_Rchild) {
			InorderPrint(p->p_Rchild);
		}
	}
}

void tree::PostorderPrint(node* p) {
	if (p) {
		if (p->p_Lchild) {
			PostorderPrint(p->p_Lchild);
		}
		if (p->p_Rchild) {
			PostorderPrint(p->p_Rchild);
		}
		cout << "(Value:" << p->value;
		if (p->color == true)
			cout << " Color: red)" << endl;
		if (p->color == false)
			cout << " Color: black)" << endl;
	}
}

void tree::PreorderPrint(node* p) {
	if (p) {
		cout << "(Value:" << p->value;
		if (p->color == true)
			cout << " Color: red)" << endl;
		if (p->color == false)
			cout << " Color: black)" << endl;
		if (p->p_Lchild) {
			PreorderPrint(p->p_Lchild);
		}
		if (p->p_Rchild) {
			PreorderPrint(p->p_Rchild);
		}
	}
}

int main() {
	tree p1;
	p1.insert_node(47);
	p1.insert_node(32);
	p1.insert_node(71);
	p1.insert_node(31);
	p1.insert_node(35);
	p1.insert_node(34);
	p1.insert_node(44);
	p1.delete_node(47);
	p1.delete_node(44);
	p1.insert_node(100);
	p1.insert_node(101);
	p1.insert_node(102);
	p1.insert_node(103);
	p1.insert_node(104);
	p1.delete_node(35);
	p1.InorderPrint(p1.root);
	getchar();
	getchar();
	return 0;
}