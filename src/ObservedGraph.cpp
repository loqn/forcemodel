#include "ObservedGraph.hpp"

void ObservedGraph::notifyAdd(const Node &n) {
    for (auto &o : observers) {
        o->treatAdd(n);
    }
}

void ObservedGraph::notifyAdd(const Edge &e) {
    for (auto &o : observers) {
        o->treatAdd(e);
    }
}

void ObservedGraph::notifyDelete(const Node &n) {
    for (auto &o : observers) {
        o->treatDelete(n);
    }
}

void ObservedGraph::notifyDelete(const Edge &e) {
    for (auto &o : observers) {
        o->treatDelete(e);
    }
}

void ObservedGraph::notifyPropertyChange(const Node &n) {
    for (auto &o : observers) {
        o->treatPropertyChange(n);
    }
}

void ObservedGraph::notifyPropertyChange(const Edge &e) {
    for (auto &o : observers) {
        o->treatPropertyChange(e);
    }
}

void ObservedGraph::attach(GraphObserver *observer) {
    observers.insert(observer);
}

void ObservedGraph::detach(GraphObserver *observer) {
    observers.erase(observer);
}



