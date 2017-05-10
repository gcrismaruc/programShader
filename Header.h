#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <vector>
#include <string>
#include <io.h>
#include <sys/types.h>
#include <fstream>
#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\freeglut.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2\core\types.hpp"
#include <SOIL.h>

#define BUFFER_OFFSET(i) ((char*)NULL + (i))
#define WIDTH 640
#define HEIGHT 480


int idWindowHandle;
GLhandleARB idProgram;
GLhandleARB idVao;
GLhandleARB idVbo[2]; // positions and colors
GLhandleARB idEbo;
GLhandleARB idVShader;
GLhandleARB idFShader;
GLhandleARB idAttributePosition;
GLhandleARB idAttributeColor;
GLhandleARB idUniformColor;
GLhandleARB pmatrix_location;
GLhandleARB rmatrix_location;
GLhandleARB smatrix_location;

GLhandleARB projMatrix_location;
GLhandleARB depthProjMatrix_location;

GLuint	 imageTextureBufferID;	// We have to create a buffer to hold the image. However, it WON'T go in the vertex buffer
GLuint	 imageTextureCoordID;	// The ID of the "texCoord" variable in the shader
GLuint	 imageTextureID;			// The ID of the "texture" variable in the shader
GLubyte* imageData;		// This will contain the raw color information from the file

GLuint	 gradientTextureBufferID;	
GLuint	 gradientTextureCoordID;	
GLuint	 gradientTextureID;			

cv::Mat imgKinect;
unsigned char* image;


int vertexIndices[] = {
	3,0,4,1,5,2
};

GLuint * vertexIndices1;

GLfloat *vertexPositions1;

GLfloat vertexPositions[] = {
	-0.9875, 0.5, 0,
	-0.971875, 0.5, 0,
	-0.95625, 0.5, 0,
	-0.9875, -0.5, 0,
	-0.971875, -0.5, 0,
	-0.95625, -0.5, 0,
};


//GLfloat textureCoord[] = {
//	0.0f, 0.0f,
//	1.0f, 0.0f,
//	1.0f, 1.0f,
//	0.0f, 1.0f
//};


GLfloat textureCoord[] = {
	0.0f, 0.0f,
	640.0f, 0.0f,
	640.0f, 480.0f,
	0.0f, 480.0f
};

//GLfloat vertexPositions[] = {
//	-1.0f, -1.0f, -1.0f,
//	1.0f, -1.0f, -1.0f,
//	1.0f, 1.0f, -1.0f,
//	-1.0f, 1.0f, -1.0f
//};


GLfloat vertexColors[] = {
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.2f, 1.0f, 0.5f, 1.0f,
};
long lengthVertexColors = 12;

GLfloat pmatrix[] = {
	2.0f / 640, 0.0f, 0.0f, 1.0f,
	0.0f, 2.0f / 480, 0.0f, 1.0f,
	0.0f, 0.0f, -2.0f, -1.0f,
	0.0f, 0.0f, -1.0f, 1.0f
};

GLfloat rmatrix[] = {
	cos(10), 0.0f, sin(10), 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	-sin(10), 0.0f, cos(10), 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};

GLfloat smatrix[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, cos(10), sin(10), 0.0f,
	0.0f, -sin(10), cos(10), 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};

float angle = 0.0f;

GLfloat projectionMatrix[] = {
	1.98761f, - 0.110331f, - 0.228261f, - 20.3096f,
	- 0.0863136f,  2.3955f,  1.04354f,  98.3571f,
	- 0.0026282f, - 0.116978f,  1.53254f,  170.111f,
	- 0.00170995f, - 0.0761082f,  0.997098f,  184.214f
};

//GLfloat projectionMatrix[] = {
//	-0.0403285f, - 0.0154059f, - 0.231736f, - 23.5552f,
//	0.00303723f, - 0.0890088f, - 0.244171f, - 25.1202f,
//	- 4.64821e-005f,  0.00438945f,  0.0555216f,  5.35711f,
//	- 0.000834586f,  0.0788126f,  0.996889f,  99.7814f
//};

//GLfloat projectionMatrix[] = {
//	2.00197f, - 0.110667f, - 0.227943f, - 20.2784f,
//	- 0.0864975f, 2.41306f, 1.05102f, 99.06f,
//	- 0.00296481f, - 0.117514f, 1.53336f, 170.397f,
//	- 0.00192788f, - 0.0764144f, 0.997074f, 184.904f
//};

GLfloat depthProjectionMatrix[] = {
	0.000173667, 0.0f, 0.0f, 0.0f,
	0.0f, 0.000173667f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, -0.00000289f,
	-0.055573332f, -0.041679999f, -0.1f, 0.00315323f
};

//GLfloat projectionMatrix[] = {
//	0.00741191f, -0.000695842f, 0.0028695f, 0.611736f,
//	-0.000246396f, 0.00649244f, 0.00571214f, 0.790973f,
//	0.0f, 0.0f, 1.0f, 0.0f,
//	- 1.24648e-008f, - 5.54797e-007f, 7.26843e-006f, 0.00134284f
//};

GLhandleARB ebo;
GLhandleARB vao;
GLhandleARB vbo;

