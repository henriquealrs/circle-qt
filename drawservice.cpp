#include "drawservice.h"
#include <QDebug>
using std::vector;

DrawService::DrawService(QObject *parent, int width, int height): QObject(parent)
{
    _thread = new QThread(this);
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
    qDebug() << "Destroying draw service\n";
    _thread->quit();
    _thread->wait();
    //delete _thread;
}


#include <QDebug>
void DrawService::slotDrawShape(std::shared_ptr<Shape> &obj)
{
    qDebug() << "Service thread id " << QThread::currentThreadId() << "\n";
    emit signalStartDrawing(obj);
}

void DrawService::slotStopDrawExecutor()
{
    _thread->quit();
    _thread->wait();
}
