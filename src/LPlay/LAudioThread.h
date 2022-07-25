#pragma once
#include <QThread>
#include <mutex>
#include <list>
struct AVCodecParameters;
class LAudioPlay;
class LResample;
#include "LDecodeThread.h"
class LAudioThread :public LDecodeThread
{
public:
	//��ǰ��Ƶ���ŵ�pts
	long long pts = 0;
	//�򿪣����ܳɹ��������
	virtual bool Open(AVCodecParameters* para, int sampleRate, int channels);

	//ֹͣ�̣߳�������Դ
	virtual void Close();


	virtual void Clear();
	void run();
	LAudioThread();
	virtual ~LAudioThread();
	void SetPause(bool isPause);

	bool isPause = false;
protected:
	std::mutex amux;
	LAudioPlay* ap = 0;
	LResample* res = 0;

};