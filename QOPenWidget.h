#ifndef QOPENWIDGET_H
#define QOPENWIDGET_H

#include <qopenglwidget.h>
#include <qopenglfunctions_3_3_compatibility>
#include <qopenglfunctions_4_3_compatibility>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <qopenglvertexarrayobject.h>
#include <qpushbutton.h>
#include <qtimer.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class QOPenWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Compatibility
{
	Q_OBJECT
public:
	QOPenWidget(QWidget *parent = 0);
	~QOPenWidget();

private:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	//加载着色器程序
	void CompileShader(unsigned int *id, const char* vertexPath, const char* fragmentPath, const char* geometryPath = NULL);

private:
	//缓存对象
	unsigned int VBO, VAO, EBO;

	//着色器程序ID
	unsigned int ID;

	//定时器
	QTimer timer;
};

#endif 