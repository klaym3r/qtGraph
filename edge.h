#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
    Edge();
    Edge(int, int);

    int getStart() const { return start; }
    int getEnd() const { return end; }


private:

    int start;
    int end;
};

#endif // EDGE_H
