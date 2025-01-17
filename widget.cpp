#include <QPainter>
#include <QPainterPath>
#include <QFile>

#include "widget.h"
#include "node.h"
#include "edge.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{}

Widget::~Widget() {}

void Widget::paintNode(const Node &node) {

    nodes_.push_back(node);
    update();
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font = painter.font();
    font.setPointSize(nodes_[0].getSize() / 2);
    painter.setFont(font);

    for (const auto &edge : edges_) {

        int start = edge.getStart();
        int end = edge.getEnd();
        int s = nodes_[start].getSize();

        if (start == end) {
            int x = nodes_[start].getX();
            int y = nodes_[start].getY() - s * 1.2;
            if (nodes_.size() % 2 == 0) {
                if (start == 0)
                    painter.drawEllipse(x + s * 0.8, y + s * 1.2, s * 1.5, s);
                else if (start == nodes_.size() / 2)
                    painter.drawEllipse(x - s * 1.2, y + s * 1.2, s * 1.5, s);
                else if (start > nodes_.size() / 2)
                    painter.drawEllipse(x, y, s, s * 1.5);
                else
                    painter.drawEllipse(x, y + s * 2, s, s * 1.5);
            }
            else {
                if (start > nodes_.size() / 2)
                    painter.drawEllipse(x, y, s, s * 1.5);
                else
                    painter.drawEllipse(x, y + s * 2, s, s * 1.5);
            }
        }
        else {
            int x1 = nodes_[start].getX() + s / 2;
            int y1 = nodes_[start].getY() + s / 2;

            int x2 = nodes_[end].getX() + s / 2;
            int y2 = nodes_[end].getY() + s / 2;

            painter.drawLine(x1, y1, x2, y2);
        }
    }

    for (const auto &node : nodes_) {

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

bool fillViaFile(Widget &w) {

  QFile file("/home/klaymer/qtGraph/data.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Cannot open file:" << file.errorString();
    return false;
  }

  QTextStream in(&file);
  for (int i = 0; !in.atEnd(); ++i) {
    QString line = in.readLine();
    Node n;
    try {
      n.setNum(i);
    } catch (char const *error_message) {
      qDebug() << error_message;
      return false;
    }
    w.nodes_.push_back(n);
    for (QChar ch : line) {
      if (ch.isDigit()) {
        Edge e{i, ch.digitValue()};
        w.edges_.push_back(e);
      }
    }
  }
  file.close();
  return true;
}

bool setNodes(Widget &w, const int &wx, const int &wy) {

    int s = w.nodes_.size();

    for (int i = 0; i < s; ++i) {
        double angle = 2 * M_PI * i / s;
    try {
      w.nodes_[i].setSize(wx * 0.08);
    } catch (char const *error_message) {
      qDebug() << error_message;
      return false;
    }
    w.nodes_[i].setX(wx / 2.0 + wx * 0.2 * cos(angle) - w.nodes_[i].getSize() / 2.0);
    w.nodes_[i].setY(wx / 2.0 + wy * 0.2 * sin(angle) - w.nodes_[i].getSize() / 2.0);
  }
  return true;
}
