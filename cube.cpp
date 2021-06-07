#include "cube.h"

Cube::Cube(GLuint pprogram) : Object(){
    /*
    this cube class is for a predefined cube
    cube derives from object for setup and draw functions
    */
    program = pprogram;

    aindices = {1,3,0,7,5,4,
                4,1,0,5,2,1,
                2,7,3,0,7,4,
                1,2,3,7,6,5,
                4,5,1,5,6,2,
                2,6,7,0,3,7};

    anormind = {0,0,0,1,1,1,
                 2,2,2,3,3,3,
                 4,4,4,5,5,5,
                 0,0,0,1,1,1,
                 2,2,2,3,3,3,
                 4,4,4,5,5,5};

    avertices = {1.0,-1.0,-1.0,
                1.0,-1.0,1.0,
                -1.0,-1.0,1.0,
                -1.0,-1.0,-1.0,
                1.0,1.0,-1.0,
                1.0,1.0,1.0,
                -1.0,1.0,1.0,
                -1.0,1.0,-1.0};

    anormals = {0.0,-1.0,0.0,
                  0.0,1.0,0.0,
                  1.0,0.0,0.0,
                  0.0,0.0,1.0,
                  -1.0,0.0,0.0,
                  0.0,0.0,-1.0};

    for(int i = 0; i < aindices.size(); i++){
        for(int j = 0; j < 3; j++){
            array.push_back(avertices[aindices[i]*3+j]);
            normals.push_back(anormals[anormind[i]*3+j]);
        }
    }
}
