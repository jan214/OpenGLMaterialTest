#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "object.h"


class Cube: public Object{
    std::vector<uint16_t> aindices;
    std::vector<float> avertices;
    std::vector<uint16_t> anormind;
    std::vector<float> anormals;

public:
    Cube(GLuint pprogram);
};

#endif // CUBE_H
