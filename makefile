OpenGLTest.exe : main.o object.o cube.o glad.o
	g++ -o OpenGLTest.exe main.o object.o cube.o glad.o -I glad -L..\OpenGLTestProject\GLFW -lglfw3 -lopengl32 -lgdi32

main.o : main.cpp
	g++ -c main.cpp -I glad -I..\OpenGLTestProject\GLFW\include -lglfw3 -std=c++11

object.o : object.cpp
	g++ -c object.cpp -I glad -I..\OpenGLTestProject\GLFW\include -lglfw3 -std=c++11

cube.o : cube.cpp
	g++ -c cube.cpp -I glad -I..\OpenGLTestProject\GLFW\include -lglfw3 -std=c++11

glad.o : glad.c
	g++ -c glad.c -I glad -I..\OpenGLTestProject\GLFW\include -lglfw3 -std=c++11