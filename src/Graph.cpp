#include "Graph.hpp"

#include "Node.hpp"
#include "Edge.hpp"
#include <set>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include "utils.hpp"

Node Graph::addNode() {
  return *this->nodes.insert(Node()).first;
}

Graph::~Graph() {
  edges.clear();
  nodes.clear();
}

const Edge& Graph::addEdge(const Node &n1, const Node &n2) {
  return *this->edges.insert(Edge(n1, n2)).first;
}

void Graph::deleteNode(const Node &n) {
  auto it = this->edges.begin();
  while (it != this->edges.end()) {
    if (it->getStart() == n || it->getEnd() == n) {
      it = this->edges.erase(it);
    } else {
      ++it;
    }
  }

  this->nodes.erase(n);
}

void Graph::deleteEdge(const Edge &e) {
  this->edges.erase(e);
}

const std::set<Node> &Graph::getNodes() const {
  return this->nodes;
}

const std::set<Edge> &Graph::getEdges() const {
  return this->edges;
}

std::set<Node> Graph::getNeighborOf(const Node &n) {
  std::set<Node> neighbors;

  for (const Edge &e: this->edges) {
    if (e.getStart() == n) {
      neighbors.insert(e.getEnd());
    }
    if (e.getEnd() == n) {
      neighbors.insert(e.getStart());
    }
  }
  return neighbors;
}

Node Graph::getSourceOf(const Edge &e) const {
  return e.getStart();
}

Node Graph::getDestinationOf(const Edge &e) const {
  return e.getEnd();
}

int Graph::degreeOf(const Node &n) const {
  int degree = 0;
  for (const Edge &e: this->edges) {
    if (e.getStart() == n) {
      ++degree;
    }
    if (e.getEnd() == n) {
      ++degree;
    }

    if (e.getStart() == n && e.getEnd() == n) {
      --degree;
    }
  }
  return degree;
}

bool Graph::charger(std::string fichier)
{
  std::map<int, Node> idSommet;

  bool sommetsFinis = false;
  std::ifstream in(fichier.c_str());
  while (!in.eof())
  {
    char ligne[10000];
    in.getline(ligne, 10000);
    std::string lignes(ligne);
    lignes = lignes.substr(0, lignes.size()-1);
    if (lignes == "#sommets"){
      continue;
    }
    else if (lignes == "#aretes")
    {
      sommetsFinis = true;
    }
    else if (!sommetsFinis)
    {
      int id = stoi(lignes);
      if (idSommet.find(id) != idSommet.end())
        return false;
      Node n = addNode();
      idSommet[id] = n;
    }
    else if (sommetsFinis && lignes != "")
    {
      std::vector<std::string> items;
      decouper(lignes, items, " ");
      if (items.size() != 2)
        return false;

      int id1 = stoi(items[0]);
      int id2 = stoi(items[1]);

      if (idSommet.find(id1) == idSommet.end() || idSommet.find(id2) == idSommet.end())
        return false;
      Node n1 = idSommet[id1];
      Node n2 = idSommet[id2];
      addEdge(n1, n2);
    }
  }
  return true;
}

int Graph::nbNodes() const {
  return this->nodes.size();
}

int Graph::nbEdges() const {
  return this->edges.size();
}