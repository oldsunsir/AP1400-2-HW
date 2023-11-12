#ifndef BST_H
#define BST_H
#include<iostream>
#include<functional>
class BST{
    public:
        class Node{
            public:
                Node(int value, Node* left, Node* right);
                Node();
                Node(const Node& node);

                int value;
                Node* left;
                Node* right;
        };
        Node*& get_root();
        void bfs(std::function<void(Node*& node)> func);
        size_t length()const;
        bool add_node(int value);
        Node** find_node(int value);
        Node** find_parrent(int value);
        Node** find_successor(int value);
        bool delete_node(int value);
        BST& operator++();
        BST operator++(int);

        BST();
        Node* copyTree(Node* root);
        BST(const BST& other);
        BST(BST&& other);
        BST(std::initializer_list<int> list);
        ~BST();

        BST& operator=(BST& other);
        BST& operator=(BST&& other);
    private:
        Node* root;
};
std::ostream& operator << (std::ostream& os, BST b);
std::ostream& operator << (std::ostream& os, BST::Node node);
bool operator == (const BST::Node& node, const int& num);
bool operator == (const int& num, const BST::Node& node);

bool operator < (const BST::Node& node, const int& num);
bool operator < (const int& num, const BST::Node& node);

bool operator <= (const BST::Node& node, const int& num);
bool operator <= (const int& num, const BST::Node& node);

bool operator > (const BST::Node& node, const int& num);
bool operator > (const int& num, const BST::Node& node);

bool operator >= (const BST::Node& node, const int& num);
bool operator >= (const int& num, const BST::Node& node);

#endif