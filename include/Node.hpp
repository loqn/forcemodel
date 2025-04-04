#ifndef NODE_H
#define NODE_H

class Node {
    public:
        Node(bool valid = true);
        ~Node() = default;
        int getID() const;
        bool operator<(const Node &other) const;
        bool operator==(const Node &other) const;
    private:
        int id;
};
#endif