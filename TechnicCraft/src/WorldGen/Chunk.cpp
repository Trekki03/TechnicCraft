#include "WorldGen/Chunk.h"
#include <iostream>
namespace game
{
    Chunk::Chunk(game::BlockManager* manager)
    {
        vertexBufferVector = nullptr;
        vertexBuffer = nullptr;
        vao = nullptr;

        this->manager = manager;
        GenerateChunk();
        GenerateVao();
    }


    void Chunk::GenerateChunk()
    {
        for(int x = 0; x < 16; x++)
        {
            for(int y = 0; y < 256; y++)
            {
                for(int z = 0; z < 16; z++)
                {
                    if(y < 250)
                    {
                        blocks[x][y][z] = 2u;
                    }
                    else
                    {
                        blocks[x][y][z] = 1u;
                    }
                }
            }
        }
    }

    void Chunk::GenerateVao()
    {
        if(vertexBufferVector != nullptr) { delete vertexBufferVector; }
        vertexBufferVector = new std::vector<float>;

        for(int x = 0; x < 16; x++)
        {
            for(int y = 0; y < 256; y++)
            {
                for(int z = 0; z < 16; z++)
                {

                    std::vector<float>* insertionVertexVector = manager->GetBlockVertexBuffer(blocks[x][y][z]);

                    // No Block at this chunk coord
                    if(insertionVertexVector == nullptr) { continue;}

                    vertexBufferVector->push_back(insertionVertexVector->at(0) + x);
                    vertexBufferVector->push_back(insertionVertexVector->at(1) + y);
                    vertexBufferVector->push_back(insertionVertexVector->at(2) + z);
                    vertexBufferVector->insert(vertexBufferVector->end(), insertionVertexVector->begin()+3, insertionVertexVector->end());
                }
            }
        }

        if(vertexBuffer != nullptr) { delete vertexBuffer; }
        vertexBuffer = new t3d::openGl::VertexBuffer(vertexBufferVector->data(), vertexBufferVector->size() * sizeof(float), GL_STATIC_DRAW);

        if(vao != nullptr) { delete vao; }
        vao = new t3d::openGl::VertexArrayObject();
        vao->SetVertexBuffer(*vertexBuffer);
        vao->ConfigureEnableVertexAttribPointer(0, 3, GL_FLOAT, false, 9*sizeof(float), 0);
        vao->ConfigureEnableVertexAttribPointer(1, 2, GL_FLOAT, false, 9*sizeof(float), 3 * sizeof(float));
        vao->ConfigureEnableVertexAttribPointer(2, 2, GL_FLOAT, false, 9*sizeof(float), 5 * sizeof(float));
        vao->ConfigureEnableVertexAttribPointer(3, 2, GL_FLOAT, false, 9 * sizeof(float), 7 * sizeof(float));
    }

    t3d::openGl::VertexArrayObject* Chunk::GetVao()
    {
        return vao;
    }
}