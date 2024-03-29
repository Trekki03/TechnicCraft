#pragma once
#include "OpenGlObject.h"
#include <cstdint>

namespace t3d::openGl
{
    /**
     *  Base class for OpenGL textures.
     *  It defines pure virtual functions for functionality existing in all texture types
     */
    class Texture : public OpenGlObject
    {
        /**
         * Sets the slot of a texture for use in shaders.
         * @param textureSlot
         */
        virtual void SetTextureSlot(uint32_t textureSlot) const = 0;

        /**
         * Generates Mipmaps of the texture
         */
        virtual void GenerateMipmaps() const = 0;
    };
}