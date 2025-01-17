#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>

#include "node.h"
#include "edge.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QVector<Node> getNodes() { return nodes_; }
    QVector<Edge> getEdges() { return edges_; }

    void paintCenter(const int, const int);
    void paintNode(const Node &);
    void paintEdge(const Node &, const Node &);

    friend bool fillViaFile(Widget &);
    friend bool setNodes(Widget &, const int &wx, const int &wy);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<Node> nodes_;
    QVector<Edge> edges_;

};
#endif // WIDGET_H
