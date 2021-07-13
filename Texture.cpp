#include "Texture.h"
void Texture2D::Bind() const{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

Texture2D::Texture2D() {
	glGenTextures(1, &this->ID);
	Width = 0;
	Height = 0;
	Internal_Format = GL_RGB;
	//	图像色彩空间
	Image_Format = GL_RGB;
	//	重复模式
	Wrap_S = GL_REPEAT;
	Wrap_T = GL_REPEAT;
	//	放大缩小插值算法
	Filter_Min = GL_LINEAR;
	Filter_Max = GL_LINEAR;
}

void Texture2D::Generate(GLuint w, GLuint h, unsigned char* data) {
	this->Width = w;
	this->Height = h;
	//	绑定贴图和生成贴图
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, w, h, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
	//	设置重复模式和插值算法
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

	glBindTexture(GL_TEXTURE_2D, 0);
}