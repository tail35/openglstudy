#include "QOPenWidget.h"
#include <iostream>
#include <qtimer.h>
#include<ctime>
#include <string.h>


QOPenWidget::QOPenWidget(QWidget *parent) :QOpenGLWidget(parent)
{
	setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);

	connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
	timer.start(0);
}
QOPenWidget::~QOPenWidget()
{

}

void QOPenWidget::initializeGL()
{
	initializeOpenGLFunctions();				//��ʼ��
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);					//������Ȼ���

	//�����ɫ��
	CompileShader(&ID, "texture.vs", "texture.fs");

	float vertices[] = {
		// λ��              // ��ɫ
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//��VAO
	glBindVertexArray(VAO);

	//��VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//�Ѷ������鸴�Ƶ�VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//�����VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//�����EBO
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//�����VAO
	glBindVertexArray(0);

}



void QOPenWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}


void QOPenWidget::paintGL()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//������ɫ��
	glUseProgram(ID);
	//�󶨶��㻺�����
	glBindVertexArray(VAO);
	//��ʼ����
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//�����
	glBindVertexArray(0);
}


//������ɫ������
void QOPenWidget::CompileShader(unsigned int *id, const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;


	// ���ļ�
	vShaderFile.open(vertexPath);
	fShaderFile.open(fragmentPath);
	std::stringstream vShaderStream, fShaderStream;
	// ��ȡ�ļ��Ļ������ݵ���������
	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();
	// �ر��ļ�������
	vShaderFile.close();
	fShaderFile.close();
	// ת����������string
	vertexCode = vShaderStream.str();
	fragmentCode = fShaderStream.str();

	if (geometryPath != NULL)
	{
		gShaderFile.open(geometryPath);
		std::stringstream gShaderStream;
		gShaderStream << gShaderFile.rdbuf();
		gShaderFile.close();
		geometryCode = gShaderStream.str();
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// 2. ������ɫ��
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// ������ɫ��
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	//������ɫ��
	glCompileShader(vertex);
	//������ʱ����
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	//����������������
	if (!success)
	{
		//��ȡ������Ϣ
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		//��ӡ����
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//ƬԪ��ɫ��
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//������
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		//��ȡ����ԭ��
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		//��ӡ
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//������ɫ��
	unsigned int geometry;
	if (geometryPath != nullptr)
	{
		const char * gShaderCode = geometryCode.c_str();
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);
	}


	// ��ɫ������
	*id = glCreateProgram();
	glAttachShader(*id, vertex);
	glAttachShader(*id, fragment);
	if (geometryPath != nullptr)
		glAttachShader(*id, geometry);
	glLinkProgram(*id);
	//������
	glGetProgramiv(*id, GL_LINK_STATUS, &success);
	if (!success)
	{
		//��ȡ������Ϣ
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geometryPath != nullptr)
		glDeleteShader(geometry);
}