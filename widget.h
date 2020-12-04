#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "cthread_video.h"
#include <iostream>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void showImg(QImage tempImg);

private:
    Ui::Widget *ui;
    void slotStart();
    void slotStop();
    void initThread();

    Cthread_video *videoThread;
    QImage oriImg;
};

#endif // WIDGET_H
