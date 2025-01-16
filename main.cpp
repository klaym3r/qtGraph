#include "widget.h"

#include <cmath>

#include <QApplication>
#include <QFile>
#include <QString>
#include <QVector>

bool FillViaFile(QVector<Node> &, QVector<Edge> &);
bool setNodes(QVector<Node> &, const int &, const int &, const int &);

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  Widget w;
  int wx = 500;
  int wy = 500;
  w.setFixedSize(wx, wy);

  if (!FillViaFile(w.nodes, w.edges) ||
      !setNodes(w.nodes, wx, wy, w.nodes.size()))
    return 1;

  w.update();
  w.show();
  return a.exec();
}

bool setNodes(QVector<Node> &nodes, const int &wx, const int &wy,
              const int &count) {
  for (int i = 0; i < count; ++i) {
    double angle = 2 * M_PI * i / count;
    try {
      nodes[i].setSize(wx * 0.08);
    } catch (char const *error_message) {
      qDebug() << error_message;
      return false;
    }
    nodes[i].setX(wx / 2.0 + wx * 0.2 * cos(angle) - nodes[i].getSize() / 2.0);
    nodes[i].setY(wx / 2.0 + wy * 0.2 * sin(angle) - nodes[i].getSize() / 2.0);
  }
  return true;
}

bool FillViaFile(QVector<Node> &node, QVector<Edge> &edge) {

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
    node.push_back(n);
    for (QChar ch : line) {
      if (ch.isDigit()) {
        Edge e{i, ch.digitValue()};
        edge.push_back(e);
      }
    }
  }
  file.close();
  return true;
}
