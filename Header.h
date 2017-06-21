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
GLhandleARB idAttributeZCoordinate;
GLhandleARB idAttributeColor;
GLhandleARB idUniformColor;
GLhandleARB pmatrix_location;
GLhandleARB rmatrix_location;

GLhandleARB viewPort_location;
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
GLfloat *textureCoord1;
GLfloat *zCoordinate;

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

GLfloat viewPort[] = {
	1, 0, 0, 0,
	0, 1.333333333333333, 0, 0,
	0, 0, -1.002002002002002, -0.2002002002002002,
	0, 0, -1, 0
};

float angle = 0.0f;

//GLfloat projectionMatrix[] = {
//	2.99952f, 0.0757395f, 0.0550869f, 7.13796f,
//	- 0.100926f, 4.00626f, 0.857646f, 82.5232f,
//	0.0743716f, 0.0344721f, - 1.53409f, - 73.0032f,
//	0.0484101f, 0.0224387f, - 0.998575f, 64.4322f
//};

GLfloat projectionMatrix[] = {
	3.60291f, -0.0682034f, -0.635952f, -58.0176f,
	0.0946639f, 4.77029f, 1.30154f, 122.229f,
	0.234703f, 0.04387f, -1.55057f, -198.061f,
	0.149602f, 0.0279632f, -0.988351f, -262.8f
};


//0.000534534, -2.02294e-05, 6.75135e-06, 4.35879e-06,
//6.55067e-06, 0.000708243, -1.84155e-06, -1.18893e-06,
//-2.28069e-05, -0.000239963, 0.000216806, -0.00019543,
//-0.154969, 0.00970855, -0.0830702, 0.31176

GLfloat depthProjectionMatrix[] = {
	0.000173667, 0.0f, 0.0f, 0.0f,
	0.0f, 0.000173667f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, -0.00000289f,
	-0.055573332f, -0.041679999f, -0.1f, 0.00315323f
};

//GLfloat depthProjectionMatrix[] = {
//	0.000173667f,	0,	0, - 0.055573332f,
//	0,	0.000173667f,	0, - 0.041679999f,
//	0,	0,	0, - 0.1f,
//	0,	0, - 0.00000289f,	0.00315323f
//};

GLhandleARB ebo;
GLhandleARB vao;
GLhandleARB vbo;

