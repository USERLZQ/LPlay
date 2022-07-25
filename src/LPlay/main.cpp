#include "LPlay.h"
#include <QtWidgets/QApplication>
#include "XDemux.h"
#include "XDecode.h"
#include "LVideoWidget.h"
#include "LResample.h"
#include "LAudioPlay.h"
#include <iostream>
#include <QThread>
#include "LAudioThread.h"
#include "LVideoThread.h"
#include "LDemuxThread.h"
using namespace std;

class TestThread :public QThread
{
public:
    LAudioThread at;
    LVideoThread vt;
    void Init()
    {
        cout << "demux.Open: " << demux.Open("video.mp4") << std::endl;
        /*cout << "demux.CopyAPara: " << demux.CopyAPara() << std::endl;
        cout << "demux.CopyVPara: " << demux.CopyVPara() << std::endl;
        cout << "demux.Seek: " << demux.Seek(0.5) << std::endl;*/

        //-----------------------------½âÂë²âÊÔ
        
        //cout << "Vdecode.Open: " << Vdecode.Open(demux.CopyVPara()) << endl;
        //cout << "Adecode.Open: " << Adecode.Open(demux.CopyAPara()) << endl;
        //cout << "resample.Open: " << resample.Open(demux.CopyAPara()) << endl;
        //LAudioPlay::Get()->channels = demux.channels;
        //LAudioPlay::Get()->sampleRate = demux.sampleRate;
        //cout << "LAudioPlay::Get()->Open(): " << LAudioPlay::Get()->Open() << endl;
        cout << "--------at.Open: " << at.Open(demux.CopyAPara(), demux.sampleRate, demux.channels) << endl;
        cout << "--------vt.Open: " << vt.Open(demux.CopyVPara(), video, demux.width, demux.height) << endl;
        at.start();
        vt.start();
    }
    unsigned char* pcm = new unsigned char[1024 * 1024];
    void run()
    {
        for (;;)
        {
        AVPacket* pkt = demux.Read();
        if (demux.IsAudio(pkt))
        {
            at.Push(pkt);
            /*Adecode.Send(pkt);
            AVFrame* frame = Adecode.Recv();
            int len = resample.Resample(frame, pcm);
            cout << "resample.Resample: " << resample.Resample(frame, pcm) << endl;
            
            while (len >= 0)
            {
                if (LAudioPlay::Get()->GetFree() >= len)
                {
                    LAudioPlay::Get()->Write(pcm, len);
                    break;
                }
                msleep(10);
            }*/
            //cout << "Audio: " << frame << endl;
            
        }
        else
        {
            vt.Push(pkt);
            /*Vdecode.Send(pkt);
            AVFrame* frame = Vdecode.Recv();
            video->Repaint(frame);
            cout << "video: " << frame << endl;*/
        }
        if (!pkt)
            break;
        }
    }
    XDemux demux;
    XDecode Vdecode;
    //XDecode Adecode;
    LVideoWidget *video = 0;
    //LResample resample;
};

int main(int argc, char *argv[])
{
    const char* url = "video.mp4";
    //XDemux demux;
    //XDecode Vdecode;
    //XDecode Adecode;
    //cout << "demux.Open: " << demux.Open("video.mp4") << std::endl;
    //cout << "demux.CopyAPara: " << demux.CopyAPara() << std::endl;
    //cout << "demux.CopyVPara: " << demux.CopyVPara() << std::endl;
    //cout << "demux.Seek: " << demux.Seek(0.99) << std::endl;

    ////-----------------------------½âÂë²âÊÔ

    //cout << "Vdecode.Open: " << Vdecode.Open(demux.CopyVPara()) << endl;
    //cout << "Adecode.Open: " << Adecode.Open(demux.CopyAPara()) << endl;

    //for (;;)
    //{
    //    AVPacket* pkt = demux.Read();
    //    if (demux.IsAudio(pkt))
    //    {
    //        /*Adecode.Send(pkt);
    //        AVFrame* frame = Adecode.Recv();
    //        cout << "Audio: " << frame << endl;*/
    //    }
    //    else
    //    {
    //        Vdecode.Send(pkt);
    //        AVFrame* frame = Vdecode.Recv();
    //        cout << "video: " << frame << endl;
    //    }
    //    if (!pkt)
    //        break;
    //}
    //TestThread tt;

    QApplication a(argc, argv);
    LPlay w;
    w.show();

    //³õÊ¼»¯gl´°¿Ú
    //w.ui.video->Init(tt.demux.width, tt.demux.height);
    //tt.video = w.ui.video;
    //tt.Init();
    //tt.start();
    //LDemuxThread dt;
    //dt.Open(url, w.ui.video);
    //dt.Start();

    return a.exec();
}
