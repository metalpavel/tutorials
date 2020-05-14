#pragma once

#include <glm/vec4.hpp>

#include <vector>

namespace vertex_data
{

const float BOX_SIZE = 10.f;

const glm::vec4 TEX_COORD_0_1(0.f, 0.f, 1.f, 0.f);
const glm::vec4 TEX_COORD_2_0(1.f, 1.f, 0.f, 0.f);
const glm::vec4 TEX_COORD_2_3(1.f, 1.f, 0.f, 1.f);

const std::vector<glm::vec4> box
{
    { -BOX_SIZE, -BOX_SIZE, BOX_SIZE, 1.f },
    { BOX_SIZE, -BOX_SIZE, BOX_SIZE, 1.f },
    { BOX_SIZE, BOX_SIZE, BOX_SIZE, 1.f },
    { -BOX_SIZE, -BOX_SIZE, BOX_SIZE, 1.f },
    { BOX_SIZE, BOX_SIZE, BOX_SIZE, 1.f },
    { -BOX_SIZE, BOX_SIZE, BOX_SIZE, 1.f },
    
    { -BOX_SIZE, BOX_SIZE, -BOX_SIZE, 1.f },
    { BOX_SIZE, BOX_SIZE, -BOX_SIZE, 1.f },
    { BOX_SIZE, -BOX_SIZE, -BOX_SIZE, 1.f },
    { -BOX_SIZE, BOX_SIZE, -BOX_SIZE, 1.f },
    { BOX_SIZE, -BOX_SIZE, -BOX_SIZE, 1.f },
    { -BOX_SIZE, -BOX_SIZE, -BOX_SIZE, 1.f },

    { -BOX_SIZE, -BOX_SIZE, -BOX_SIZE, 1.f },
    { BOX_SIZE, -BOX_SIZE, -BOX_SIZE, 1.f },
    { BOX_SIZE, -BOX_SIZE, BOX_SIZE, 1.f },
    { -BOX_SIZE, -BOX_SIZE, -BOX_SIZE, 1.f },
    { BOX_SIZE, -BOX_SIZE, BOX_SIZE, 1.f },
    { -BOX_SIZE, -BOX_SIZE, BOX_SIZE, 1.f },
    
    { -BOX_SIZE, BOX_SIZE, BOX_SIZE, 1.f },
    { BOX_SIZE, BOX_SIZE, BOX_SIZE, 1.f },
    { BOX_SIZE, BOX_SIZE, -BOX_SIZE, 1.f },
    { -BOX_SIZE, BOX_SIZE, BOX_SIZE, 1.f },
    { BOX_SIZE, BOX_SIZE, -BOX_SIZE, 1.f },
    { -BOX_SIZE, BOX_SIZE, -BOX_SIZE, 1.f },

    { -BOX_SIZE, -BOX_SIZE, BOX_SIZE, 1.f },
    { -BOX_SIZE, BOX_SIZE, BOX_SIZE, 1.f },
    { -BOX_SIZE, BOX_SIZE, -BOX_SIZE, 1.f },
    { -BOX_SIZE, -BOX_SIZE, BOX_SIZE, 1.f },
    { -BOX_SIZE, BOX_SIZE, -BOX_SIZE, 1.f },
    { -BOX_SIZE, -BOX_SIZE, -BOX_SIZE, 1.f },

    { BOX_SIZE, -BOX_SIZE, -BOX_SIZE, 1.f },
    { BOX_SIZE, BOX_SIZE, -BOX_SIZE, 1.f },
    { BOX_SIZE, BOX_SIZE, BOX_SIZE, 1.f },
    { BOX_SIZE, -BOX_SIZE, -BOX_SIZE, 1.f },
    { BOX_SIZE, BOX_SIZE, BOX_SIZE, 1.f },
    { BOX_SIZE, -BOX_SIZE, BOX_SIZE, 1.f },

    TEX_COORD_0_1,
    TEX_COORD_2_0,
    TEX_COORD_2_3,

    TEX_COORD_0_1,
    TEX_COORD_2_0,
    TEX_COORD_2_3,

    TEX_COORD_0_1,
    TEX_COORD_2_0,
    TEX_COORD_2_3,

    TEX_COORD_0_1,
    TEX_COORD_2_0,
    TEX_COORD_2_3,

    TEX_COORD_0_1,
    TEX_COORD_2_0,
    TEX_COORD_2_3,

    TEX_COORD_0_1,
    TEX_COORD_2_0,
    TEX_COORD_2_3,
};

const size_t VERTICES_COUNT = 36;

}  // namespace vertex_data
