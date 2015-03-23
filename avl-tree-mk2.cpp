#include "avl-tree-mk2.h"

Tree::Tree(int n)
{
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    for (int i = 0; i < n; ++i)
        sequence.push_back(data.insert(generator() % (MAXVALUE - MINVALUE) + MINVALUE));
}

Tree::Tree(std::initializer_list<int> args)
{
    for (auto it = args.begin(); it != args.end(); ++it) 
        sequence.push_back(data.insert(*it));
}

void Tree::insert(int val, int pos) 
{
    if (pos > sequence.size())
        pos = sequence.size();
    sequence.resize(sequence.size() + 1);
    for (int i = sequence.size(); i > pos ; --i)
        sequence[i] = sequence[i-1];
    sequence[pos] = data.insert(val);
}

void Tree::erase(int pos)
{
    if (pos > sequence.size())
        return;
    data.erase(sequence[pos]);
    for (int i = pos; i < sequence.size(); ++i)
        sequence[i] = sequence[i+1];
    sequence.resize(sequence.size() - 1);
}

std::multiset<int>::iterator Tree::find(int val) const
{
    return data.find(val);
}

Tree& Tree::operator|(const Tree& t)
{
    std::multiset<int> result;
    std::set_union(this->data.begin(), this->data.end(), t.data.begin(), t.data.end(), std::inserter(result, result.end()));
    data = result;
    sequence.clear();
    for(auto it = data.begin(); it != data.end(); ++it) 
        sequence.push_back(it);
    return *this;
}

Tree& Tree::operator&(const Tree& t)
{
    std::multiset<int> result;
    std::set_intersection(this->data.begin(), this->data.end(), t.data.begin(), t.data.end(), std::inserter(result, result.end()));
    data = result;
    sequence.clear();
    for(auto it = data.begin(); it != data.end(); ++it)
        sequence.push_back(it);
    return *this;
}

Tree& Tree::operator/(const Tree& t)
{
    std::multiset<int> result;
    std::set_difference(this->data.begin(), this->data.end(), t.data.begin(), t.data.end(), std::inserter(result, result.end()));
    data = result;
    sequence.clear();
    for(auto it = data.begin(); it != data.end(); ++it) 
        sequence.push_back(it);
    return *this;
}

std::ostream& operator<<(std::ostream& out, Tree& t)
{
    out << "{ ";
   for (auto it = t.sequence.begin(); it != t.sequence.end(); ++it)
       out << **it << " ";
    out << "} \n";
   return out;
}

bool comparator(std::multiset<int>::iterator l, std::multiset<int>::iterator r) 
{
    return *l < *r;
}

void Tree::merge(Tree& t) 
{  
    std::multiset<int> result;
    std::merge(data.begin(), data.end(), 
                t.data.begin(), t.data.end(), 
                std::inserter(result, result.end())); //  сложность?
    data = result;
    sequence.clear();
    for(auto it = data.begin(); it != data.end(); ++it) 
        sequence.push_back(it);    
}

void Tree::subst(Tree& t, int pos) // O(n*log(n))
{ 
    if (pos > sequence.size())
        pos = sequence.size();
    
    // новый размер последовательности = сумме двух входных. (c)кэп
    sequence.resize(sequence.size() + t.sequence.size());
    
    // перестановка элементов с позиции pos на t.sequence.size() ячеек вправо
    for (auto it = sequence.end(); it != sequence.begin() + pos; --it)
        *it = *(it - t.sequence.size());
    
    // вставка элементов из t
    int i = pos;
    for (auto it = t.sequence.begin(); it != t.sequence.end(); ++it)
        sequence[i++] = data.insert(**it );
}

void Tree::change(Tree& t, int pos) //  O(n*log(n)) в худшем
{                                  // можно сделать линейную в среднем, но лень 
    // проверка слишком большого pos 
    if (pos > sequence.size())
        pos = sequence.size();
    
    // если вторря последовательность не влезает в середину первой, увеличить первую
    if (sequence.size() < t.sequence.size() + pos)
        sequence.resize(t.sequence.size() + pos);
    
    //  замена, пока не прошли левую, а потом вставка в конец левой
    int i = pos;
    for (auto it = t.sequence.begin(); it != t.sequence.end(); ++it)
    {
        if (pos+i < sequence.size())
            data.erase(sequence[i]);
        sequence[i] = data.insert(**it);
        ++i;
    }
}