#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

extern int windowsize[];
extern GLint windowxsize, windowysize;

class Object{
public:
    Object(std::vector<uint16_t> pindices,std::vector<float> pvertices,std::vector<uint16_t> pnormind, std::vector<float> pnormals, GLuint &pprogram);
    Object();
    ~Object();

    void setup();
    void draw(float ptranslate[3],float protation[3]);
    void translate(std::vector<float> ptranslation);
private:
    std::vector<uint16_t> indices;
    std::vector<float> vertices;
    std::vector<uint16_t> normind;
    float tmatrix[4][4];
    float rmatrix[4][4];
    GLuint indicesBuffer, vertexBuffer, normalBuffer;
    GLint locPosition, locNormals, locTranslation;
    GLint tMatrix,yrotationmatrix;
    std::vector<float> translation;

public:
    GLuint program;
    std::vector<float> normals;
    std::vector<float> array;
};

#endif // OBJECT_H
