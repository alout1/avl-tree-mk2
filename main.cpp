#include "avl-tree-mk2.h"

int main(int argc, char** argv) {

    AvlTree t({1,2,3,3,4,9}), k({3,4,5,1, 9, 9});
    t.insert(4, 0);
    t.erase(2);
    std::cout << t << k;
    
    std::cout << t ;
    return 0;
}

