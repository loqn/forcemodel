#include "ForceModel.hpp"

#include <chrono>
#include <cmath>
#include <thread>

static const int IDEAL = 150;
static const int MAX_ATTRACTIVE = 30;
static const int MAX_DEPLACEMENT = 20;
static const int ITER = 500;

ForceModel::ForceModel(ValuedGraph *g) : graph(g) {}

void ForceModel::initDrawing(uint width, uint height) {
    for (const Node &n : graph->getNodes()) {
        float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/width));
        float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/height));
        graph->positionSommet(n, Coord(x,y));
    }
}

Coord ForceModel::calcAttractions(const Node &n) {
    Coord res;
    for (const Node &v : graph->getNeighborOf(n)) {
        Coord uPos = graph->getPositionsProperties().value(n);
        Coord vPos = graph->getPositionsProperties().value(v);

        Coord vector = vPos - uPos;
        double dist = uPos.distanceFrom(vPos);

        res+= vector * (dist/pow(IDEAL,2));
    }
    if (res.norm() > MAX_ATTRACTIVE) {
        res /= res.norm();
        res *= MAX_ATTRACTIVE;
    }
    return res;
}

Coord ForceModel::calcRepulsions(const Node &n) {
    Coord res;

    const int MAX_DIST = 5 * IDEAL;

    for (const Node &v: graph->getNodes()) {
        if (v == n) {
            continue;
        }
        Coord uPos = graph->getPositionsProperties().value(n);
        Coord vPos = graph->getPositionsProperties().value(v);

        Coord vector = vPos-uPos;
        double dist = uPos.distanceFrom(vPos);

        if (dist >= MAX_DIST) continue;

        if (dist < 0.00001) {
            dist = 0.00001;
        }
        res += vector * (-1.0 * pow(IDEAL, 2) / pow(dist, 2));
    }

    if (res.norm() > MAX_ATTRACTIVE) {
        res /= res.norm();
        res *= MAX_ATTRACTIVE;
    }
    return res;
}

Coord ForceModel::calcForces(const Node &n) {
    return calcAttractions(n) + calcRepulsions(n) + calcGravityForce(n);
}

void ForceModel::move(const Node &n, Coord moving) {
    Coord pos = graph->getPositionsProperties().value(n);
    if (moving.norm() > MAX_DEPLACEMENT) {
        moving /= moving.norm();
        moving *= MAX_DEPLACEMENT;
    }
    pos+= moving;
    graph->positionSommet(n, pos);
}

void ForceModel::exec() {
    float coolingFactor = 1.0;
    for (int i = 0; i < ITER; ++i) {
        for (const Node &n : graph->getNodes()) {
            Coord force = calcForces(n);
            force *= coolingFactor;
            move(n, force);
        }
        coolingFactor = 1.0 - (i / (double)ITER) * 0.7;

        if (i%20 == 0) {
        }
    }
}

Coord ForceModel::calcGravityForce(const Node &n) {
    Coord bary(0,0);
    int nbNodes=  0;
    for (const Node &v: graph->getNodes()) {
        bary+= graph->getPositionsProperties().value(v);
        ++nbNodes;
    }
    if (nbNodes>0) {
        bary/=static_cast<float>(nbNodes);
    }

    Coord vector = bary - graph->getPositionsProperties().value(n);
    return vector*0.05;
}

void *ForceModel::dessiner(void *vg) {
    std::cout << "ForceModel draw" << std::endl;
    auto *g = static_cast<ValuedGraph*>(vg);

    ForceModel f(g);
    f.initDrawing(1200,800);
    f.exec();
    pthread_exit(nullptr);
}




