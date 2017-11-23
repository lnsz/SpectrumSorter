#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
{
}

GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string& vertexShader, const std::string& fragmentShader) {
	_programID = glCreateProgram();

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		fatalError("Vertex shader failed to be created");
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) {
		fatalError("Fragment shader failed to be created");
	}

	compile(vertexShader, _vertexShaderID);
	compile(fragmentShader, _fragmentShaderID);

	linkShaders();
}

void GLSLProgram::addAttribute(const std::string& attributeName) {
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

void GLSLProgram::use() {
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse() {
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::linkShaders() {
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.

	//Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		//Use the errorLog as you see fit.
		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shaders failed to link");

		//In this simple program, we'll just leave
		return;
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
}

void GLSLProgram::compile(const std::string& filePath, GLuint id) {
	//Read our shaders into the appropriate buffers
	std::ifstream file(filePath);
	if (file.fail()) {
		fatalError("Failed to open " + filePath);
	}

	std::string fileContent = "";
	std::string line;
	while (std::getline(file, line)) {
		fileContent += line + "\n";
	}
	file.close();

	//Send the shader source code to GL
	//Note that std::string's .c_str is NULL character terminated.
	const char* contentsPtr = fileContent.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	//Compile the shader
	glCompileShader(id);

	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shader " + filePath + " failed to compile");
	}
}