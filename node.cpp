#include "node.h"

Node::Node() {}
Node::Node(int num) : num_(num) {}
Node::Node(int x, int y, int num, double size) : x_(x), y_(y), num_(num), size_(size) {}


void Node::setX(int x) {
    x_ = x;
}
void Node::setY(int y) {
    y_ = y;
}
void Node::setNum(int num) {
    if (num >= 0) {
        num_ = num;
    }
    else {
        throw "Num can be only > 0";
    }
}
void Node::setSize(double size) {
    if (size >= 0) {
        size_ = size;
    }
    else {
        throw "Size can be only > 0";
    }
}
