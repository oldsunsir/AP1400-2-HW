#include"bst.h"
#include<queue>
#include<sstream>
#include<iomanip>
#include<vector>
using std::queue;
using std::ostream;
BST::Node::Node(int value, Node* left, Node* right)
            :value(value), left(left), right(right){}

BST::Node::Node():value(0), left(nullptr), right(nullptr){}

BST::Node::Node(const Node& node){
    this->value = node.value;
    this->left = node.left;
    this->right = node.right;
}

std::ostream& operator << (std::ostream& os, BST::Node node){
    os << "node: " << &node << "\tvalue: " << node.value
       << "\tleft: " << node.left << "\tright" << node.right << "\n";
    return os;
}

bool operator == (const BST::Node& node, const int& num){
    return node.value == num;
}
bool operator == (const int& num, const BST::Node& node){
    return num == node.value;
}
bool operator < (const BST::Node& node, const int& num){
    return node.value < num;
}
bool operator < (const int& num, const BST::Node& node){
    return num < node.value;
}
bool operator <= (const BST::Node& node, const int& num){
    return node.value <= num;
}
bool operator <= (const int& num, const BST::Node& node){
    return num <= node.value;
}
bool operator > (const BST::Node& node, const int& num){
    return node.value > num;
}
bool operator > (const int& num, const BST::Node& node){
    return num > node.value;
}
bool operator >= (const BST::Node& node, const int& num){
    return node.value >= num;
}
bool operator >= (const int& num, const BST::Node& node){
    return num >= node.value;
}

BST::Node*& BST::get_root(){
    return this->root;
}

void BST::bfs(std::function<void(Node*& node)> func){
    if (this->root == nullptr)
        return;
    auto lam = [&func](Node* root){
        if (root == nullptr)
            return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()){
            Node* temp = q.front();
            q.pop();
            Node* left = temp->left;
            Node* right = temp->right;
            if (left != nullptr)
                q.push(left);
            if (right != nullptr)
                q.push(right);
            func(temp);
        }
        return;
    };
    lam(this->root);
}
int num(BST::Node* node){
    if (node == nullptr)
        return 0;
    return 1 + num(node->left) + num(node->right);
}
size_t BST::length()const{
    return num(this->root);
}
bool BST::add_node(int value){
    if (this->root == nullptr){
        this->root = new Node(value, nullptr, nullptr);
        return true;
    }
    Node* p = this->root;
    while (true){
        if (value > *p){
            if (p->right == nullptr)
                break;
            p = p->right;
        }
        else if (value < *p){
            if (p->left == nullptr)
                break;
            p = p->left;
        }
        else break;
    }
    if (value > *p){
        p->right = new Node(value, nullptr, nullptr);
        return true;
    }
    else if (value < *p){
        p->left = new Node(value, nullptr, nullptr);
        return true;
    }
    else return false;
}
BST::Node**  BST::find_node(int value){
    auto cur = this->root;
    while (cur) {
        if (value < *cur)
            cur = cur->left;
        else if (value > *cur)
            cur = cur->right;
        else break;
    }
    if (cur == nullptr)
        return nullptr;
    else{
        auto res = new Node*{cur};
        return res;
    }
}
BST::Node** BST::find_parrent(int value){
    auto cur = this->root;
    Node* pre = nullptr;
    while (cur) {
        if (value > *cur){
            pre = cur, cur = cur->right;
        }
        else if (value < *cur){
            pre = cur, cur = cur->left;
        }
        else break;
    }
    if (cur == nullptr)
        return nullptr;
    else{
        auto res = (pre != nullptr) ? new Node*{pre} : nullptr;
        return res;
    }
}
BST::Node** BST::find_successor(int value){
    auto b = this->find_node(value);
    if (b == nullptr)
        return nullptr;
    if ((*b)->left == nullptr){
        delete b;
        return nullptr;
    }
    auto p = (*b)->left;
    while (p->right != nullptr)
        p = p->right;
    auto res = new Node*{p};
    delete b;
    return res;
}
bool BST::delete_node(int value){
    auto node = find_node(value);
    auto parent = find_parrent(value);
    if (node == nullptr)
        return false;
    if ((*node)->left == nullptr && (*node)->right == nullptr){
        if (parent == nullptr)
            root = nullptr;
        else {
            if (value > (*parent)->value)
                (*parent)->right = nullptr;
            else
                (*parent)->left = nullptr;
        }
    }
    else if((*node)->left != nullptr && (*node)->right != nullptr){
        auto next = find_successor(value);
        auto new_node = new Node{(*next)->value, (*node)->left, (*node)->right};
        delete_node((*next)->value);
        delete next;
        if (parent == nullptr){
            new_node->left = root->left;
            new_node->right = root->right;
            root = new_node;
        }
        else{
            if ((*parent)->left == *node)
                (*parent)->left = new_node;
            else
                (*parent)->right = new_node;
        }
    }
    else{
        Node* new_node = nullptr;
        if ((*node)->left)
            new_node = (*node)->left;
        else
            new_node = (*node)->right;
        if (parent == nullptr){
            new_node->left = root->left;
            new_node->right = root->right;
            root = new_node;
        }
        else{
            if ((*parent)->left == *node)
                (*parent)->left = new_node;
            else
                (*parent)->right = new_node;
        }
    }
    if (parent) delete parent;
    if (node){
        delete *node;
        delete node;
    }
    return true;
}

ostream& operator<<(ostream& os, BST b){
    os << "********************************************************************************\n";
    if (b.get_root() == nullptr){}
    else{
        queue<BST::Node*> q;
        q.push(b.get_root());
        while (!q.empty()){
            BST::Node* temp = q.front();
            q.pop();
            BST::Node* left = temp->left;
            BST::Node* right = temp->right;
            if (left != nullptr)
                q.push(left);
            if (right != nullptr)
                q.push(right);
            std::stringstream ss;
            ss << std::left << std::setw(17) << temp << "=> value:" << std::setw(10)
                    << temp->value;
            if (temp->left == nullptr)
                ss << "left:0               ";
            else{
                ss << "left:" << std::setw(16) << temp->left;
            }
            if (temp->right == nullptr)
                ss << "right:0               ";
            else{
                ss << "right:" << std::setw(16) << temp->right;
            }
            os << ss.str() << std::endl;
        }
    }
    os << "binary search tree size: " << b.length() << "\n";
    os << "********************************************************************************\n";
    return os;
}

//++bst
BST& BST::operator++(){
    auto plus = [](Node*& node){node->value += 1;};
    bfs(plus);
    return *this;
}
BST BST::operator++(int){
    BST b = BST(*this);
    auto plus = [](Node*& node){node->value += 1;};
    bfs(plus);
    return b;
}
BST::BST(){
    this->root = nullptr;
}
BST::Node* BST::copyTree(Node* root){
    if (root == nullptr)
        return nullptr;
    Node* newRoot = new Node(root->value, nullptr, nullptr);
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);
    return newRoot;
}
BST::BST(const BST& other){
    this->root = copyTree(other.root);
}
BST::BST(BST&& other){
    this->root = other.root;
    other.root = nullptr;
}
BST::~BST(){
    std::vector<Node*> nodes;
    bfs([&nodes](Node*& node){nodes.push_back(node);});
    for (auto& node:nodes)
        delete node;
}
BST& BST::operator=(BST& b){
    this->root = copyTree(b.root);
    return *this;
}
BST& BST::operator=(BST&& b){
    this->root = b.root;
    b.root = nullptr;
    return *this;
}
BST::BST(std::initializer_list<int> list){
    this->root = nullptr;
    if (list.size() == 0){}
    else{
        for (auto num : list)
            add_node(num);
    }
}