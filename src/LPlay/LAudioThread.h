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
	//当前音频播放的pts
	long long pts = 0;
	//打开，不管成功与否都清理
	virtual bool Open(AVCodecParameters* para, int sampleRate, int channels);

	//停止线程，清理资源
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