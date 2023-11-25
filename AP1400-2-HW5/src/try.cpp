#include<iostream>
#include<vector>

int main(){
    std::vector<int*> side;
    int a = 10, b = 20;
    int* p = &a;
    int* q = &b;
    side.push_back(p);
    side.push_back(q);
    std::cout << side.size() << std::endl;
    delete p;
    std::cout << side.size() << std::endl;
}