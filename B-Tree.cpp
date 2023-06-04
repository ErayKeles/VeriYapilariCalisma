#include <iostream>
using namespace std;

const int MAX_KEYS = 3;

struct node {
    int key[MAX_KEYS + 1];
    int count;
    node* child[MAX_KEYS + 1];
    bool leaf;
};

node* newnode() {
    node* new_node = new node;
    new_node->count = 0;
    new_node->leaf = true;
    for (int i = 0; i <= MAX_KEYS; i++) {
        new_node->child[i] = NULL;
    }
    return new_node;
}

void inserttree(node*& tree, node* node_) {
    if (tree == NULL) {
        tree = newnode();
        tree->key[1] = node_->key[1];
        tree->count = 1;
        tree->child[0] = NULL;
        tree->child[1] = node_;
    } else {
        if (tree->count < MAX_KEYS) {
            int i = tree->count;
            while (i > 0 && node_->key[1] < tree->key[i]) {
                tree->key[i + 1] = tree->key[i];
                tree->child[i + 1] = tree->child[i];
                i--;
            }
            tree->key[i + 1] = node_->key[1];
            tree->child[i + 1] = node_;
            tree->count++;
        } else {
            int mid = (MAX_KEYS / 2) + 1;
            node* new_node = newnode();
            new_node->child[0] = tree;
            new_node->leaf = false;
            new_node->key[1] = tree->key[mid];
            new_node->child[1] = node_;
            new_node->child[2] = newnode();
            for (int i = mid + 1; i <= MAX_KEYS; i++) {
                new_node->child[2]->key[i - mid] = tree->key[i];
                new_node->child[2]->child[i - mid] = tree->child[i];
            }
            new_node->count = 1;
            tree->count = mid - 1;
            tree->child[0] = new_node;
            tree->child[1] = newnode();
        }
    }
}

void printtree(node* tree) {
    if (tree != NULL) {
        for (int i = 0; i < tree->count; i++) {
            printtree(tree->child[i]);
            cout << tree->key[i + 1] << " ";
        }
        printtree(tree->child[tree->count]);
    }
}

int main() {
    node* btree = NULL;
    node* node1 = newnode();
    node* node2 = newnode();
    node* node3 = newnode();
    
	
	cout << "B-Tree: ";
    printtree(btree);
    cout << endl;
    
	
	node1->key[1] = 1;
    node2->key[1] = 2;
    node3->key[1] = 3;
    
	
	cout << "B-Tree: ";
    printtree(btree);
    cout << endl;
    
	inserttree(btree, node2);
    inserttree(btree, node1);
    inserttree(btree, node3);

    cout << "B-Tree: ";
    printtree(btree);
    cout << endl;

    return 0;
}

