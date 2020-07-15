//============================================================================
// Name        : Learning on my own
// Version     : 1.0
// Description : Create 2 triangles using two different VAOs and VBOs
//============================================================================

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#define GLEW_STATIC
#include <GL\glew.h>

// Include GLFW
#include <GLFW\glfw3.h>

using namespace std;

GLuint renderingProgram;

GLuint m_VBO[2];
GLuint m_VAO[2];
//GLuint m_EBO;

using namespace std;


GLuint createShaderProgram() {
    // declares two shaders as character strings
    // Vertex Shader code

    static const char *vshaderSource =
    		"#version 330  \n"
    		"layout (location = 0) in vec3 pos; \n" //Vendrá un array con 3 coordenadas, porfa almacenalo en pos
    		"void main() { \n"
    		" gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);	\n" //Cada coordenada anterior, asignala a Gl_position, necesito listo cada vertices, rai nau
    		"}";

    // Fragment Shader
    static const char *fshaderSource =
    		"#version 330  \n"
    		"out vec4 fColor; \n" //Crea la variable para el color, ojo, tiene que ser out
    		"void main(){ \n"
    	    " fColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n" //Asignale un color bonito xfa
    	    "}";

    
   GLuint vShader = glCreateShader(GL_VERTEX_SHADER); //Creame un shader de tipo GL_VERTEX_SHADER
   GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(vShader, 1, &vshaderSource, NULL);//a la variable que cree, asignale el stringSource, ojo, solo hay 1
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    
    glCompileShader(vShader); //Compila el VShader, ya tiene la info, thks
    glCompileShader(fShader);
    
    //Tengo todo listo, ahora necesito linkearlo al shaderProgram

    //Creame el ID de un program
    GLuint vfProgram = glCreateProgram();
    
  //Al programa creado, porfa, asignale los shaders que cree hace poco :(
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    
   //Oki, une todo lo que está en el shader program, rai nau
    glLinkProgram(vfProgram);
    
    return vfProgram;
}

void init (GLFWwindow* window) {
    renderingProgram = createShaderProgram();
    //Puntos base
    GLfloat firstTriangle[] = {
            -0.9f, -0.5f, 0.0f,  // left
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top
        };
    GLfloat secondTriangle[] = {
            0.0f, -0.5f, 0.0f,  // left
            0.9f, -0.5f, 0.0f,  // right
            0.45f, 0.5f, 0.0f   // top
        };


    //Generame dos VAO y 2 VBO
    glGenVertexArrays(1, &m_VAO[0]);
    glGenBuffers(1, &m_VBO[0]);

    glGenVertexArrays(1, &m_VAO[1]);
       glGenBuffers(1, &m_VBO[1]);

    //Configurando mi primer triangulo
    //Ojo, usaré el primer VA0
    glBindVertexArray(m_VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Cada paquete es de 3
    glEnableVertexAttribArray(0);

    //Configurando segundo triangulo
    glBindVertexArray(m_VAO[1]);
     glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
     glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Cada paquete es de 3
     glEnableVertexAttribArray(0); //Im in doubt with this
}

void display(GLFWwindow* window, double currentTime) {
	//Usa lo que cree en el createProgram
	glUseProgram(renderingProgram);

		// Ya que tengo el programa, porfa, usa el vao(y el vbo indirectamente)
		glBindVertexArray(m_VAO[0]);
		//Dibujame un triangulo
	    glDrawArrays(GL_TRIANGLES, 0, 3);

	    //Segundo VAO
	    glBindVertexArray(m_VAO[1]);
	    		//Dibujame un triangulo
	    glDrawArrays(GL_TRIANGLES, 0, 3);
		//Ahora dibujaré elementos uwuwuwu
		//glDrawElements(GL_TRIANGLES, 6 //Numero de vertices a dibuujar
			//	, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);
}

int main(void) {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 	// Resizable option.

    GLFWwindow* window = glfwCreateWindow(600, 600, "Happiness", NULL, NULL);
    glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);
    
    init(window);
    
    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
