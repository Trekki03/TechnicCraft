#include "Objects/BlockManager.h"
#include <vector>

namespace game
{

    BlockManager::~BlockManager()
    {
        for(auto& [key, value] : vbs)
        {
            delete value;
        }
    }

    std::vector<float>* BlockManager::GetBlockVertexBuffer(uint8_t blockID)
    {
        // If no block
        if(blockID == 0)
        {
            return nullptr;
        }

        //if already created
        if(vbs.contains(blockID))
        {
            return vbs.at(blockID);
        }

        //if new
        auto* vertices = new std::vector<float>;
        float position[3] = { 0.0f, 0.0f, 0.0f };
        AddDataFromArrayIntoVector(vertices, position, 0, 3);
        vertices->push_back(blockAtlas.getTopTexPos(blockID)[0]);
        vertices->push_back(blockAtlas.getTopTexPos(blockID)[1]);
        vertices->push_back(blockAtlas.getBottomTexPos(blockID)[0]);
        vertices->push_back(blockAtlas.getBottomTexPos(blockID)[1]);
        vertices->push_back(blockAtlas.getSideTexPos(blockID)[0]);
        vertices->push_back(blockAtlas.getSideTexPos(blockID)[1]);

        vbs.insert({ blockID, vertices});
        return vertices;
    }

    template<typename T>
    void BlockManager::AddDataFromArrayIntoVector(std::vector<T>*vector, T * array, int start, int number)
    {
        for (int i = start; i < start + number; i++)
        {
            vector->push_back(array[i]);
        }
    }
}