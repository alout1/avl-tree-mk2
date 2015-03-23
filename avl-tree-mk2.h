#ifndef AVL_TREE_MK2_H
#define	AVL_TREE_MK2_H

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <initializer_list>
#include <chrono>
#include <random>

#define MINVALUE 0
#define MAXVALUE 100

class Tree
{
public:
    // конструкторы: n случайных элементов или последовательность
    Tree(int n = 10);
    Tree(std::initializer_list<int> args);
    
    // формальные базовые операции структуры данных
    void insert(int val, int pos);
    void erase(int pos);
    std::multiset<int>::iterator find(int val) const;
    
    // перегрузка операции арифметического сдвига для вывода
    friend std::ostream& operator<<(std::ostream& out, Tree& t);
      
    // "логические" операции, каждая по O(n*log(n)))
    Tree& operator|(const Tree& t);    //  \/ объединение
    Tree& operator&(const Tree& t);    //  /\ пересечение 
    Tree& operator/(const Tree& t);    //    \  вычитание
    
    // функции для последовательностей: слияние, подстановка, замена
    void merge(Tree& t);
    void subst(Tree& t, int pos);
    void change(Tree& t, int pos); 
    

private:
    std::multiset<int> data;
    std::vector<std::multiset<int>::iterator> sequence;    
};

#endif	/* AVL_TREE_MK2_H */

