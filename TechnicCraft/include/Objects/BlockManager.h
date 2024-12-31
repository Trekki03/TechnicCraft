
#ifndef BLOCKBUILDINGGAME_BLOCKMANAGER_H
#define BLOCKBUILDINGGAME_BLOCKMANAGER_H

#include <map>
#include <cstdint>
#include <vector>
#include "T3D/OpenGlWrapper/VertexArrayObject.h"
#include "T3D/OpenGlWrapper/VertexBuffer.h"
#include "T3D/OpenGlWrapper/indexBuffer.h"
#include "BlockAtlas.h"
#include <glm/glm.hpp>

namespace game
{

    class BlockManager
    {
    private:
        game::world::object::BlockAtlas blockAtlas;
        std::map<uint32_t, std::vector<float>*> vbs;
    
    private:
        template<typename T>
        void AddDataFromArrayIntoVector(std::vector<T>* vector, T* array, int start, int number);

    public:
        BlockManager() = default;
        ~BlockManager();

        std::vector<float>* GetBlockVertexBuffer(uint8_t blockID);
    };

} // game

#endif //BLOCKBUILDINGGAME_BLOCKMANAGER_H
