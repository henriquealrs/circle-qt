#ifndef DRAWSERVICE_H
#define DRAWSERVICE_H

#include <QThread>
#include <memory>
#include "drawexec.h"
#include "shape.h"
#include <vector>

class DrawService : public QObject
{
    Q_OBJECT
private:
    QThread *_thread;
    DrawExec *_worker;
public:
    DrawService() = delete;
    explicit DrawService(QObject *parent, int width, int height);
    ~DrawService();
public slots:
    void slotDrawShape(std::shared_ptr<Shape>& obj);
    void slotStopDrawExecutor();
signals:
    void signalStartDrawing(std::shared_ptr<Shape>& obj);
    void signalDrawingFinished(std::vector<std::vector<uint8_t>>& data);
};

#endif // DRAWSERVICE_H
