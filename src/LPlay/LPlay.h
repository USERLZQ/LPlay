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

    //��ʱ�� ��������ʾ
    void timerEvent(QTimerEvent *e);

    //���ڳߴ�仯
    void resizeEvent(QResizeEvent* e);


    //˫��ȫ��
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
