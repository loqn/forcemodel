#include "Edge.hpp"

using namespace std;

Edge::Edge(Node start, Node end) {
    this->start = start;
    this->end = end;
    // std::cout << "Construction d'une arête : " << start.getID() << " -> " << end.getID() << std::endl;
}

Edge::~Edge() {
    // std::cout << "Destruction d'une arête : " << start.getID() << " -> " << end.getID() << std::endl;
}

Edge::Edge(const Edge& other) {
    this->start = other.start;
    this->end = other.end;
}

Edge& Edge::operator=(const Edge& other) {
    if (this != &other) {
        this->start = other.start;
        this->end = other.end;
    }
    return *this;
}

bool Edge::operator<(const Edge &other) const {
    // std::cout << "[<] this->start ID: " << this->getStart().getID() << std::endl;
    // std::cout << "[<] this->end ID: " << this->getEnd().getID() << std::endl;
    // std::cout << "[<] other->start ID: " << other.getStart().getID() << std::endl;
    // std::cout << "[<] other->end ID: " << other.getEnd().getID() << std::endl;

    int startId = this->start.getID();
    int otherStartId = other.start.getID();

    if (startId == otherStartId) {
        return this->end.getID() < other.end.getID();
    }
    return startId < otherStartId;
}


Node Edge::getStart() const {
	return this->start;
}

Node Edge::getEnd() const {
	return this->end;
}
