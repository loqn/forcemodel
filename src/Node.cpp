#include "Node.hpp"

using namespace std;

static int lastId = 0;

Node::Node(bool valid) {
    if (valid) {
        this->id = ++lastId;
    } else {this->id = -1;}
}

bool Node::operator<(const Node &other) const {
  return this->id < other.getID();
}

bool Node::operator==(const Node &other) const {
  return this->id == other.id;
}

int Node::getID() const {
	return this->id;
}



