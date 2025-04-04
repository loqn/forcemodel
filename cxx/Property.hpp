#ifndef PROPERTY_HPP
#define PROPERTY_HPP
#include <map>
#include "Node.hpp"
#include "Edge.hpp"
#include <cassert>

template<typename T>
class Property
{
private:
    std::map<Node, T> nodes_values;
    std::map<Edge, T> edges_values;

public:
    Property() = default;

    void change(Node n, const T &val);
    void change(Edge e, const T &val);

    const T & value(Node n) const;
    const T & value(Edge e) const;

    void remove(Node n);
    void remove(Edge e);
};

template<typename T>
void Property<T>::change(Node n, const T &val){
    nodes_values[n] = val;
}

template<typename T>
void Property<T>::change(Edge e, const T &val){
    edges_values[e] = val;
}

template<typename T>
const T & Property<T>::value(Node n) const{
    assert(nodes_values.find(n) != nodes_values.end());
    return nodes_values.at(n);
}

template<typename T>
const T & Property<T>::value(Edge e) const{
    assert(edges_values.find(e) != edges_values.end());
    return edges_values.at(e);
}

template<typename T>
void Property<T>::remove(Node n) {
    assert(nodes_values.find(n) != nodes_values.end());
    nodes_values.erase(nodes_values.find(n));
}

template<typename T>
void Property<T>::remove(Edge e) {
    assert(edges_values.find(e) != edges_values.end());
    edges_values.erase(edges_values.find(e));
}

#endif // PROPERTY_HPP
