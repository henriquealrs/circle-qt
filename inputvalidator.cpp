#include "inputvalidator.h"

#include "circle.h"

#include <string>
#include <sstream>
#include <memory>

#include <QThread>
#include <QDebug>

using std::string;
using std::stringstream;
using std::shared_ptr;
using std::make_shared;


static bool isValidFloat( string s, float &f )
{
   char junk;
   stringstream ss( s );
   return ( ss >> f && !(ss >> junk) );
}


void InputValidator::ValidateCircleInput(QString x, QString y, QString r)
{
    float fx, fy, fr;
    bool res = true;

    res &= isValidFloat(x.toStdString(), fx);
    res &= isValidFloat(y.toStdString(), fy);
    res &= isValidFloat(r.toStdString(), fr);

    if(!res) {
        emit invalidInput();
        return;
    }
    auto c =  vec2d((int) fx, (int) fy);
    auto circle =  shared_ptr<Shape>(new Circle(c, int(fr)));

    qDebug() << "Validator thread id " << QThread::currentThreadId() << "\n";
    emit draw(circle);
}

InputValidator::InputValidator(QObject *parent) : QObject(parent)
{

}
