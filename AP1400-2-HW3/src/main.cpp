#include <gtest/gtest.h>
#include<vector>
#include <iostream>

#include "bst.h"
using std::cout;
using std::endl;
int tmpfunc(std::vector<int>&& myvec){
    return myvec.size();
}
int main(int argc, char** argv) {
    if (true)  // make false to run unit-tests
    {
        BST bst{1, 2, 3, 4, 5};
        cout << bst << endl;
        cout << tmpfunc(std::vector<int>(10, 2)) << endl;
        // std::string& tmp = std::string();
    } else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}