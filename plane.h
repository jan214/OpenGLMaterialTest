#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "object.h"

class Plane : public Object{
    std::vector<uint16_t> aindices;
    std::vector<float> avertices;
    std::vector<uint16_t> anormind;
    std::vector<float> anormals;
public:
    Plane(GLuint pprogram);
};

#endif // PLANE_H
