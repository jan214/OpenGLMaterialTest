#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "object.h"
#include "cube.h"
#include "plane.h"
#include "lodePNG.h"

#define PI 3.141

int windowsize[2] = {640,320}; //size of the window
GLint windowxsize, windowysize; //uniform for shader

int main(void){
    GLFWwindow* window;
    
    bool bCursor = true; //show hide cursor by pressing alt
    bool bButtonDown = false;
    double mouse[2] = {0.0f,0.0f}; //for mouse movement
    double move[2] = {0.0f,0.0f}; //also for mouse movement

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowsize[0], windowsize[1], "Hello World", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(0);

    //vertex shader source
    const char* vertexShadertext = "#version 110\n"
                                    "attribute vec3 position;\n"
                                    "attribute vec3 normal;\n"
                                    "uniform float screenx;\n"
                                    "uniform float screeny;\n"
                                    "uniform vec3 translation;\n"
                                    "uniform mat4 translate;\n"
                                    "uniform mat4 rotation;\n"
                                    "varying vec4 aposition;\n"
                                    "varying vec4 anormal;\n"
                                    "vec3 screenpos;\n"
                                    "void main(){\n"
                                    "anormal = rotation*vec4(normal,1.0);\n"
                                    "aposition = rotation*translate*vec4(position+translation,1.0);\n"
                                    "screenpos = vec3(aposition.x/aposition.z,aposition.y/aposition.z,aposition.z);\n"
                                    "gl_Position = vec4(screenpos.x,screenpos.y,screenpos.z*0.01,1.0);\n"
                                    "}\n";
    //frag shader for ambient only material
    const char* fragShadertext = "#version 110\n"
                                    "varying vec3 aposition;\n"
                                    "varying vec3 anormal;\n"
                                    "void main(){\n"
                                    "gl_FragColor = vec4(1.0,1.0,1.0,1.0);\n"
                                    "}\n";
    //fragment shader for a red metallic material
    const char* redfragShadertext = "#version 110\n"
                                    "varying vec4 anormal;\n"
                                    "varying vec4 aposition;\n"
                                    "varying float arotation;\n"
                                    "float diffuse;\n"
                                    "vec3 lightfrag;\n"
                                    "vec3 reflec;\n"
                                    "float specular;\n"
                                    "void main(){\n"
                                    "lightfrag = normalize(vec3(0.0,2.0,3.0)-aposition.xyz);\n"
                                    "diffuse = dot(lightfrag,anormal.xyz);\n"
                                    "reflec = reflect(lightfrag,anormal.xyz);\n"
                                    "specular = pow(dot(reflec,vec3(0.0,0.0,0.0)-lightfrag),128.0);\n"
                                    "gl_FragColor = (specular+diffuse) * vec4(1.0,0.0,0.0,1.0)*0.9;\n"
                                    "}\n";
    //fragment shader for green diffuse material
    const char* greenfragShadertext = "#version 110\n"
                                      "varying vec4 anormal;\n"
                                      "varying vec4 aposition;\n"
                                      "float diffuse;\n"
                                      "vec3 lightfrag;\n"
                                      "vec3 reflec;\n"
                                      "float specular;\n"
                                      "void main(){\n"
                                      "lightfrag = normalize(vec3(0.0,0.0,0.0)-aposition.xyz);\n"
                                      "diffuse = dot(lightfrag,anormal.xyz);\n"
                                      "gl_FragColor = (diffuse) * vec4(0.0,1.0,0.0,1.0)*0.9;\n"
                                      "}\n";
    
    GLuint vertexShader, fragShader, redfragShader, greenfragShader, vertexBuffer, indicesBuffer, program, redprogram,greenprogram;
    //compiling and linking all material shaders
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShadertext,NULL);
    glCompileShader(vertexShader);

    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader,1,&fragShadertext,NULL);
    glCompileShader(fragShader);

    redfragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(redfragShader,1,&redfragShadertext,NULL);
    glCompileShader(redfragShader);

    greenfragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(greenfragShader,1,&greenfragShadertext,NULL);
    glCompileShader(greenfragShader);

    program = glCreateProgram();
    glAttachShader(program,vertexShader);
    glAttachShader(program,fragShader);
    glLinkProgram(program);
    //glUseProgram(program);

    redprogram = glCreateProgram();
    glAttachShader(redprogram,vertexShader);
    glAttachShader(redprogram,redfragShader);
    glLinkProgram(redprogram);
    glUseProgram(redprogram);

    greenprogram = glCreateProgram();
    glAttachShader(greenprogram,vertexShader);
    glAttachShader(greenprogram,greenfragShader);
    glLinkProgram(greenprogram);
    //creating test objects
    Cube* obj1 = new Cube(program);
    obj1->setup();
    obj1->translate(std::vector<float>{0.0f,0.0,5.0f});

    Cube* obj2 = new Cube(greenprogram);
    obj2->setup();
    obj2->translate(std::vector<float>{-3.0f,0.0f,5.0f});

    Cube* obj3 = new Cube(redprogram);
    obj3->setup();
    obj3->translate(std::vector<float>{3.0,0.0f,5.0f});


    Plane* planeobj = new Plane(redprogram);
    planeobj->setup();
    planeobj->translate(std::vector<float>{0.0f,0.0f,3.0f});
    //for translation(WASD) and rotation(locked mouse)
    float translate[3] = {0.0f,0.0f,0.0f};
    float rotation[3] = {0.0f,0.0f,0.0f};

    glEnable(GL_DEPTH_TEST);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(!bCursor){
            //mouse stuff
            glfwGetCursorPos(window,&move[0],&move[1]);
            if(mouse[0] > 360.0f){
                mouse[0] -= 360.0f;
            }else if(mouse[0] < 0.0f){
                mouse[0] += 360.0f;
            }
            mouse[0] += move[0];
            mouse[1] += move[1];
            rotation[1] = mouse[0] * (PI / 180.0f);
            std::cout << mouse[0] << "/" << mouse[1] << std::endl;
            glfwSetCursorPos(window,0.0,0.0);
        }

        if(glfwGetKey(window,GLFW_KEY_W)){
            translate[2] -= 0.1f;
        }

        if(glfwGetKey(window,GLFW_KEY_S)){
            translate[2] += 0.1f;
        }

        if(glfwGetKey(window,GLFW_KEY_D)){
            translate[0] -= 0.1f;
        }

        if(glfwGetKey(window,GLFW_KEY_A)){
            translate[0] += 0.1f;
        }

        if(glfwGetKey(window,GLFW_KEY_LEFT_ALT)){
            if(!bButtonDown){
                if(bCursor){
                    bCursor = false;
                }else{
                    bCursor = true;
                }
                bButtonDown = true;
            }
        }

        if(glfwGetKey(window,GLFW_KEY_LEFT_ALT)==GLFW_RELEASE){
            if(bButtonDown){
                bButtonDown = false;
            }
        }

        if(bCursor){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }else{
            glfwSetCursorPos(window,0.0f,0.0f);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        //draw testobjects
        obj1->draw(translate,rotation);
        obj2->draw(translate,rotation);
        obj3->draw(translate,rotation);
        planeobj->draw(translate,rotation);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
