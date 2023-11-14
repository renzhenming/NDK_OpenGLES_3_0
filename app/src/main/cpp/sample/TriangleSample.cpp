//
// Created by ByteFlow on 2019/7/9.
//

#include "TriangleSample.h"
#include "../util/GLUtils.h"
#include "../util/LogUtil.h"

TriangleSample::TriangleSample()
{

}

TriangleSample::~TriangleSample()
{
}


void TriangleSample::LoadImage(NativeImage *pImage)
{
	//null implement

}

void TriangleSample::Init()
{
	if(m_ProgramObj != 0)
		return;
	char vShaderStr[] =
			"#version 300 es                          \n"
			"layout(location = 0) in vec4 vPosition;  \n"
			"void main()                              \n"
			"{                                        \n"
			"   gl_Position = vPosition;              \n"
			"}                                        \n";

	char fShaderStr[] =
			"#version 300 es                              \n"
			"precision mediump float;                     \n"
			"out vec4 fragColor;                          \n"
			"void main()                                  \n"
			"{                                            \n"
			"   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
			"}                                            \n";

	m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);

}

void TriangleSample::Draw(int screenW, int screenH)
{
	LOGCATE("TriangleSample::Draw");
	GLfloat vVertices[] = {
			0.0f,  0.5f, 0.0f,
			-1.0f, -0.5f, 0.0f,
			1.0f, -0.5f, 0.0f,
	};

	if(m_ProgramObj == 0)
		return;

	glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Use the program object
	glUseProgram (m_ProgramObj);

	// Load the vertex data
	//将当前的顶点属性与顶点缓冲对象（VBO）关联起来
	//index 指定要配置的顶点属性的编号。
	//size 指定每个顶点属性的分量数（1、2、3 或 4，就像向量的维度一样）。
	//type 指定每个分量的数据类型，可以是 GL_BYTE、GL_UNSIGNED_BYTE、GL_SHORT、GL_UNSIGNED_SHORT、GL_INT、GL_UNSIGNED_INT、GL_FLOAT 或 GL_DOUBLE。
	//normalized1 指定是否将数据归一化到 [0,1] 或 [-1,1] 范围内。
	//stride （步长）指定连续两个顶点属性间的字节数。如果为 0，则表示顶点属性是紧密排列的。
	//pointer 指向缓冲对象中第一个顶点属性的第一个分量的地址。（offset的作用）
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
	glEnableVertexAttribArray (0);

	glDrawArrays (GL_TRIANGLES, 0, 3);
	glUseProgram (GL_NONE);

}

void TriangleSample::Destroy()
{
	if (m_ProgramObj)
	{
		glDeleteProgram(m_ProgramObj);
		m_ProgramObj = GL_NONE;
	}

}
