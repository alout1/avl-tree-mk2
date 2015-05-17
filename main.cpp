#include "avl-tree-mk2.h"
#include <fstream>

#define SET_SIZE_MIN 10
#define SET_SIZE_MAX 200
#define N_TESTS 190


int main(int argc, char** argv) {
    
    std::ofstream outfile("in.txt", std::fstream::out | std::fstream::trunc);
    outfile << N_TESTS << std::endl; 

    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::chrono::duration<double> time_span;
    std::chrono::steady_clock::time_point t1, t2; 
    
    for (int i = SET_SIZE_MIN; i <= SET_SIZE_MAX; ++i)
    {
        Tree* setA = new Tree(i);
        Tree* setB = new Tree(i);
        Tree* setC = new Tree(i);
        Tree* setD = new Tree(i);
        Tree* setE = new Tree(i);
        Tree* setF = new Tree(i);
        Tree* setG = new Tree(i);
        Tree* setResult = new Tree(0);
        
        outfile << i << ' ';
        t1 = std::chrono::steady_clock::now();
        //----------
        *setResult = (*setA | *setB & *setC / *setD)
                    .merge(*setE)
                    .subst(*setF, generator() % i )
                    .change(*setG, generator() % i);
        //-----------
        t2 = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        outfile << time_span.count() << std::endl; 
        
        delete setA;
        delete setB;
        delete setC;
        delete setD;
        delete setE;
        delete setF;
        delete setG;
        delete setResult;
    }
    
    outfile.close();
    return 0;
}
