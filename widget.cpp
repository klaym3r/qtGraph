#include <QPainter>
#include <QPainterPath>

#include "widget.h"
#include "node.h"
#include "edge.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{}

Widget::~Widget() {}

void Widget::paintNode(const Node &node) {

    nodes.push_back(node);
    update();
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font = painter.font();
    font.setPointSize(nodes[0].getSize() / 2);
    painter.setFont(font);

    for (const auto &edge : edges) {

        int start = edge.getStart();
        int end = edge.getEnd();
        int s = nodes[start].getSize();

        if (start == end) {
            int x = nodes[start].getX();
            int y = nodes[start].getY() - s * 1.2;
            if (nodes.size() % 2 == 0) {
                if (start == 0)
                    painter.drawEllipse(x + s * 0.8, y + s * 1.2, s * 1.5, s);
                else if (start == nodes.size() / 2)
                    painter.drawEllipse(x - s * 1.2, y + s * 1.2, s * 1.5, s);
                else if (start > nodes.size() / 2)
                    painter.drawEllipse(x, y, s, s * 1.5);
                else
                    painter.drawEllipse(x, y + s * 2, s, s * 1.5);
            }
            else {
                if (start > nodes.size() / 2)
                    painter.drawEllipse(x, y, s, s * 1.5);
                else
                    painter.drawEllipse(x, y + s * 2, s, s * 1.5);
            }
        }
        else {
            int x1 = nodes[start].getX() + s / 2;
            int y1 = nodes[start].getY() + s / 2;

            int x2 = nodes[end].getX() + s / 2;
            int y2 = nodes[end].getY() + s / 2;

            painter.drawLine(x1, y1, x2, y2);
        }
    }

    for (const auto &node : nodes) {

        int x = node.getX();
        int y = node.getY();
        int s = node.getSize();

        int centerX = x + s / 2;
        int centerY = y + s / 2;

        painter.setBrush(QBrush(Qt::white));
        painter.drawEllipse(x, y, s, s);
        QString numberText = QString::number(node.getNum());
        QRect textRect(centerX - 15, centerY - 15, 30, 30);
        painter.drawText(textRect, Qt::AlignCenter, numberText);
    }
    painter.end();
}
