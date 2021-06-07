#include "plane.h"

Plane::Plane(GLuint pprogram) : Object(){
    /*
    A predefined Plane
    derives from Object for setup and draw function
    */
    program = pprogram;

    aindices = {
        0,1,2,0,2,3
    };

    anormind = {
        0,0,0,
        0,0,0
    };

    avertices = {
        -0.5f,-0.5f,-1.0f,
        -0.5f,0.5f,0.0f,
        0.5f,0.5f,0.0f,
        0.5f,-0.5f,-1.0f
    };

    anormals = {
        0.0f,1.0f,1.0f,
        0.0f,1.0f,0.0f
    };

    for(int i = 0; i < aindices.size(); i++){
        for(int j = 0; j < 3; j++){
            array.push_back(avertices[aindices[i]*3+j]);
            normals.push_back(anormals[anormind[i]*3+j]);
        }
    }
}
