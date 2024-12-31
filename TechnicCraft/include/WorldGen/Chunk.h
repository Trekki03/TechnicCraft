#ifndef BLOCKBUILDINGGAME_CHUNK_H
#define BLOCKBUILDINGGAME_CHUNK_H

#include <cstdint>
#include "T3D/OpenGlWrapper/VertexArrayObject.h"
#include "Objects/BlockManager.h"

namespace game
{
    class Chunk
    {
    private:
        game::BlockManager* manager;
        uint8_t blocks[16][256][16] {};
        std::vector<float>* vertexBufferVector;
        t3d::openGl::VertexBuffer* vertexBuffer;
        t3d::openGl::VertexArrayObject* vao;

    private:
        void GenerateChunk();
        void GenerateVao();
    public:
        Chunk(game::BlockManager* manager);
        t3d::openGl::VertexArrayObject *GetVao();
    };

} // game

#endif //BLOCKBUILDINGGAME_CHUNK_H
