#include "T3D/openGlWrapper/ShaderProgram.h"
#include "T3D/util/FileIO.h"

#include <iostream>
#include <string>

namespace t3d::openGl
{
// CONSTRUCTOR / DESTRUCTOR
    ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
    {
        std::string vertexShaderSource = t3d::util::GetStringFromFile(vertexShaderPath);
        std::string fragmentShaderSource = t3d::util::GetStringFromFile(fragmentShaderPath);

        _objectID = glCreateProgram();

        uint32_t vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        SetShaderSource(vertexShaderID, vertexShaderSource.c_str());
        CompileShader(vertexShaderID);
        AttachShader(vertexShaderID);

        uint32_t fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        SetShaderSource(fragmentShaderID, fragmentShaderSource.c_str());
        CompileShader(fragmentShaderID);
        AttachShader(fragmentShaderID);

        LinkShader();

        DeleteShader(vertexShaderID);
        DeleteShader(fragmentShaderID);
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(_objectID);
    }

// UNIFORMS:
    void ShaderProgram::SetUniform1f(const char* location, float data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniform1f(uniformLocation, data);
        }
    }

    void ShaderProgram::SetUniform2f(const char* location, glm::vec2 data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniform2f(uniformLocation, data.x, data.y);
        }
    }

    void ShaderProgram::SetUniform3f(const char* location, glm::vec3 data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniform3f(uniformLocation, data.x, data.y, data.z);
        }
    }

    void ShaderProgram::SetUniform4f(const char* location, glm::vec4 data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniform4f(uniformLocation, data.x, data.y, data.z, data.w);
        }
    }

    void ShaderProgram::SetUniform1i(const char* location, int32_t data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniform1i(uniformLocation, data);
        }
    }

    void ShaderProgram::SetUniform2i(const char* location, glm::ivec2 data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniform2i(uniformLocation, data.x, data.y);
        }
    }
    void ShaderProgram::SetUniform3i(const char* location, glm::ivec3 data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniform3i(uniformLocation, data.x, data.y, data.y);
        }
    }

    void ShaderProgram::SetUniform4i(const char* location, glm::ivec4 data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniform4i(uniformLocation, data.x, data.y, data.y, data.w);
        }
    }

    void ShaderProgram::SetUniform1ui(const char* location, uint32_t data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniform1ui(uniformLocation, data);
        }
    }

    void ShaderProgram::SetUniform2ui(const char* location, glm::uvec2 data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniform2ui(uniformLocation, data.x, data.y);
        }
    }

    void ShaderProgram::SetUniform3ui(const char* location, glm::uvec3 data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniform3ui(uniformLocation, data.x, data.y, data.z);
        }
    }

    void ShaderProgram::SetUniform4ui(const char* location, glm::uvec4 data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniform4ui(uniformLocation, data.x, data.y, data.z, data.w);
        }
    }

    void ShaderProgram::SetUniformMatrix2fv(const char* location, bool transpose, const float* data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniformMatrix2fv(uniformLocation, 1, transpose, data);
        }
    }

    void ShaderProgram::SetUniformMatrix3fv(const char* location, bool transpose, const float* data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniformMatrix3fv(uniformLocation, 1, transpose, data);
        }
    }

    void ShaderProgram::SetUniformMatrix4fv(const char* location, bool transpose, const float* data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniformMatrix4fv(uniformLocation, 1, transpose, data);
        }
    }

    void ShaderProgram::SetUniformMatrix2x3fv(const char* location, bool transpose, const float* data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniformMatrix2x3fv(uniformLocation, 1, transpose, data);
        }
    }

    void ShaderProgram::SetUniformMatrix3x2fv(const char* location, bool transpose, const float* data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniformMatrix3x2fv(uniformLocation, 1, transpose, data);
        }
    }

    void ShaderProgram::SetUniformMatrix2x4fv(const char* location, bool transpose, const float* data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniformMatrix2x4fv(uniformLocation, 1, transpose, data);
        }
    }

    void ShaderProgram::SetUniformMatrix4x2fv(const char* location, bool transpose, const float* data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniformMatrix4x2fv(uniformLocation, 1, transpose, data);
        }
    }

    void ShaderProgram::SetUniformMatrix3x4fv(const char* location, bool transpose, const float* data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniformMatrix3x4fv(uniformLocation, 1, transpose, data);
        }
    }

    void ShaderProgram::SetUniformMatrix4x3fv(const char* location, bool transpose, const float* data) const
    {
        int32_t uniformLocation = GetUniformLocation(location);
        if(uniformLocation != -1)
        {
            Bind();
            glUniformMatrix4x3fv(uniformLocation, 1, transpose, data);
        }
    }

    // PRIVATE FUNCTIONS:
    void ShaderProgram::SetShaderSource(uint32_t shaderID, const char* shaderSrcString)
    {
        glShaderSource(shaderID, 1, &shaderSrcString, nullptr);
    }

    void ShaderProgram::CompileShader(uint32_t shaderID)
    {
        glCompileShader(shaderID);
        int32_t result;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

        if(!result)
        {
            char log[512];
            glGetShaderInfoLog(shaderID, 512, nullptr, log);
            std::cerr << "[Shader Compilation Error]:\n" << log << std::endl;
        }
    }

    void ShaderProgram::AttachShader(uint32_t shaderID) const
    {
        glAttachShader(_objectID, shaderID);
    }

    void ShaderProgram::LinkShader() const
    {
        glLinkProgram(_objectID);
        int32_t result;
        glGetProgramiv(_objectID, GL_LINK_STATUS, &result);
        if(!result)
        {
            char log[512];
            glGetProgramInfoLog(_objectID, 512, nullptr, log);
            std::cerr << "[Shader Linking Error]:\n" << log << std::endl;
        }
    }

    void ShaderProgram::DeleteShader(uint32_t shaderID)
    {
        glDeleteShader(shaderID);
    }

    int32_t ShaderProgram::GetUniformLocation(const char* location) const
    {
        int32_t uniformLocation = glGetUniformLocation(_objectID, location);
        if(uniformLocation == -1)
        {
            std::cerr
                << "[Shader Uniform Error]:\n"
                << "Error while retrieving location of uniform: "
                << location << " in shader programm: "
                << _objectID
                << std::endl;
            return -1;
        }
        return uniformLocation;
    }
}
