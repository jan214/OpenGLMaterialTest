#include "object.h"
#include <iostream>
#include <math.h>

Object::Object(std::vector<uint16_t> pindices,std::vector<float> pvertices,std::vector<uint16_t> pnormind, std::vector<float> pnormals, GLuint &pprogram){
    //for creating a test object with custom vertices,indices,normals and material
    indices = pindices;
    vertices = pvertices;
    program = pprogram;
    translation = {0.0f,0.0f,0.0f};

    for(int i = 0; i < indices.size(); i++){
        for(int j = 0; j < 3; j++){
            array.push_back(vertices[indices[i]*3+j]);
            normals.push_back(pnormals[pnormind[i]*3+j]);
        }
    }

    windowxsize = glGetUniformLocation(program,"sizex");
    windowysize = glGetUniformLocation(program,"sizey");
}

Object::Object(){

}

Object::~Object(){

}

void Object::setup(){
    //setting up all buffer for vertices and normals
    glUseProgram(program);

    glGenBuffers(1,&vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
    std::cout << array.size() << std::endl;
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*array.size(),&array[0],GL_STATIC_DRAW);

    glGenBuffers(1,&normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,normalBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*normals.size(),&normals[0],GL_STATIC_DRAW);
    //setting up attribute variables
    locPosition = glGetAttribLocation(program,"position");
    locNormals = glGetAttribLocation(program,"normal");
    //setting up uniforms
    windowxsize = glGetUniformLocation(program,"screenx");
    windowysize = glGetUniformLocation(program,"screeny");
    locTranslation = glGetUniformLocation(program, "translation");
    tMatrix = glGetUniformLocation(program, "translate");
    yrotationmatrix = glGetUniformLocation(program, "rotation");
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Object::draw(float ptranslate[3],float protation[3]){
    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);

    glVertexAttribPointer(locPosition,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,0);
    glEnableVertexAttribArray(locPosition);

    glBindBuffer(GL_ARRAY_BUFFER,normalBuffer);

    glVertexAttribPointer(locNormals,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,0);
    glEnableVertexAttribArray(locNormals);

    glUniform1f(windowxsize, windowsize[0]);
    glUniform1f(windowysize, windowsize[1]);
    glUniform3f(locTranslation, translation[0], translation[1], translation[2]);

    //translation matrix
    tmatrix[0][0] = 1.0f;
    tmatrix[0][1] = 0.0f;
    tmatrix[0][2] = 0.0f;
    tmatrix[0][3] = ptranslate[0];
    tmatrix[1][0] = 0.0f;
    tmatrix[1][1] = 1.0f;
    tmatrix[1][2] = 0.0f;
    tmatrix[1][3] = ptranslate[1];
    tmatrix[2][0] = 0.0f;
    tmatrix[2][1] = 0.0f;
    tmatrix[2][2] = 1.0f;
    tmatrix[2][3] = ptranslate[2];
    tmatrix[3][0] = 0.0f;
    tmatrix[3][1] = 0.0f;
    tmatrix[3][2] = 0.0f;
    tmatrix[3][3] = 1.0f;

    glUniformMatrix4fv(tMatrix, 1, GL_TRUE, &tmatrix[0][0]);
    //rotation around the y axis matrix
    rmatrix[0][0] = cos(-protation[1]);
    rmatrix[0][1] = 0.0f;
    rmatrix[0][2] = sin(-protation[1]);
    rmatrix[0][3] = 0.0f;
    rmatrix[1][0] = 0.0f;
    rmatrix[1][1] = 1.0f;
    rmatrix[1][2] = 0.0f;
    rmatrix[1][3] = 0.0f;
    rmatrix[2][0] = -sin(-protation[1]);
    rmatrix[2][1] = 0.0f;
    rmatrix[2][2] = cos(-protation[1]);
    rmatrix[2][3] = 0.0f;
    rmatrix[3][0] = 0.0f;
    rmatrix[3][1] = 0.0f;
    rmatrix[3][2] = 0.0f;
    rmatrix[3][3] = 1.0f;

    glUniformMatrix4fv(yrotationmatrix, 1, GL_TRUE, &rmatrix[0][0]);
    //draw all vertices
    glDrawArrays(GL_TRIANGLES,0,array.size());
}

void Object::translate(std::vector<float> ptranslation){
    translation = ptranslation;
}
