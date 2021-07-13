#include "Texture.h"
void Texture2D::Bind() const{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

Texture2D::Texture2D() {
	glGenTextures(1, &this->ID);
	Width = 0;
	Height = 0;
	Internal_Format = GL_RGB;
	//	ͼ��ɫ�ʿռ�
	Image_Format = GL_RGB;
	//	�ظ�ģʽ
	Wrap_S = GL_REPEAT;
	Wrap_T = GL_REPEAT;
	//	�Ŵ���С��ֵ�㷨
	Filter_Min = GL_LINEAR;
	Filter_Max = GL_LINEAR;
}

void Texture2D::Generate(GLuint w, GLuint h, unsigned char* data) {
	this->Width = w;
	this->Height = h;
	//	����ͼ��������ͼ
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, w, h, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
	//	�����ظ�ģʽ�Ͳ�ֵ�㷨
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

	glBindTexture(GL_TEXTURE_2D, 0);
}