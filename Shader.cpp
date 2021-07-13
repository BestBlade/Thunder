#include "Shader.h"

void Shader::Compile(const GLchar* vertexSource, const GLchar* fragmentSource
    , const GLchar* geometryPath) {
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    //  geometry Shader
    GLuint gShader;
    if (geometryPath != nullptr) {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometryPath, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    // shader Program
    this->ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if (geometryPath != nullptr) {
        glAttachShader(ID, gShader);
    }
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryPath != nullptr) {
        glDeleteShader(gShader);
    }
}

Shader& Shader::Use() {
    glUseProgram(this->ID);
    return *this;
}

void Shader::setBool(const GLchar* name, GLboolean value, GLboolean useShader) {
    if (useShader) {
        this->Use();
    }
    glUniform1i(glGetUniformLocation(this->ID, name), (int)value);
}
void Shader::setInt(const GLchar* name, GLint value, GLboolean useShader) {
    if (useShader) {
        this->Use();
    }
    glUniform1i(glGetUniformLocation(this->ID, name), (int)value);
};
void Shader::setFloat(const GLchar* name, GLfloat value, GLboolean useShader){
    if (useShader) {
        this->Use();
    }
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void Shader::setVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader){
    if (useShader) {
        this->Use();
    }
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void Shader::setVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader){
    if (useShader) {
        this->Use();
    }
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void Shader::setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader){
    if (useShader) {
        this->Use();
    }
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void Shader::setVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader){
    if (useShader) {
        this->Use();
    }
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
void Shader::setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader){
    if (useShader) {
        this->Use();
    }
    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void Shader::setVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader){
    if (useShader) {
        this->Use();
    }
    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}
void Shader::setMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader){
    if (useShader) {
        this->Use();
    }
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(GLuint shader, std::string type){
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}