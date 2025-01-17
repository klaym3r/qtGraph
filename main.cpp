#include "widget.h"

#include <cmath>

#include <QApplication>
#include <QString>
#include <QVector>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  Widget w;
  int wx = 500;
  int wy = 500;
  w.setFixedSize(wx, wy);

  if (!fillViaFile(w) ||
      !setNodes(w, wx, wy))
    return -1;

  w.update();
  w.show();
  return a.exec();
}
