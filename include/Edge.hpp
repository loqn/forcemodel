#ifndef EDGE_H
#define EDGE_H

#include "Node.hpp"

class Edge {
  public:
    Edge(Node start, Node end);
    Edge(const Edge& other);
    Edge& operator=(const Edge& other);
    ~Edge();
    Node getStart() const;
    Node getEnd() const;
    bool operator<(const Edge &other) const;

  private:
    Node start;
    Node end;
};
#endif
