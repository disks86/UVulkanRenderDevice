#version 460
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable
#extension GL_EXT_scalar_block_layout : enable

layout (location = 0) in vec3 positionIn;
layout (location = 1) in vec4 color1In;
layout (location = 2) in vec2 texcoord1In;

layout (location = 0) out vec4 color1Out;
layout (location = 1) out vec2 texcoord1Out;

out gl_PerVertex 
{
        vec4 gl_Position;
};

struct VertexGlobalConstants
{
	mat4 ProjectionMatrix;
	vec2 XAxis;
	vec2 UDot;
	vec2 YAxis;
	vec2 VDot;
	float Upan1;
	float VPan1;
	float UMult1;
	float VMult1;
	float Upan2;
	float VPan2;
	float UMult2;
	float VMult2;
	float Upan3;
	float VPan3;
	float UMult3;
	float VMult3;
	float Upan4;
	float VPan4;
	float UMult4;
	float VMult4;
};

layout(std430,binding = 0) uniform RenderStateBlock
{
	VertexGlobalConstants globalConstants;
};

void main() 
{
	texcoord1Out = texcoord1In;
	color1Out = color1In;
	gl_Position = vec4(positionIn.xyz,1.0) * globalConstants.ProjectionMatrix;
}