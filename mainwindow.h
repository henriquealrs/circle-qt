#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>
#include <memory>
#include "inputvalidator.h"

class DrawService;
class Shape;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void invalidInput();

private slots:
    void on_btn_add_clicked();

    void on_pushButton_clicked();

signals:
    void createCircle(QString x, QString y, QString r);
    void signalNewObjectAdded(std::shared_ptr<Shape>& obj);
    void signalStop();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPixmap image;
    InputValidator *iv;
    DrawService *draw_service;
};
#endif // MAINWINDOW_H
