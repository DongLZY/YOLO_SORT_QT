#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->startButton, &QPushButton::pressed,this, &Widget::slotStart);
    connect(ui->stopButton, &QPushButton::pressed,this, &Widget::slotStop);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotStart(){
    videoThread = new Cthread_video();

    videoThread -> start();
    qDebug()<<"开启拍摄线程！";
    connect(videoThread,&Cthread_video::sendOriImg, this,&Widget::showImg);
    ui->startButton -> setEnabled(false);
    ui->stopButton -> setEnabled(true);
}

void Widget::slotStop(){

    videoThread -> closeCamera();

    videoThread -> quit();
    videoThread -> wait();
    delete videoThread;
    ui->startButton -> setEnabled(true);
    ui->stopButton -> setEnabled(false);
    qDebug() << "退出并清除拍摄线程!";

}

void Widget::showImg(QImage tempImg){
    oriImg=tempImg;
    ui->label1->setAlignment(Qt::AlignCenter);
    ui->label1->setScaledContents(true);
    ui->label1->setPixmap(QPixmap::fromImage(oriImg));
}
