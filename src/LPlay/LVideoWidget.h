#pragma once

#include <mutex>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLShaderProgram>
#include "IvideoCall.h"
struct AVFrame;

class LVideoWidget : public QOpenGLWidget, protected QOpenGLFunctions, public IvideoCall
{
	Q_OBJECT

public:
	virtual void Init(int width, int height);

	//���ܳɹ�����ͷ�frame�ռ�
	virtual void Repaint(AVFrame *frame);

	LVideoWidget(QWidget* parent);
	~LVideoWidget();

protected:
	//ˢ����ʾ
	void paintGL();
	//��ʼ��GL
	void initializeGL();
	//���ڳߴ�仯
	void resizeGL(int width, int height);

private:
	std::mutex mux;

	//shader����
	QGLShaderProgram  program;

	//shader�е�yuv������ַ
	GLuint unis[3] = { 0 };
	//opengl��texture��ַ
	GLuint texs[3] = { 0 };

	//�����ڴ�ռ�
	unsigned char* datas[3] = { 0 };

	int width = 240;
	int height = 128;
};
