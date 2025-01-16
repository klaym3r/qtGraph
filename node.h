#include <QVector>

#ifndef NODE_H
#define NODE_H

class Node
{
public:
    QVector<int> friends;

    Node();
    Node(int);
    Node(int, int, int, int);

    void setX(int);
    void setY(int);
    void setNum(int);
    void setSize(double);

    int getX() const { return x; }
    int getY() const { return y; }
    int getNum() const { return num; }
    double getSize() const { return size; }

private:

    int x;
    int y;
    int num;
    double size;
};

#endif // NODE_H
