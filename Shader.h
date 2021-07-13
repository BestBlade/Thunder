#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h> // ����glew����ȡ���еı���OpenGLͷ�ļ�
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h> // ����glew����ȡ���еı���OpenGLͷ�ļ�

class Shader {
public:
    // ����ID
    GLuint ID;
    // ��������ȡ��������ɫ��
    Shader() {};
    void Compile(const GLchar* vertexPath, const GLchar* fragmentPath
        , const GLchar* geometryPath = nullptr);
    // ʹ�ó���
    Shader& Use();

    void setBool(const GLchar* name, GLboolean value, GLboolean useShader = false);
    void setInt(const GLchar* name, GLint value, GLboolean useShader = false);
    void setFloat(const GLchar* name, GLfloat value, GLboolean useShader = false);
    void setVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void setVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader = false);
    void setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void setVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader = false);
    void setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void setVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader = false);
    void setMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader = false);

private:
    void checkCompileErrors(GLuint shader, std::string type);
};
