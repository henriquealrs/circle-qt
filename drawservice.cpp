#include "drawservice.h"

using std::vector;

DrawService::DrawService(QObject *parent, int width, int height): QObject(parent)
{
    _thread = new QThread;
    _worker = new DrawExec(nullptr, width, height);
    _worker->moveToThread(_thread);

    connect(this, &DrawService::signalStartDrawing, _worker, &DrawExec::slotDrawImage);
    connect(_worker, &DrawExec::signalDrawFinished, this, [this](vector<vector<uint8_t>>& data){
        emit signalDrawingFinished(data);
    });
    connect(_thread, &QThread::finished, _worker, &QObject::deleteLater);

    _thread->start();
}

DrawService::~DrawService()
{
    _thread->quit();
    _thread->wait();
}


#include <QDebug>
void DrawService::slotDrawShape(std::shared_ptr<Shape> &obj)
{
    qDebug() << "Service thread id " << QThread::currentThreadId() << "\n";
    emit signalStartDrawing(obj);
}
