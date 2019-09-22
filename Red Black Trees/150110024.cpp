#include <iostream>
#include <fstream>
using namespace std;

struct Node{
	char name[50];
	char gender;
	int age;
	bool red;
	Node *left, *right, *parent;
	Node(){
		left = right = parent = NULL;
		red = false;
	}
};

class Tree{
	private:
		Node *root;
	public:
		void rotateLeft(Node *);
		void rotateRight(Node *);
		void print();
		bool getColor(Node *);
		Tree(){ root = NULL; }
		void insert(Node *);
};

bool Tree::getColor(Node *node) {
    if (node == NULL)
        return false;

    return true;
}

void inorder(Node *root)
{
    if (root == NULL){
    	return;
	}
        
    inorder(root->left);
    if(root->red){
    	cout << root->name << "(R)" << endl;
	}
    else
    	cout << root->name << "(B)" << endl;
    inorder(root->right);
}

void Tree::print(){
	inorder(root);
}

Node *BSTInsert(Node *root, Node *Newnode){
	Node *current;
	Node *parent;
	if(root == NULL)
		return Newnode;
	else{
		current = root;
		parent = NULL;
		while(true){
			parent = current;
			if(Newnode->name < current->name){
				current = current->left;
				if(current == NULL){
					parent->left = Newnode;
					Newnode->parent = parent;
					return root;
				}
			}
			else{
				current = current->right;
				if(current == NULL){
					parent->right = Newnode;
					Newnode->parent = parent;
					return root;
				}
			}
		}
	}
}

void Tree::rotateLeft(Node *ptr){
	Node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != NULL)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == NULL)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}

void Tree::rotateRight(Node *ptr){
	Node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != NULL)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == NULL)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}

void Tree::insert(Node *Newnode){
	Node *p = NULL;
	Node *grantP = NULL;
	Newnode->red = true;
	root = BSTInsert(root, Newnode);
	while(Newnode != root && getColor(Newnode->parent)){
		p = Newnode->parent;
		grantP = Newnode->parent->parent;
		if(grantP == NULL)
			return;
		if(p == grantP->left){
			Node *uncle = grantP->right;
			if(getColor(uncle)){
				p->red = false;
				uncle->red = false;
				grantP->red = true;
				Newnode = grantP;
			}
			else{
				if(Newnode == p->right){
					rotateLeft(p);
					Newnode = p;
					p = Newnode->parent;
				}
				p->red = false;
				grantP->red = true;
				rotateRight(grantP);
				Newnode = p;
			}
		}
		else{
			Node *uncle = grantP->left;
			if(getColor(uncle)){
				p->red = false;
				uncle->red = false;
				grantP->red = true;
				Newnode = grantP;
			}
			else{
				if(Newnode == p->left){
					rotateRight(p);
					Newnode = p;
					p = Newnode->parent;
				}
				rotateLeft(grantP);
				p->red = false;
				grantP->red = true;
				Newnode = p;
			}
		}
	}
	root->red = false;
}

int main(int argc, char *argv[]){
	ifstream file;
	
	Tree t;
	if(argc != 2){
		cout << "usage ./<student_ID> <input_file> " << endl;
		return 1;
	}
	file.open(argv[1]);
	if(!file.is_open()){
		cout << "sorry we could not opened the file" << endl;
		return -1;
	}
	while(!file.eof()){
		Node *person = new Node;
		file >> person->name;
		file >> person->gender;
		file >> person->age;
		t.insert(person);
	}
	t.print();
	return 0;
}
