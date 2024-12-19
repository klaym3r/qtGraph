#include <QApplication>
#include <QtWidgets>
#include <QFile>

using namespace std;

class Node {

public:

    Node(qreal p_x, qreal p_y, QString p_label) {
        x = p_x;
        y = p_y;
        label = p_label;
    }

    void paint(QGraphicsScene* scene) {
        scene->addEllipse(x, y, size, size, QPen(Qt::black), QBrush(Qt::NoBrush));
        QGraphicsTextItem* text = scene->addText(label, QFont("Source Code Pro", 15));
        text->setDefaultTextColor(Qt::black);
        text->setPos(x + 14 / 2.0, y + 2 / 2.0);
    }

    void setX(qreal x) {
        this->x = x;
    }

    void setY(qreal y) {
        this->y = y;
    }

    void setLabel(QString label) {
        this->label = label;
    }

    qreal getX() {
        return x;
    }

    qreal getY() {
        return y;
    }

    qreal getSize() {
        return size;
    }

private:
    qreal x;
    qreal y;
    qreal size{35};
    QString label;
};

class Edge {

public:

    Edge(Node node1) {
        x1 = node1.getX();
        y1 = node1.getY();
        size1 = node1.getSize();
    }

    Edge(Node node1, Node node2) : Edge(node1) {
        x2 = node2.getX();
        y2 = node2.getY();
        size2 = node2.getSize();
    }

    void paint(QGraphicsScene* scene) {
        x1 = x1 + size1 / 2.0;
        y1 = y1 + size1 / 2.0;
        x2 = x2 + size2 / 2.0;
        y2 = y2 + size2 / 2.0;
        scene->addLine(x1, y1, x2, y2, QPen(Qt::green, 3));
    }

    void paintLoop(QGraphicsScene* scene) {
        scene->addEllipse(x1 + size1 * 0.15, y1 + size1, size1 * 0.7, size1, QPen(Qt::green, 3), QBrush(Qt::NoBrush));
    }

private:
    qreal x1;
    qreal y1;
    qreal x2;
    qreal y2;
    qreal size1;
    qreal size2;
};

void paintNodes(QGraphicsScene*, vector<Node>&, const int);
void paintEdges(QGraphicsScene*, vector<Node>, QMap<int, QVector<int>>, const int);

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // проверка работы с файлами
    // QMap<int, QVector<int>> new_graph;
    // QFile file("data.txt");

    // for (int i = 0; !file.atEnd(); ++i) {
    //     qDebug() << i;
    // }
    // file.close();

    // код работает с этим вектором
    QMap<int, QVector<int>> graph;
    graph[0] = {2};
    graph[1] = {1, 3, 4};
    graph[2] = {2, 4};
    graph[3] = {2, 3};
    graph[4] = {5};

    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(-450, -450, 450, 450);

    QGraphicsView* view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);

    const int g_size = graph.size();
    vector<Node> node;

    paintNodes(scene, node, g_size);
    paintEdges(scene, node, graph, g_size);


    view->show();
    return a.exec();
}

void paintNodes(QGraphicsScene *scene, vector<Node>& node, const int g_size) {

    int count{};
    if (g_size % 2 == 0) {
        for (int i = 0; i < g_size / 2; ++i) {
            for (int j = 0; j < g_size / 2; ++j) {
                Node tmp_node{static_cast<qreal>(-400 + 125 * j), static_cast<qreal>(-400 + 125 * i), QString::number(count + 1)};
                node.push_back(tmp_node);
                node[count].paint(scene);
                count++;
            }
        }
    }
    else {

        for (int i = 0; i <= (g_size / 2); ++i) {
            if (i == (g_size / 2)) {
                Node tmp_node{-400, static_cast<qreal>(-400 + 125 * i), QString::number(count + 1)};
                node.push_back(tmp_node);
                node[count].paint(scene);
                count++;
            }
            else {
                for (int j = 0; j < g_size / 2; ++j) {
                    Node tmp_node{static_cast<qreal>(-400 + 125 * j), static_cast<qreal>(-400 + 125 * i), QString::number(count + 1)};
                    node.push_back(tmp_node);
                    node[count].paint(scene);
                    count++;
                }
            }
        }
    }
}

void paintEdges(QGraphicsScene *scene, vector<Node> node, QMap<int, QVector<int>> graph, const int g_size) {


    for (int i = 0; i < g_size; ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            if (i == (graph[i][j] - 1)) {
                Edge edge{node[i]};
                edge.paintLoop(scene);
            }
            else {
                Edge edge{node[i], node[graph[i][j] - 1]};
                edge.paint(scene);
            }
        }
    }
}
