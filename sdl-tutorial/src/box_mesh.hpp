#pragma once

#include <glm/vec4.hpp>

#include <vector>

namespace vertex_data
{

const float BOX_SIZE = 10.f;

const glm::vec4 COLOR_0(0.14f, 0.44f, 0.85f, 1.f);
const glm::vec4 COLOR_1(0.72f, 0.29f, 0.f, 1.f);
const glm::vec4 COLOR_2(0.95f, 0.61f, 0.07f, 1.f);
const glm::vec4 COLOR_3(0.68f, 0.47f, 0.77f, 1.f);
const glm::vec4 COLOR_4(0.32f, 0.74f, 0.5f, 1.f);
const glm::vec4 COLOR_5(1.f, 0.34f, 0.2f, 1.f);

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

    COLOR_0,
    COLOR_0,
    COLOR_0,
    COLOR_0,
    COLOR_0,
    COLOR_0,

    COLOR_1,
    COLOR_1,
    COLOR_1,
    COLOR_1,
    COLOR_1,
    COLOR_1,

    COLOR_2,
    COLOR_2,
    COLOR_2,
    COLOR_2,
    COLOR_2,
    COLOR_2,

    COLOR_3,
    COLOR_3,
    COLOR_3,
    COLOR_3,
    COLOR_3,
    COLOR_3,

    COLOR_4,
    COLOR_4,
    COLOR_4,
    COLOR_4,
    COLOR_4,
    COLOR_4,

    COLOR_5,
    COLOR_5,
    COLOR_5,
    COLOR_5,
    COLOR_5,
    COLOR_5,
};

/**
* Half of box are vertices and half are colors.
*/

const size_t VERTICES_COUNT = box.size() / 2;

}  // namespace vertex_data
