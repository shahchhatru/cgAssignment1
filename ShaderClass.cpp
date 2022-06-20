#include"ShaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}


Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

    //initializing a vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    //to make gpu understand the source code
    glCompileShader(vertexShader);
    //---------vertex shader---------//
     //---------fragment shader---------//
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    //to make gpu understand the fragment source code
    glCompileShader(fragmentShader);
    //---------fragment shader---------//

    //in order to use both the shader we need to ramp it up into something called as shader program
    ID = glCreateProgram();
    //to attach shader to the shader program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    //let's ramp up the shader program
    glLinkProgram(ID);
    //now we can delete the shader as they are already in the shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //---deletion completed--//
}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}