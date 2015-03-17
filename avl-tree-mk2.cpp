#include "avl-tree-mk2.h"

Element::Element(int val, int pos)
{
    value = val;
    position = pos;
}

std::ostream& operator<<(std::ostream& out, Element e)
{
    out << e.value;
    return out;
}

bool operator<(const Element& l, const Element& r) // нужен для std::sort
{
    return l.value < r.value;
}

bool operator==(const Element& l, const Element& r) // для multiset::find
{
    return l.value == r.value;
}

AvlTree::AvlTree(int n)
{
    sequence.resize(n);
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    for (int i = 0; i < n; ++i)
        sequence[i] = data.insert(Element(generator() % (MAXVALUE - MINVALUE) + MINVALUE, sequence.size()));
}

AvlTree::AvlTree(std::initializer_list<int> args)
{
    int i = 0;
    sequence.resize(args.size());
    for (auto it = args.begin(); it != args.end(); ++it) 
        sequence[i++] = data.insert(Element(*it, sequence.size()));
}

void AvlTree::insert(int val, int pos) 
{
    if (pos > sequence.size())
        pos = sequence.size();
    sequence.resize(sequence.size() + 1);
    for (int i = sequence.size(); i > pos ; --i)
        sequence[i] = sequence[i-1];
    sequence[pos] = data.insert(Element(val, pos));
}

void AvlTree::erase(int pos)
{
    if (pos > sequence.size())
        return;
    data.erase(sequence[pos]);
    for (int i = pos; i < sequence.size(); ++i)
        sequence[i] = sequence[i+1];
    sequence.resize(sequence.size() - 1);
}

std::multiset<Element>::iterator AvlTree::find(int val)
{
    return data.find(Element(val, 0));
}

AvlTree& AvlTree::operator|(AvlTree& t)
{
    std::multiset<Element> result;
    std::set_union(this->data.begin(), this->data.end(), t.data.begin(), t.data.end(), std::inserter(result, result.end()));
    data = result;
    sequence.clear();
    for(auto it = data.begin(); it != data.end(); ++it) 
        sequence.push_back(it);
    return *this;
}

AvlTree& AvlTree::operator&(AvlTree& t)
{
    std::multiset<Element> result;
    std::set_intersection(this->data.begin(), this->data.end(), t.data.begin(), t.data.end(), std::inserter(result, result.end()));
    data = result;
    sequence.clear();
    for(auto it = data.begin(); it != data.end(); ++it)
        sequence.push_back(it);
    return *this;
}

AvlTree& AvlTree::operator/(AvlTree& t)
{
    std::multiset<Element> result;
    std::set_difference(this->data.begin(), this->data.end(), t.data.begin(), t.data.end(), std::inserter(result, result.end()));
    data = result;
    sequence.clear();
    for(auto it = data.begin(); it != data.end(); ++it) 
        sequence.push_back(it);
    return *this;
}

std::ostream& operator<<(std::ostream& out, AvlTree& t)
{
    out << "{ ";
   for (auto it = t.sequence.begin(); it != t.sequence.end(); ++it)
       out << **it << ' ';
    out << "} \n";
   return out;
}

bool comparator(std::multiset<Element>::iterator l, std::multiset<Element>::iterator r) 
{
    return l->value < r->value;
}

void AvlTree::merge(AvlTree& t) // O(n*log(n))
{  
    std::sort(sequence.begin(), sequence.end(), comparator);
    std::sort(t.sequence.begin(), t.sequence.end(), comparator); // изменяет правую последовательность. нехорошо.
    
    std::multiset<Element> result;
    std::merge(*(sequence.begin()), *(sequence.end()), 
                *(t.sequence.begin()), *(t.sequence.end()), 
                std::inserter(result, result.end())); // хрень какая-то. проверить
    data = result;
    sequence.clear();
    for(auto it = data.begin(); it != data.end(); ++it) 
        sequence.push_back(it);
}

void AvlTree::subst(AvlTree& t, int pos) // O(n*log(n))
{ // нагло врет. поправить
    if (pos > sequence.size())
        pos = sequence.size();
    
    // новый размер последовательности
    sequence.resize(sequence.size() + t.sequence.size() - pos);
    
    // перестановка элементов с позиции pos на t.sequence.size() ячеек вправо
    for (auto it = sequence.end(); it != sequence.begin() + pos; --it)
        *it = *(it - t.sequence.size());
    
    // вставка элементов из t
    int i = 0;
    for (auto it = t.sequence.begin() + pos; it != t.sequence.end(); ++it)
        sequence[pos + i++] = data.insert(Element((**it).value, pos + i ));
}

void AvlTree::change(AvlTree& t, int pos) //  O(n*log(n)) в худшем
{                                         // можно сделать линейную в среднем, но лень 
    
    // падает -___-
    
    // проверка слишком большого pos 
    if (pos > sequence.size())
        pos = sequence.size();
    
    // если вторря последовательность не влезает в середину первой, увеличить первую
    if (sequence.size() < t.sequence.size() + pos)
        sequence.resize(t.sequence.size() + pos);
    
    //  замена, пока не прошли левую, а потом вставка в конец левой
    int i = 0;
    for (auto it = t.sequence.begin(); it != t.sequence.end(); ++it, ++i)
    {
        if (pos+i < sequence.size())
            data.erase(sequence[pos+i]);
        sequence[pos + i] = data.insert(Element( (**it).value, pos + i));  
    }
}