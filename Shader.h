#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h> // 包含glew来获取所有的必须OpenGL头文件
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h> // 包含glew来获取所有的必须OpenGL头文件

class Shader {
public:
    // 程序ID
    GLuint ID;
    // 构造器读取并构建着色器
    Shader() {};
    void Compile(const GLchar* vertexPath, const GLchar* fragmentPath
        , const GLchar* geometryPath = nullptr);
    // 使用程序
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
