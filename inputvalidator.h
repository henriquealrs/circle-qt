#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <QObject>
#include <QString>
#include <memory>
#include <shape.h>

class InputValidator : public QObject
{
    Q_OBJECT
public slots:
    void ValidateCircleInput(QString x, QString y, QString r);
public:
    InputValidator() = delete;
    InputValidator(QObject *parent);
    ~InputValidator();

signals:
    void invalidInput();
    void draw(std::shared_ptr<Shape>& obj);
};

#endif // INPUTVALIDATOR_H
