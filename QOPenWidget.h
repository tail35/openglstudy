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

	//������ɫ������
	void CompileShader(unsigned int *id, const char* vertexPath, const char* fragmentPath, const char* geometryPath = NULL);

private:
	//�������
	unsigned int VBO, VAO, EBO;

	//��ɫ������ID
	unsigned int ID;

	//��ʱ��
	QTimer timer;
};

#endif 