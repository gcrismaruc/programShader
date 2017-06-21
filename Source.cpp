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

	vertexIndices1 = new GLuint[WIDTH * HEIGHT * 2];
	vertexPositions1 = new GLfloat[WIDTH * HEIGHT * 2];
	textureCoord1 = new GLfloat[WIDTH * HEIGHT * 2];
	zCoordinate = new GLfloat[WIDTH * HEIGHT];

	long long index = 0;
	long zIndex = 0;
	
	//for (double y = -1; y <= 1; y += 0.00416666666667) {
	//	for (double x = -1; x <= 1; x += 0.003125) {
	//		// Set the template vertex' position to the pixel center's position: 
	//		vertexPositions1[index] = GLfloat(x);
	//		vertexPositions1[index + 1] = GLfloat(y);
	//		vertexPositions1[index + 2] = GLfloat(0);
	//		index += 3;
	//	}
	//}

	for (double y = 0; y < 480 ; y++) {
		for (double x = 0; x < 640; x++) {
			// Set the template vertex' position to the pixel center's position: 
			vertexPositions1[index] = GLfloat(x);
			vertexPositions1[index + 1] = GLfloat(y);
			//vertexPositions1[index + 2] = GLfloat(0);
			index += 2;
		}
	}


	imgKinect = cv::imread("calibration\\calibration20.png", CV_LOAD_IMAGE_UNCHANGED | CV_LOAD_IMAGE_ANYDEPTH);
	for (int y = 0; y < 480; y++)
	{
		for (int x = 0; x < 640; x++)
		{
			ushort z = imgKinect.at<ushort>(cv::Point(x, y));
			//cout << z << " ";
			zCoordinate[zIndex] = GLfloat(z);
			//cout << zCoordinate[zIndex] << " \n";
			zIndex++;
		}
	}


	//float vx, vy,vz;
	//ifstream file("bufferGenerat.txt");

	//for (double y = 0; y < 480 ; y++) {
	//	for (double x = 0; x < 640; x++) {
	//		// Set the template vertex' position to the pixel center's position: 
	//		file >> vx >> vy;
	//		vertexPositions1[index] = GLfloat(vx);
	//		vertexPositions1[index + 1] = GLfloat(vy);
	//		vertexPositions1[index + 2] = GLfloat(0.9);
	//		index += 3;
	//	}
	//}

	//index = 0;
	//ofstream g("vertexPosition1.txt");
	//for (double y = 0; y < 480; y++) {
	//	for (double x = 0; x < 640; x++) {
	//		// Set the template vertex' position to the pixel center's position: 
	//		g << vertexPositions1[index] << " "<<vertexPositions1[index + 1] << " "<< vertexPositions1[index + 2]<<std::endl;
	//		index += 3;
	//	}
	//}
	//g.close();

	index = 0;
	for (unsigned int y = 1; y < HEIGHT; ++y) {
		for (unsigned int x = 0; x < WIDTH; ++x) {
			// Set the template vertex' position to the pixel center's position:
			vertexIndices1[index] = GLfloat(y * WIDTH + x);
			vertexIndices1[index + 1] = GLfloat((y - 1) * WIDTH + x);

			index += 2;
		}
	}

	/*vertexIndices1 = new GLuint[WIDTH * HEIGHT * 2];
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

	ifstream f("buffer.txt");
	float x1, y1, z;
	for (unsigned int y = 1; y < HEIGHT; ++y) {
		for (unsigned int x = 0; x < WIDTH; ++x) {
			f >> x1 >> y1 >> z;
			vertexPositions1[index] = GLfloat(x1);
			vertexPositions1[index + 1] = GLfloat(y1);
			vertexPositions1[index + 2] = GLfloat(z);
			//cout << z << " ";
			index += 3;
		
		}
	}
	
	f.close();*/

	index = 0;
	for (unsigned int y = 0; y < HEIGHT; ++y) {
		for (unsigned int x = 0; x < WIDTH; ++x) {
			// Set the template vertex' position to the pixel center's position: 
			textureCoord1[index] = GLfloat(x);
			textureCoord1[index + 1] = GLfloat(y);
			index += 2;
		}
	}
	
	
	
	std::cout << "Done!";
}
void setShaders(){

	string vertexShaderCode = textFileRead("vertexShader.vs");
	const char* vv = vertexShaderCode.c_str();
	GLint const vertexShaderLength = vertexShaderCode.size();
	
	idVShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(idVShader, 1, &vv, NULL);
	glCompileShader(idVShader);
	//std::cout << "idVShader " << idVShader << "shader length " << vv << endl;

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
	//std::cout << "idFShader " << idFShader << "shader length " << fragmentShaderLength << endl;

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
		std::cout << "Error! Vertex getAttribLocation. Error code in_Position = \n" << (int)idAttributePosition;
	}

	const char *zCoordinateAttributeName = "in_ZCoordinate";
	idAttributeZCoordinate = (GLuint)glGetAttribLocation(idProgram, zCoordinateAttributeName);
	if (idAttributeZCoordinate == -1) {
		std::cout << "Error! Vertex getAttribLocation. in_zCoordinate Error code = \n" << (int)idAttributeZCoordinate;
	}

	/*const char *colorAttributeName = "in_Color";
	idAttributeColor = (GLuint)glGetAttribLocation(idProgram, colorAttributeName);
	if (idAttributeColor == -1) {
		cout << "Error! Fragment glGetUniformLocation.\n";

	}*/
	
	//imagine kinect
	int width, height;
	imgKinect = cv::imread("calibration\\calibration25.png", CV_LOAD_IMAGE_UNCHANGED | CV_LOAD_IMAGE_ANYDEPTH);

	cv::flip(imgKinect, imgKinect,0);
//	cv::flip(imgKinect, imgKinect,1);
	//std::cout << type2str(imgKinect.type())<<endl;
	glEnable(GL_TEXTURE_RECTANGLE_ARB);					// Turn on texturing
	glGenTextures(2, &imageTextureBufferID);				// Create an ID for a texture buffer
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, imageTextureBufferID);	// Bind that buffer so we can then fill it (in next line)
	glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RED, WIDTH, HEIGHT, 0, GL_RED, GL_UNSIGNED_SHORT, imgKinect.ptr());


	//*zCoordinate = (GLushort)imgKinect.ptr();

	imageTextureCoordID = glGetAttribLocation(idProgram, "s_vTexCoord");

	glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set the preferences
	glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	imageTextureID = glGetUniformLocation(idProgram, "texture");
	glActiveTexture(GL_TEXTURE0);				// Turn on texture unit 0
	glUniform1i(imageTextureID, 0);

	pmatrix_location = glGetUniformLocation(idProgram, "pmatrix");
	rmatrix_location = glGetUniformLocation(idProgram, "rmatrix");
	viewPort_location = glGetUniformLocation(idProgram, "viewPort");

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

void tasta(unsigned char key, int xmouse, int ymouse)
{
	switch (key){
	case 'f':
		glutFullScreen();
		break;

	default:
		break;
	}
}


void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(pmatrix_location, 1, GL_TRUE, pmatrix);
	glUniformMatrix4fv(rmatrix_location, 1, GL_TRUE, rmatrix);
	
	glUniformMatrix4fv(viewPort_location, 1, GL_FALSE, viewPort);
	glUniformMatrix4fv(projMatrix_location, 1, GL_TRUE, projectionMatrix);
	glUniformMatrix4fv(depthProjMatrix_location, 1, GL_FALSE, depthProjectionMatrix);


	
	GLuint* indexPtr = 0;
	for (unsigned int y = 1; y < HEIGHT; ++y, indexPtr += WIDTH * 2){
		glDrawElements(GL_QUAD_STRIP, WIDTH * 2, GL_UNSIGNED_INT, indexPtr);
	}

	glutSwapBuffers();
	glutPostRedisplay();
}

void cpu(){
	imgKinect = cv::imread("calibration\\calibration20.png", CV_LOAD_IMAGE_UNCHANGED | CV_LOAD_IMAGE_ANYDEPTH);

	std::ifstream image("buffer.txt");

	int index = 0;
	float *img = new float[640 * 480];
	float a,b,c;
	for (int y = 0; y < 480; y++){
		for (int x = 0; x < 640; x++){
			image >> b>>c>>a;
			img[index++] = a;
		}
	}

	cv::Mat projM = cv::Mat(4, 4, CV_32F, &projectionMatrix);
	cv::Mat depthM = cv::Mat(4, 4, CV_32F, &depthProjectionMatrix);

	

	std::ofstream f("rezultat.txt");
	std::ofstream g("bufferGenerat.txt");

	index = 0;

	for (int y = 0; y < 480; y++) {
		for (int x = 0; x < 640; x++){
			cv::Mat xyzOmogen = cv::Mat(4, 1, CV_32FC1);
			cv::Mat xyzOmogen1 = cv::Mat(4, 1, CV_32FC1);

			float zInMM = imgKinect.at<ushort>(cv::Point(x, y));
			//double xInMM = (x - WIDTH / 2.0f) * (320.0f / WIDTH) * 3.501e-3f * zInMM;
			//float yInMM = -(y - HEIGHT / 2.0f) * (240.0f / HEIGHT) * 3.501e-3f * zInMM;

			float delta = 0.0017505;


			float xInMM = x * zInMM * delta - 320 * zInMM * delta;
			float yInMM = -y * zInMM * delta + 240 * zInMM * delta;

			index++;

			xInMM /= 10;
			yInMM /= 10;
			zInMM /= 10;

			xyzOmogen.at<float>(0, 0) = xInMM;
			xyzOmogen.at<float>(1, 0) = yInMM;
			xyzOmogen.at<float>(2, 0) = -zInMM;
			xyzOmogen.at<float>(3, 0) = 1.0;

			cv::Mat depthTranspose, projectionTranspose, viewPortMatTransposed;
			cv::Mat viewPortMat = cv::Mat(4, 4, CV_32F, &viewPort);

			cv::transpose(depthM, depthTranspose);
			cv::transpose(projM, projectionTranspose);
			cv::transpose(viewPortMat, viewPortMatTransposed);


			cv::Mat UV1 = projM * xyzOmogen;
			double w = UV1.at<float>(3, 0);
			UV1 /= w;

			//UV1 = projectionTranspose * UV1;

			f << " x = " << xyzOmogen.at<float>(0, 0) << " y = " << xyzOmogen.at<float>(1, 0) << " z = " << xyzOmogen.at<float>(2, 0)
				<< " xFinal = " << UV1.at<float>(0, 0) << " yFinal = " << UV1.at<float>(1, 0) << "  factor scalare = "<< UV1.at<float>(3, 0)<< " xFinalScalat = " << UV1.at<float>(0, 0) / UV1.at<float>(3, 0)
				<< " yFinalScalat = " << UV1.at<float>(1, 0) / UV1.at<float>(3, 0) << std::endl;
				
			g << UV1.at<float>(0, 0)  << " " << UV1.at<float>(1, 0)  << std::endl;

		}
	}

	f.close();
	g.close();
}

void setOpenGL(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT);


	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitWindowSize(WIDTH, HEIGHT);	
	glutCreateWindow("Hello");

	//glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(tasta);

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glewExperimental = GL_TRUE;

	GLenum glew_status;
	glew_status = glewInit();

	if (glew_status != GLEW_OK) {
		std::cout << "GLEW error: ";
	}

	if (!GLEW_VERSION_4_0) {
		std::cout << "No support for OpenGL 4.0 found : ";
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

	glBufferData(GL_ARRAY_BUFFER, WIDTH * HEIGHT * 2 * sizeof(GLfloat)+WIDTH * HEIGHT * sizeof(GLfloat)+WIDTH * HEIGHT * 2 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, WIDTH * HEIGHT * 2 * sizeof(GLfloat), vertexPositions1);
		glBufferSubData(GL_ARRAY_BUFFER, WIDTH * HEIGHT * 2 * sizeof(GLfloat), WIDTH * HEIGHT * sizeof(GLfloat), zCoordinate);
		glBufferSubData(GL_ARRAY_BUFFER, WIDTH * HEIGHT * 2 * sizeof(GLfloat)+WIDTH * HEIGHT * sizeof(GLfloat), WIDTH * HEIGHT * 2 * sizeof(GLfloat), textureCoord1);

	glVertexAttribPointer(idAttributePosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(idAttributeZCoordinate, 1, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(WIDTH * HEIGHT * 2 * sizeof(GLfloat)));

	//load text coords
	glVertexAttribPointer(imageTextureCoordID, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(WIDTH * HEIGHT * 2 * sizeof(GLfloat)+WIDTH * HEIGHT * sizeof(GLfloat)));

	glEnableVertexAttribArray(imageTextureCoordID);
	glEnableVertexAttribArray(idAttributePosition);
	glEnableVertexAttribArray(idAttributeZCoordinate);

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
}


int main(int argc, char** argv) {

	
	cout << "\n\t1 -> OpenGL\n";
	cout << "\n\t2 -> CPU\n";
	int option;
	cin >> option;

	switch (option)
	{
	case 1:
		setOpenGL(argc, argv);
		break;
	case 2:
		cpu();
		setOpenGL(argc, argv);

		break;
	default:
		break;
	}
	

	imgKinect = cv::imread("calibration\\calibration25.png", CV_LOAD_IMAGE_UNCHANGED | CV_LOAD_IMAGE_ANYDEPTH);

	ofstream f("testBuffer.txt");
	//f << (uint)imgKinect.ptr();

	uint *v = new uint[640 * 480];
	for (int y = 0; y < 480; y++)
	{
		for (int x = 0; x < 640; x++)
		{
			ushort z = imgKinect.at<ushort>(cv::Point(x, y));
			f << "ushort z =" << z << "  uint z = " << (uint)z << endl;
		}
	}

	//v = (uint)imgKinect.data();

	return 0;

}