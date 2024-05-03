#include <iostream>
#include <string>

using namespace std;

class RBT;
class Node{
private:
    Node *left;
    Node *right;
    Node *parent;
    int key;
    int color; //0: Red, 1: Black
    friend class RBT;
public:
    Node():left(0),right(0),parent(0),key(0),color(0){}
    Node(int key):left(0),right(0),parent(0),key(key),color(0){}
    
    int GetKey() const{return key;};
};

class RBT{
private:
    Node *root;
    Node *neel;

    void LeftRotate(Node *current);
    void RightRotate(Node *current);
    void CheckInsert(Node *current);
    void CheckDelete(Node *current);
    Node* Successor(Node *current);
    Node* Leftest(Node *current);
public:
    RBT(){
        neel = new Node;
        neel->color = 1;
        root = neel;
        root->parent = neel;
    };
    
    Node *start;
    void Insert(int key);
    void Delete(int KEY);
    void Print(class Node* current);
    Node* Find(int KEY);
};

/*struct Node{
    int data;
    struct Node *left, *right;
};*/

void RBT::Print(Node* current)
{
    if (current == NULL)
        return;
    if (current == neel)
        return;
    Print(current->left);
    cout << "key: " << current->key;
    cout << " parent: ";
    if((current->parent->key)==0)
        cout << "   ";
    else
        cout << current->parent->key;
    if((current->color)==0)
        cout << " color: red\n ";
    else if((current->color)==1)
        cout << " color: black\n";
    
    Print(current->right);
}

void RBT::Delete(int KEY){
    
    Node *DeleteNode = Find(KEY);
    if (DeleteNode == NULL) {
        cout << "WRONG INPUT!\n";
        return;
    }

    Node *y=0;
    Node *x=0;

    if((DeleteNode->left) == neel || (DeleteNode->right) == neel)
        y = DeleteNode;
    else
        y = Successor(DeleteNode);
    
    if((y->left) != neel)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;

    if((y->parent) == neel)
        this->root = x;
    else if(y == y->parent->left){
        y->parent->left = x;
    }
    else{
        y->parent->right = x;
    }

    if(y != DeleteNode)
        DeleteNode->key = y->key;

    if(y->color == 1)
        CheckDelete(x);
        
}

void RBT::CheckDelete(Node *current){
    //current is red or root->black
    while(current != root && (current->color) == 1){
        // current是leftchild
        if(current == current->parent->left){
            Node *sibling = current->parent->right;
            if((sibling->color)==0){
                sibling->color = 1;
                current->parent->color = 0;
                LeftRotate(current->parent);
                sibling = current->parent->right;
            }
            if(sibling->left->color == 1 && sibling->right->color == 1){
                sibling->color = 0;
                current = current->parent; //到root的時候跳出去
            }
            else{
                if(sibling->right->color==1){
                    sibling->left->color = 1;
                    sibling->color = 0;
                    RightRotate(sibling);
                    sibling = current->parent->right;
                }
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->right->color = 1;
                LeftRotate(current->parent);
                current = root;
            }
        }
        // current是rightchild
        else{
            Node *sibling = current->parent->left;
            //sibling red
            if(sibling->color==0){
                sibling->color = 1;
                current->parent->color = 0;
                RightRotate(current->parent);
                sibling = current->parent->left;
            }
            if(sibling->left->color==1 && sibling->right->color==1){
                sibling->color = 0;
                current = current->parent; // 若current更新到root, 即跳出迴圈
            }
            else{
                if(sibling->left->color==1){
                    sibling->right->color = 1;
                    sibling->color = 0;
                    LeftRotate(sibling);
                    sibling = current->parent->left;
                }
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->left->color = 1;
                RightRotate(current->parent);
                current = root; // 將current移動到root, 一定跳出迴圈
            }
        }
    }
    current->color = 1;
}

void RBT::Insert(int key){
    Node *y = neel;
    Node *x = root;
    Node *InsertNode = new Node(key);

    while(x!=neel){
        y = x;
        if (InsertNode->key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    InsertNode->parent = y;

    if (y==neel){
        this->root = InsertNode;
    }
    else if (InsertNode->key < y->key){
        y->left = InsertNode;
    }
    else{
        y->right = InsertNode;
    }
    
    InsertNode->left = neel;
    InsertNode->right = neel;
    InsertNode->color = 0;
        
    CheckInsert(InsertNode);      //red-red
}

void RBT::CheckInsert(Node *current){
    while(current->parent->color==0){
        //parent is left child
        if(current->parent==current->parent->parent->left){
            Node *uncle = current->parent->parent->right;
            //uncle red
            if(uncle->color==0){
                current->parent->color = 1;
                uncle->color = 1;
                current->parent->parent->color = 0;  //grandparent red
                current = current->parent->parent;
            }
            //uncle black
            else{
                if(current==current->parent->right){
                    current = current->parent;
                    LeftRotate(current);
                }
                current->parent->color = 1;  //parent black
                current->parent->parent->color = 0;  // grandparent red
                RightRotate(current->parent->parent);
            }
        }
        //parent is right child
        else{
            Node *uncle = current->parent->parent->left;
            if(uncle->color==0){
                current->parent->color = 1;
                uncle->color = 1;
                current->parent->parent->color = 0;
                current = current->parent->parent;
            }
            else{
                if(current==current->parent->left){
                    current = current->parent;
                    RightRotate(current);
                }
                current->parent->color = 1;
                current->parent->parent->color = 0;
                LeftRotate(current->parent->parent);
            }
        }
    }
    root->color = 1; //root is black
}

void RBT::LeftRotate(Node *x){
    Node *y = x->right;
    x->right = y->left;

    if(y->left!=neel){
        y->left->parent = x;
    }
    y->parent = x->parent;

    if(x->parent == neel){
        root = y;
    }
    //原本是什麼就是什麼
    else if(x==x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    start = root;
}

void RBT::RightRotate(Node *y){
    Node *x = y->left;
    y->left = x->right;
    
    if(x->right!=neel){
        x->right->parent = y;
    }
    x->parent = y->parent;
    
    if(y->parent==neel){
        root = x;
    }
    //原本是什麼就是什麼
    else if(y==y->parent->left){
        y->parent->left = x;
    }
    else
        y->parent->right = x;
    
    x->right = y;
    y->parent = x;
    start = root;
}

Node* RBT::Leftest(Node *current){
    while(current->left!=NULL){
        current = current->left;
    }
    return current;
}

Node* RBT::Successor(Node *current){
    if(current->right!=NULL){
        return Leftest(current->right);
    }
    Node *new_node = current->parent;
    while(new_node!=NULL && current==new_node->right){
        current = new_node;
        new_node = new_node->parent;
    }
    return new_node;
}

Node* RBT::Find(int KEY){
    Node *current = root;
    while(current!=NULL && KEY!=current->key){
        if(KEY < current->key)
            current = current->left;
        else
            current = current->right;
    }
    return current;
}

int main(){
    RBT tree;
    int t;
    cin >> t;
    for(int i=0; i<t; i++){
        int op;
        int n;
        int key[25];
        cin >> op >> n;
        
        if(op==1){
            for(int j=0; j<n; j++){
                cin >> key[j];
                tree.Insert(key[j]);
            }
            cout << "Insert: ";
            for(int j=0; j<n-1; j++)
                cout << key[j] << ", ";
            cout << key[n-1] << endl;
            tree.Print(tree.start);
        }
        
        else if(op==2){
            for(int j=0; j<n; j++){
                cin >> key[j];
                tree.Delete(key[j]);
            }
            cout << "Delete: ";
            for(int j=0; j<n-1; j++)
                cout << key[j] <<", ";
            cout << key[n-1] << endl;
            tree.Print(tree.start);
        }
        else
            cout << "WRONG INPUT!";
    }
    return 0;
}
