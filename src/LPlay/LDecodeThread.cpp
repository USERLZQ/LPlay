#include "LDecodeThread.h"
#include "XDecode.h"
//������Դ��ֹͣ�߳�
void LDecodeThread::Close()
{
	Clear();

	//�ȴ��߳��˳�
	isExit = true;
	wait();
	decode->Close();

	mux.lock();
	delete decode;
	decode = NULL;
	mux.unlock();
}
void LDecodeThread::Clear()
{
	mux.lock();
	decode->Clear();
	while (!packs.empty())
	{
		AVPacket* pkt = packs.front();
		XFreePacket(&pkt);
		packs.pop_front();
	}

	mux.unlock();
}


//ȡ��һ֡���ݣ�����ջ�����û�з���NULL
AVPacket* LDecodeThread::Pop()
{
	mux.lock();
	if (packs.empty())
	{
		mux.unlock();
		return NULL;
	}
	AVPacket* pkt = packs.front();
	packs.pop_front();
	mux.unlock();
	return pkt;
}
void LDecodeThread::Push(AVPacket* pkt)
{
	if (!pkt)return;
	//����
	while (!isExit)
	{
		mux.lock();
		if (packs.size() < maxList)
		{
			packs.push_back(pkt);
			mux.unlock();
			break;
		}
		mux.unlock();
		msleep(1);
	}
}


LDecodeThread::LDecodeThread()
{
	//�򿪽�����
	if (!decode) decode = new XDecode();
}


LDecodeThread::~LDecodeThread()
{	//�ȴ��߳��˳�
	isExit = true;
	wait();
}
