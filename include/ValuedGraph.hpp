#ifndef GRAPHVALUE_H
#define GRAPHVALUE_H

#include <ObservedGraph.hpp>
#include "Graph.hpp"
#include "Color.hpp"
#include "Coord.hpp"
#include "Property.hpp"
#include <string>
class Node;
class Edge;

class ValuedGraph : public Graph, public ObservedGraph{
  public:
    ~ValuedGraph() override = default;
    bool charger(std::string fichier) override ;
    void positionSommet(Node n, Coord c) ;
    Coord positionSommet(Node n) const ;
    void positionsMinMax(Coord &min, Coord &max) ;
    void couleurSommet(Node n, Color c) ;
    Color couleurSommet(Node n) ;
    void couleurArete(Edge e, Color c) ;
    Color couleurArete(Edge e) ;
    void etiquetteSommet(Node n, std::string label);
    std::string etiquetteSommet(Node n) const;
    void setEdgeLabel(Edge e, std::string label);
    std::string getEdgeLabel(Edge e) const;

    Property<Color> getColorsProperties();
    Property<Coord> getPositionsProperties();
    Property<std::string> getLabelsProperties();

  private:
    Property<Color> colors;
    Property<Coord> positions;
    Property<std::string> labels;
};
#endif
