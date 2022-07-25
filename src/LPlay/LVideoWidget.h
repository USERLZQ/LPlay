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

	//不管成功与否都释放frame空间
	virtual void Repaint(AVFrame *frame);

	LVideoWidget(QWidget* parent);
	~LVideoWidget();

protected:
	//刷新显示
	void paintGL();
	//初始化GL
	void initializeGL();
	//窗口尺寸变化
	void resizeGL(int width, int height);

private:
	std::mutex mux;

	//shader程序
	QGLShaderProgram  program;

	//shader中的yuv变量地址
	GLuint unis[3] = { 0 };
	//opengl的texture地址
	GLuint texs[3] = { 0 };

	//材质内存空间
	unsigned char* datas[3] = { 0 };

	int width = 240;
	int height = 128;
};
