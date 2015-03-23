#include "avl-tree-mk2.h"

int main(int argc, char** argv) {

    Tree t({1,2,3,4,5}), k({7,8,9}), p({0,0,0,0,0});
    std::cout << t << k << p;
    
    t.merge(k);
    std::cout <<'\n' << t ;
    
    t.subst(k, 0);
    std::cout << t;
    
    t.change(p, 3);
    std::cout <<t;
    return 0;
}

