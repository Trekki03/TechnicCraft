#include "openGlWrapperFixture.h"
#include "T3D/openGlWrapper/ShaderProgram.hpp"

TEST_F(T3D_OpenGlWrapperTest, ShaderBinding)
{
    using namespace T3D::OpenGl;

    ShaderProgram shader("res/shader/VertexShader.vert", "res/shader/FragmentShader.frag");

    int32_t shaderProgramID = static_cast<int32_t>(shader.GetObjectId());
    int32_t activeShaderProgramID;

    shader.Bind();
    glGetIntegerv(GL_CURRENT_PROGRAM, &activeShaderProgramID);
    EXPECT_EQ(shaderProgramID, activeShaderProgramID);

    shader.Unbind();
    glGetIntegerv(GL_CURRENT_PROGRAM, &activeShaderProgramID);
    EXPECT_NE(shaderProgramID, activeShaderProgramID);
}