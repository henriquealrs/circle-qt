#include "drawexec.h"
#include <QDebug>

using std::vector;
DrawExec::DrawExec(QObject *parent, int width, int height) : QObject(parent), _size(width, height)
{
    for(int i = 0; i < height; ++i) {
        _data.push_back(vector<uint8_t>(width, 255));
    }
    qDebug() << "_data {" << _data.size() << ", " << _data[0].size() << "}\n";
}

void DrawExec::slotDrawImage(std::shared_ptr<Shape> &shape)
{
    qDebug() << "Exec thread id " << QThread::currentThreadId() << "\n";
    auto pix = shape->get_points(100);
    for(auto& p : pix) {
        _data[p.y][p.x] = 0;
    }
    emit signalDrawFinished(_data);
}
