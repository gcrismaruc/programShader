#version 430

#extension GL_ARB_texture_rectangle : enable

in vec3 in_Position;
//in vec4 in_Color;

uniform sampler2DRect texture;
uniform sampler2D gradient;

in vec2 s_vTexCoord;	// Coming FROM the OpenGL program
in vec2 gradient_textCoord;

uniform mat4 pmatrix;

out vec2 texCoord;		// Going TO the fragment shader

uniform mat4 projMatrix;
uniform mat4 depthProjMatrix;

//out vec4 color;

void main()
{	
	//color = in_Color;
	texCoord = s_vTexCoord;

	vec4 vertexDic = vec4(in_Position, 1.0);
	vertexDic.z = texture2DRect(texture, s_vTexCoord.xy).r;
	//texCoord = vec2(in_Position.xy);

	gl_Position =  vertexDic;
}