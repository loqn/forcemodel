#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>

class Node;
class Edge;

class Graph {
  public:
    //const & dest
    Graph() = default;
    virtual ~Graph();

    Node addNode();

    const Edge& addEdge(const Node &n1, const Node &n2);
    void deleteNode(const Node &n);
    void deleteEdge(const Edge &e);
    const std::set<Node> &getNodes() const;
    const std::set<Edge> &getEdges() const;
    std::set<Node> getNeighborOf(const Node &n);
    Node getSourceOf(const Edge &e) const;
    Node getDestinationOf(const Edge &e) const;
    int degreeOf(const Node &n) const;
    virtual bool charger(std::string fichier);
    int nbNodes() const;
    int nbEdges() const;

  private:
    std::set<Node> nodes;
    std::set<Edge> edges;
};

#endif
