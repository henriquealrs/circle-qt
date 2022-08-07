#ifndef DRAWEXEC_H
#define DRAWEXEC_H

#include <QObject>
#include <stdint.h>
#include <QThread>
#include <vector>
#include "shape.h"
#include <memory>

class DrawExec : public QObject
{
    Q_OBJECT
private:
    vec2d _size;
    std::vector<std::vector<uint8_t>> _data;

public:
    DrawExec() = delete;
    explicit DrawExec(QObject *parent, int width, int height);

signals:
    void signalDrawFinished(std::vector<std::vector<uint8_t>>& data);

public slots:
    void slotDrawImage(std::shared_ptr<Shape> &shape);
};

#endif // DRAWEXEC_H
