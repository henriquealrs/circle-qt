#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "drawservice.h"

#include <iostream>
#include <QThread>

using std::vector;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto viewSize = this->ui->graphicsView->sizeHint();
    scene = new QGraphicsScene(0, 0, viewSize.width(), viewSize.height(), this);

    scene->addPixmap(this->image);

    this->ui->graphicsView->setScene(scene);

    iv = new InputValidator(this);

    connect(this, &MainWindow::createCircle, iv, &InputValidator::ValidateCircleInput);
    connect(iv, &InputValidator::invalidInput, this, &MainWindow::invalidInput);


    draw_service = new DrawService(this, scene->width(), scene->height());
    connect(draw_service, &DrawService::signalDrawingFinished, this, [this](vector<vector<uint8_t>>& data){
        const int width = data[0].size();
        const int height = data.size();
        vector<uint8_t> pixels(data[0].size() * data.size());
        for(int i = 0; i < height; ++i) {
            auto& row = data[i];
            for(int j = 0; j < width; ++j) {
                pixels[i*width + j] = row[j];
            }
        }

        QImage qimg( pixels.data(), width, height, QImage::Format_Grayscale8 );
        auto pixmap = QPixmap::fromImage(qimg);
        scene->addPixmap(pixmap);
    });
    connect(iv, &InputValidator::draw, draw_service, &DrawService::slotDrawShape);

    qDebug() << "Init thread id " << QThread::currentThreadId() << "\n";

    connect(this, &MainWindow::signalStop, draw_service, &DrawService::slotStopDrawExecutor);
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete draw_service;
}

void MainWindow::invalidInput()
{
    QString err = "<span style=\" font-size:8pt; font-weight:600; color:#aa0000;\"> Invlid input </span>";
    this->ui->lbl_err->setText(err);
}




void MainWindow::on_btn_add_clicked()
{
    this->ui->lbl_err->setText("");
    QString sxc = this->ui->e_xc->text();
    QString syc = this->ui->e_yc->text();
    QString sr = this->ui->e_r->text();

    qDebug() << "OnClick thread id " << QThread::currentThreadId() << "\n";


    emit createCircle(sxc, syc, sr);

   //std::cout <<  this->image.load("myimage2.jpeg") << std::endl;;
   //scene->addPixmap(this->image);
}




void MainWindow::on_pushButton_clicked()
{
    emit signalStop();
}

