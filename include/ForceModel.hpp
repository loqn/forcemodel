#ifndef FORCEMODEL_H
#define FORCEMODEL_H

#include "ValuedGraph.hpp"
#include "Coord.hpp"

class ForceModel {
  public:
    ForceModel() = delete;
    explicit ForceModel(ValuedGraph* g);
    void initDrawing(uint width, uint height);
    Coord calcAttractions(const Node &n);
    Coord calcRepulsions(const Node &n);
    Coord calcForces(const Node &n);
    void move(const Node &n, Coord moving);
    void exec();

    Coord calcGravityForce(const Node &n);

    static void* dessiner(void* vg);

  private:
    ValuedGraph * graph;
};

#endif //FORCEMODEL_H
