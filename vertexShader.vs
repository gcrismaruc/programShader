#version 430
#extension GL_ARB_texture_rectangle : enable

in vec2 in_Position;
in float in_ZCoordinate;

//in vec4 in_Color;

uniform sampler2DRect texture;
uniform sampler2D gradient;

in vec2 s_vTexCoord;	// Coming FROM the OpenGL program
in vec2 gradient_textCoord;

uniform mat4 pmatrix;
uniform mat4 rmatrix;

out vec2 texCoord;		// Going TO the fragment shader

uniform mat4 viewPort;
uniform mat4 projMatrix;
uniform mat4 depthProjMatrix;

out vec4 color;

void main()
{	
	texCoord = s_vTexCoord;

	float delta = 0.0017505;

	vec4 vertexDic = vec4(1.0);
	float pz = texture2DRect(texture, s_vTexCoord.xy).r;
	
	//coordonate in mm
	float z = -in_ZCoordinate;
	float x = in_Position.x * z * delta - 320 * z * delta;
	float y = -in_Position.y * z * delta + 240 * z * delta;
	
	//transform in cm
	vertexDic.x = x / 10;
	vertexDic.y = y / 10;
	vertexDic.z = z / 10;

	vec4 pos = projMatrix * vertexDic;
	
	pos.x = pos.x / pos.w;
	pos.y = -pos.y / pos.w;

	pos.z = -0.5 ;
	pos.w = 1;

	
	gl_Position = pos;
	//gl_Position =  vertexDic;
}