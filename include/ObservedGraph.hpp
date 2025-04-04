#ifndef OBSERVEDGRAPH_HPP
#define OBSERVEDGRAPH_HPP

#include <set>
#include "Node.hpp"
#include "Edge.hpp"
#include "GraphObserver.hpp"

class ObservedGraph
{
protected:
    std::set<GraphObserver *> observers;

    virtual void notifyAdd(const Node &n);
    virtual void notifyAdd(const Edge &e);

    virtual void notifyDelete(const Edge &e);
    virtual void notifyDelete(const Node &n);

    virtual void notifyPropertyChange(const Node &n);
    virtual void notifyPropertyChange(const Edge &e);

public:
    ObservedGraph() = default;
    virtual ~ObservedGraph() = default;

    virtual void attach(GraphObserver *observer);
    virtual void detach(GraphObserver *observer);
};

#endif //OBSERVEDGRAPH_HPP
