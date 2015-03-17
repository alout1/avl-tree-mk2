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

class Element 
{
public:
    Element(int val, int pos);
    
    friend std::ostream& operator<<(std::ostream& out, Element e);
    friend bool operator<(const Element& l, const Element& r);
    
    int value;
    int position;
};

class AvlTree
{
public:
    AvlTree(int n);
    AvlTree(std::initializer_list<int> args);
    
   // ~AvlTree();
    
    void insert(int val, int pos);
    void erase(int pos);
    std::multiset<Element>::iterator find(int val);
    
    friend std::ostream& operator<<(std::ostream& out, AvlTree& t);
      
    // "логические" операции, каждая по O(n*log(n)))
    AvlTree& operator|(AvlTree& t);    //  \/ объединение
    AvlTree& operator&(AvlTree& t);    //  /\ пересечение 
    AvlTree& operator/(AvlTree& t);    //    \  вычитание
    
    // функции для последовательностей: слияние, подстановка, замена
    void merge(AvlTree& t);
    void subst(AvlTree& t, int pos);
    void change(AvlTree& t, int pos);
    

private:
    std::multiset<Element> data;
    std::vector<std::multiset<Element>::iterator> sequence;
    
    // "настройки": диапазон генерируемых значений
    static const int MINVALUE = 0;
    static const int MAXVALUE = 100;
    
};

#endif	/* AVL_TREE_MK2_H */

