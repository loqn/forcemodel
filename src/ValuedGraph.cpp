#include "ValuedGraph.hpp"

#include <string>
#include <fstream>
#include <vector>
#include "utils.hpp"

bool ValuedGraph::charger(std::string fichier)
{
  std::cout << "Loading graph..." << std::endl;
  std::map<int, Node> idSommet;

  std::ifstream in(fichier.c_str());
  if (!in.is_open()) {
    std::cout << "Could not open file: " << fichier << std::endl;
    return false;
  }

  std::string ligne;
  std::getline(in, ligne);

  int nodeCount = 0;
  while (std::getline(in, ligne)) {
    if (ligne.empty()) continue;

    if (ligne == "#aretes") {
      std::cout << "Found edge section marker" << std::endl;
      break;
    }

    std::vector<std::string> items;
    decouper(ligne, items, ";");

    if (items.size() < 4) {
      std::cout << "Skipping invalid node line: " << ligne << std::endl;
      continue;
    }

    int id = std::stoi(items[0]);
    if (idSommet.find(id) != idSommet.end()) {
      std::cout << "Skipping duplicate node ID: " << id << std::endl;
      continue;
    }

    Node n = addNode();
    notifyAdd(n);
    idSommet[id] = n;
    nodeCount++;

    std::vector<std::string> posItems;
    decouper(items[1], posItems, " ");
    if (posItems.size() >= 2) {
      float x = std::stof(posItems[0]);
      float y = std::stof(posItems[1]);
      positionSommet(n, Coord(x, y));
    }

    std::vector<std::string> colorItems;
    decouper(items[2], colorItems, " ");
    if (colorItems.size() >= 4) {
      int r = std::stoi(colorItems[0]);
      int g = std::stoi(colorItems[1]);
      int b = std::stoi(colorItems[2]);
      int a = std::stoi(colorItems[3]);
      couleurSommet(n, Color(r, g, b, a));
    }

    etiquetteSommet(n, items[3]);
  }
  std::cout << "Loaded " << nodeCount << " nodes" << std::endl;

  int edgeCount = 0;
  while (std::getline(in, ligne)) {
    if (ligne.empty()) continue;

    std::vector<std::string> items;
    decouper(ligne, items, " ");

    if (items.size() < 2) {
      std::cout << "Skipping invalid edge line: " << ligne << std::endl;
      continue;
    }

    int id1 = std::stoi(items[0]);
    int id2 = std::stoi(items[1]);

    if (idSommet.find(id1) == idSommet.end() || idSommet.find(id2) == idSommet.end()) {
      std::cout << "Skipping edge with unknown node IDs: " << id1 << " -> " << id2 << std::endl;
      continue;
    }

    Node n1 = idSommet[id1];
    Node n2 = idSommet[id2];
    const Edge& e = addEdge(n1, n2);
    notifyAdd(e);
    edgeCount++;
    couleurArete(e, Color(0,0,0,255));
    setEdgeLabel(e, "");
  }

  std::cout << "Loaded " << edgeCount << " edges" << std::endl;
  std::cout << "Final graph state: " << getNodes().size() << " nodes, "
            << getEdges().size() << " edges" << std::endl;
  return true;
}

void ValuedGraph::positionSommet(Node n, Coord c) {
  positions.change(n,c);
  notifyPropertyChange(n);
}

Coord ValuedGraph::positionSommet(Node n) const {
  return positions.value(n);
}

void ValuedGraph::positionsMinMax(Coord &min, Coord &max) {
  if (getNodes().empty()) {
    min = Coord(0, 0);
    max = Coord(0, 0);
    return;
  }

  Node firstNode = *getNodes().begin();
  min = positionSommet(firstNode);
  max = min;

  for (const Node &n : getNodes()) {
    if (n.getID() == firstNode.getID()) {
      continue;
    }
    Coord pos = positionSommet(n);

    min.setX(std::min(min.getX(), pos.getX()));
    min.setY(std::min(min.getY(), pos.getY()));
    max.setX(std::max(max.getX(), pos.getX()));
    max.setY(std::max(max.getY(), pos.getY()));
  }

  std::cout << "Fin positionsMinMax: min=(" << min.getX() << "," << min.getY()
            << "), max=(" << max.getX() << "," << max.getY() << ")" << std::endl;
}

void ValuedGraph::couleurSommet(Node n, Color c) {
  colors.change(n,c);
  notifyPropertyChange(n);
}

Color ValuedGraph::couleurSommet(Node n) {
  return colors.value(n);
}

void ValuedGraph::couleurArete(Edge e, Color c) {
  colors.change(e,c);
  notifyPropertyChange(e);
}

Color ValuedGraph::couleurArete(Edge e) {
  return colors.value(e);
}

void ValuedGraph::etiquetteSommet(Node n, std::string label) {
  labels.change(n, label);
  notifyPropertyChange(n);
}

std::string ValuedGraph::etiquetteSommet(Node n) const {
  return labels.value(n);
}

void ValuedGraph::setEdgeLabel(Edge e, std::string label) {
  labels.change(e, label);
  notifyPropertyChange(e);
}

std::string ValuedGraph::getEdgeLabel(Edge e) const {
  return labels.value(e);
}

Property<Color> ValuedGraph::getColorsProperties() {
  return colors;
}

Property<Coord> ValuedGraph::getPositionsProperties() {
  return positions;
}

Property<std::string> ValuedGraph::getLabelsProperties() {
  return labels;
}