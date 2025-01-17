#ifndef NODE_H
#define NODE_H

#include <QVector>


class Node
{
public:
    Node();
    Node(int num);
    Node(int x, int y, int num, double size);

    void setX(int);
    void setY(int);
    void setNum(int);
    void setSize(double);

    int getX() const { return x_; }
    int getY() const { return y_; }
    int getNum() const { return num_; }
    double getSize() const { return size_; }

private:

    int x_;
    int y_;
    int num_;
    double size_;
};

#endif // NODE_H
