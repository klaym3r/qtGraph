#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QVector>

#include "node.h"
#include "edge.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QVector<Node> getNodes() { return nodes; }

    void paintCenter(const int, const int);
    void paintNode(const Node &);
    void paintEdge(const Node &, const Node &);

    QVector<Node> nodes;
    QVector<Edge> edges;
protected:
    void paintEvent(QPaintEvent *event) override;

};
#endif // WIDGET_H
