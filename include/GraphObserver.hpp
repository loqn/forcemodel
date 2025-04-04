#ifndef GRAPHOBSERVER_HPP
#define GRAPHOBSERVER_HPP

#include "Node.hpp"
#include "Edge.hpp"


class GraphObserver {
  public:
    virtual ~GraphObserver() = default;

    virtual void treatAdd(const Node &n) = 0 ;
    virtual void treatAdd(const Edge &e) = 0;

    virtual void treatDelete(const Edge &e) = 0;
    virtual void treatDelete(const Node &n) = 0 ;

    virtual void treatPropertyChange(const Node &n) = 0 ;
    virtual void treatPropertyChange(const Edge &e) = 0 ;
};

#endif //GRAPHOBSERVER_HPP
