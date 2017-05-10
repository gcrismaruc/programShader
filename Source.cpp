#pragma warning (disable : 4996)

#include "Header.h";



using namespace std;

string textFileRead(char *fn) {

	std::ifstream ifile(fn);
	std::string filetext;

	while (ifile.good()) {
		std::string line;
		std::getline(ifile, line);
		filetext.append(line + "\n");
	}

	return filetext;
}


void addVertexPositions(){

	/*vertexIndices1 = new GLuint[WIDTH * HEIGHT * 2];
	vertexPositions1 = new GLfloat[WIDTH * HEIGHT * 3];
	long long index = 0;
	
	for (unsigned int y = 0; y < HEIGHT; ++y) {
		for (unsigned int x = 0; x < WIDTH; ++x) {
			// Set the template vertex' position to the pixel center's position: 
			vertexPositions1[index] = GLfloat(x) + 0.5;
			vertexPositions1[index + 1] = GLfloat(y) + 0.5;
			vertexPositions1[index + 2] = GLfloat(0);

			index += 3;	
		}
	}

	index = 0;
	for (unsigned int y = 1; y < HEIGHT; ++y) {
		for (unsigned int x = 0; x < WIDTH; ++x) {
			// Set the template vertex' position to the pixel center's position:
			vertexIndices1[index] = GLfloat(y * WIDTH + x);
			vertexIndices1[index + 1] = GLfloat((y - 1) * WIDTH + x);

			index += 2;
		}
	}*/

	vertexIndices1 = new GLuint[WIDTH * HEIGHT * 2];
	vertexPositions1 = new GLfloat[WIDTH * HEIGHT * 3];
	textureCoord1 = new GLfloat[WIDTH * HEIGHT * 2];
	long long index = 0;

	for (double y = -1; y <= 1; y += 0.00416666666667) {
		for (double x = -1; x <= 1; x += 0.003125) {
			// Set the template vertex' position to the pixel center's position: 
			vertexPositions1[index] = GLfloat(x);
			vertexPositions1[index + 1] = GLfloat(y);
			vertexPositions1[index + 2] = GLfloat(0);
			index += 3;
		}
	}
	index = 0;
	for (unsigned int y = 1; y < HEIGHT; ++y) {
		for (unsigned int x = 0; x < WIDTH;  ++x) {
			// Set the template vertex' position to the pixel center's position:
			vertexIndices1[index] = GLfloat(y * WIDTH + x );
			vertexIndices1[index + 1] = GLfloat((y - 1) * WIDTH + x);
			index += 2;
		}
	}


	index = 0;
	for (unsigned int y = 0; y < HEIGHT; ++y) {
		for (unsigned int x = 0; x < WIDTH; ++x) {
			// Set the template vertex' position to the pixel center's position: 
			textureCoord1[index] = GLfloat(x);
			textureCoord1[index + 1] = GLfloat(y);

			index += 2;
		}
	}
	
	/*ofstream f("vertexPositions.txt");

	for (float x = -1; x <= 1; x += 0.003125){
		vertexPositions1[index] = GLfloat(x);
		vertexPositions1[index + 1] = GLfloat(-0.5);
		vertexPositions1[index + 2] = GLfloat(0);

		f << vertexPositions1[index] << " " << vertexPositions1[index + 1] << " " << vertexPositions1[index + 2] << "\n";
		index += 3;
	}
	for (float x = -1; x <= 1; x += 0.003125){
		vertexPositions1[index] = GLfloat(x);
		vertexPositions1[index + 1] = GLfloat(0.5);
		vertexPositions1[index + 2] = GLfloat(0);

		f << vertexPositions1[index] << " " << vertexPositions1[index + 1] << " " << vertexPositions1[index + 2] << "\n";
		index += 3;
	}
	f.close();
	index = 0;

	ofstream g("trianglesIndices.txt");

		for (unsigned int x = 0; x < WIDTH; ++x) {
			vertexIndices1[index] = GLfloat(WIDTH + x);
			vertexIndices1[index + 1] = GLfloat(x);
			g << vertexIndices1[index] << " " << vertexIndices1[index + 1] << "\n";

			index += 2;
		}
		g.close();

	
	ofstream g1("indecsi.txt");

	
	for (int idx = 0; idx < WIDTH * 2; idx += 2){
		g1 << "| " << vertexPositions1[3*vertexIndices1[idx]] << ", " << vertexPositions1[3*vertexIndices1[idx] + 1] << ", " << vertexPositions1[3*vertexIndices1[idx] + 2] << ", | "
			"| " << vertexPositions1[3*vertexIndices1[idx+1]] << ", " << vertexPositions1[3*vertexIndices1[idx+1] + 1] << ", " << vertexPositions1[3*vertexIndices1[idx+1] + 2] << ", |\n";
	}
	g1.close();
	*/

	/*index = 0;
	ofstream f("vertexPositions.txt");

	for (unsigned int y = 0; y < HEIGHT; ++y) {
		for (unsigned int x = 0; x < WIDTH; ++x) {
			f << vertexPositions1[index] << " " << vertexPositions1[index + 1] << " " << vertexPositions1[index + 2] << "\n";
			index += 3;
		}		
	}


	index = 0;
	ofstream g("trianglesIndices.txt");

	for (unsigned int y = 1; y < HEIGHT; ++y) {
		for (unsigned int x = 0; x < WIDTH; ++x) {
			g << vertexIndices1[index] << " " << vertexIndices1[index + 1] <<"\n";
			index += 2;
		}
	}

	f.close();
	g.close();*/
	
	std::cout << "Done!";
}
void setShaders(){

	string vertexShaderCode = textFileRead("vertexShader.vs");
	const char* vv = vertexShaderCode.c_str();
	GLint const vertexShaderLength = vertexShaderCode.size();
	
	idVShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(idVShader, 1, &vv, NULL);
	glCompileShader(idVShader);
	std::cout << "idVShader " << idVShader << "shader length " << vv << endl;

	GLint Result = GL_FALSE;
	int InfoLogLength;


	glGetShaderiv(idVShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(idVShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(idVShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	string fragmentShaderCode = textFileRead("fragmentShader.fgs");
	const char* ff = fragmentShaderCode.c_str();
	GLint const fragmentShaderLength = fragmentShaderCode.size();
	
	idFShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(idFShader, 1, &ff, &fragmentShaderLength);
	glCompileShader(idFShader);
	std::cout << "idFShader " << idFShader << "shader length " << fragmentShaderLength << endl;

	glGetShaderiv(idFShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(idFShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(idFShader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}


	idProgram = glCreateProgram();

	glAttachShader(idProgram, idFShader);
	glAttachShader(idProgram, idVShader);

	//glUniform4fv(glGetUniformLocation(idProgram, "in_Color"), 1, mycolor);

	glLinkProgram(idProgram);

	GLint linkStatus;
	glGetProgramiv(idProgram, GL_LINK_STATUS, &linkStatus);
	char m_linked = (linkStatus == GL_TRUE);

	if (!m_linked)
	{
		GLint logLength;
		glGetProgramiv(idProgram, GL_INFO_LOG_LENGTH, &logLength);

		char* log = new char[logLength];
		GLsizei length;
		glGetProgramInfoLog(idProgram, logLength, &length, log);

		std::cout << log;

		delete[] log;
	}
	
		

	const char *positionAttributeName = "in_Position";
	idAttributePosition = (GLuint)glGetAttribLocation(idProgram, positionAttributeName);
	if (idAttributePosition == -1) {
		std::cout << "Error! Vertex getAttribLocation.\n";
	}

	/*const char *colorAttributeName = "in_Color";
	idAttributeColor = (GLuint)glGetAttribLocation(idProgram, colorAttributeName);
	if (idAttributeColor == -1) {
		cout << "Error! Fragment glGetUniformLocation.\n";

	}*/
	
	//imagine kinect
	int width, height;
	imgKinect = cv::imread("calibration\\calibration20.png", CV_LOAD_IMAGE_UNCHANGED | CV_LOAD_IMAGE_ANYDEPTH);
	//cv::flip(imgKinect, imgKinect,0);
	//std::cout << type2str(imgKinect.type())<<endl;
	glEnable(GL_TEXTURE_RECTANGLE);					// Turn on texturing
	glGenTextures(2, &imageTextureBufferID);				// Create an ID for a texture buffer
	glBindTexture(GL_TEXTURE_RECTANGLE, imageTextureBufferID);	// Bind that buffer so we can then fill it (in next line)
	glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RED, WIDTH, HEIGHT, 0, GL_RED, GL_UNSIGNED_SHORT, imgKinect.ptr());

	imageTextureCoordID = glGetAttribLocation(idProgram, "s_vTexCoord");

	glTexParameterf(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// Set the preferences
	glTexParameterf(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameterf(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	imageTextureID = glGetUniformLocation(idProgram, "texture");
	glActiveTexture(GL_TEXTURE0);				// Turn on texture unit 0
	glUniform1i(imageTextureID, 0);

	pmatrix_location = glGetUniformLocation(idProgram, "pmatrix");

	projMatrix_location = glGetUniformLocation(idProgram, "projMatrix");
	depthProjMatrix_location = glGetUniformLocation(idProgram, "depthProjMatrix");

	glUseProgram(idProgram);
}


/******************************* CALLBACKS ***********************/
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void idle() {
	glutPostRedisplay();
}


void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUniformMatrix4fv(pmatrix_location, 1, GL_TRUE, pmatrix);

	glUniformMatrix4fv(projMatrix_location, 1, GL_TRUE, projectionMatrix);
	glUniformMatrix4fv(depthProjMatrix_location, 1, GL_TRUE, depthProjectionMatrix);



	GLuint* indexPtr = 0;
	for (unsigned int y = 1; y < HEIGHT; ++y, indexPtr += WIDTH * 2){
		glDrawElements(GL_QUAD_STRIP, WIDTH * 2, GL_UNSIGNED_INT, indexPtr);
	}

	//glDrawElements(GL_LINES, HEIGHT * WIDTH * 2, GL_UNSIGNED_INT, 0);

	/*GLuint* idx = GLuint(0);
	//idx += 1;
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
	*/
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	imgKinect = cv::imread("calibration\\gradient.png", CV_LOAD_IMAGE_COLOR);
	cv::imshow("gradient", imgKinect);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutCreateWindow("Hello");

	//glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	//glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glewExperimental = GL_TRUE;

	GLenum glew_status;
	glew_status = glewInit();
	
	if (glew_status != GLEW_OK) {
		std::cout<<"GLEW error: ";
	}

	if (!GLEW_VERSION_4_0) {
		std::cout<<"No support for OpenGL 4.0 found : ";
	}

	addVertexPositions();
	setShaders();

	//vertices buffer
	//generez nume pentru array
	glGenVertexArrays(1, &vao);
	//fac "activ" noul array -> vao, si il creeaza daca este cazul
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, WIDTH * HEIGHT * 3 * sizeof(GLfloat)+WIDTH * HEIGHT * 2 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, WIDTH * HEIGHT * 3 * sizeof(GLfloat), vertexPositions1);
	glBufferSubData(GL_ARRAY_BUFFER, WIDTH * HEIGHT * 3 * sizeof(GLfloat), WIDTH * HEIGHT * 2 * sizeof(GLfloat), textureCoord1);

	glVertexAttribPointer(idAttributePosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//load text coords
	glVertexAttribPointer(imageTextureCoordID, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(WIDTH * HEIGHT * 3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(imageTextureCoordID);
	glEnableVertexAttribArray(idAttributePosition);
	
	//indices buffer
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, WIDTH * HEIGHT * 2 * sizeof(GLfloat), vertexIndices1, GL_STATIC_DRAW);
	//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(vertexIndices), vertexIndices);
	
	
	
	
	glutMainLoop();

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, idVbo);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glUseProgram(0);
	glDeleteProgram(idProgram);



	return 0;

}