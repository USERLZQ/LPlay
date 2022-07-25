#include "LPlay.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include "LDemuxThread.h"
#include <QMessageBox>

static LDemuxThread dt;

LPlay::LPlay(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    dt.Start();
    startTimer(40);
}

void LPlay::SliderPress()
{
    isSliderPress = true;
}

void LPlay::SliderRelease()
{
    isSliderPress = false;
    double pos = 0.0;
    pos = (double)ui.playPos->value() / (double)ui.playPos->maximum();
    dt.Seek(pos);
}

void LPlay::OpenFile()
{
    //选择文件
    QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择视频文件"));
    if (name.isEmpty()) return;
    this->setWindowTitle(name);
    
    if (!dt.Open(name.toLocal8Bit(), ui.video))
    {
        QMessageBox::information(this, "error", "open file failed");
    }
    else
    {
        //ui.openFile->hide();
    }
    SetPause(dt.isPause);
}

//定时器 滑动条显示
void LPlay::timerEvent(QTimerEvent* e)
{
    if (isSliderPress) return;
    long long total = dt.totalMs;
    if (total > 0)
    {
        double pos = (double)dt.pts / (double)dt.totalMs;
        int v = ui.playPos->maximum() * pos;
        ui.playPos->setValue(v);
    }
}

void LPlay::SetPause(bool isPause)
{
    if (isPause)
    {
        ui.isPlay->setText(QString::fromLocal8Bit("播放"));
    }
    else
    {
        ui.isPlay->setText(QString::fromLocal8Bit("暂停"));
    }
}

//窗口尺寸变化
void LPlay::resizeEvent(QResizeEvent* e)
{
    ui.playPos->move(50, this->height() - 50);
    ui.playPos->resize(this->width() - 100, ui.playPos->height());
    
    ui.openFile->move(100, this->height() - 150);
    ui.isPlay->move(ui.openFile->x() + ui.openFile->width() + 20, ui.openFile->y());
    ui.video->resize(this->size());
}

void LPlay::mouseDoubleClickEvent(QMouseEvent* e)
{
    if (isFullScreen())
        this->showNormal();
    else this->showFullScreen();
}

void LPlay::PlayOrPause()
{
    bool isPause = !dt.isPause;
    SetPause(isPause);
    dt.SetPause(isPause);
}

void LPlay::CloseFile()
{
    
}

LPlay::~LPlay()
{
    dt.Close();

}
