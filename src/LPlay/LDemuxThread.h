#pragma once
#include <QThread>
#include "IvideoCall.h"
#include <mutex>
class XDemux;
class LVideoThread;
class LAudioThread;
class LDemuxThread :public QThread
{
public:
	//创建对象并打开
	virtual bool Open(const char* url, IvideoCall* call);

	//启动所有线程
	virtual void Start();

	//关闭线程清理资源
	virtual void Close();
	virtual void Clear();

	virtual void Seek(double pos);

	void run();
	LDemuxThread();
	virtual ~LDemuxThread();
	bool isExit = false;
	long long pts = 0;
	long long totalMs = 0;
	void SetPause(bool isPause);
	bool isPause = false;
protected:
	std::mutex mux;
	XDemux* demux = 0;
	LVideoThread* vt = 0;
	LAudioThread* at = 0;
};

