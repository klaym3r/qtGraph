#include "node.h"

Node::Node() {}
Node::Node(int num) : num(num) {}
Node::Node(int x, int y, int num, int size) : x(x), y(y), num(num), size(size) {}


void Node::setX(int p_x) {
    x = p_x;
}
void Node::setY(int p_y) {
    y = p_y;
}
void Node::setNum(int p_num) {
    if (p_num >= 0) {
        num = p_num;
    }
    else {
        throw "Num can be only > 0";
    }
}
void Node::setSize(double p_size) {
    if (p_size >= 0) {
        size = p_size;
    }
    else {
        throw "Size can be only > 0";
    }
}
