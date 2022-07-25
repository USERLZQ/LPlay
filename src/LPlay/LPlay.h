#pragma once

#include <QtWidgets/QWidget>
#include "ui_LPlay.h"
#include <QTimer>

class LPlay : public QWidget
{
    Q_OBJECT

public:
    LPlay(QWidget *parent = nullptr);
    ~LPlay();

    //定时器 滑动条显示
    void timerEvent(QTimerEvent *e);

    //窗口尺寸变化
    void resizeEvent(QResizeEvent* e);


    //双击全屏
    void mouseDoubleClickEvent(QMouseEvent* e);

    void SetPause(bool isPause);

public slots:
    void OpenFile();
    void CloseFile();
    void PlayOrPause();
    void SliderPress();
    void SliderRelease();

private:
    Ui::LPlayClass ui;
    bool isSliderPress = false;
};
