#version 460
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable
#extension GL_EXT_scalar_block_layout : enable

layout (location = 0) in vec4 color1In;
layout (location = 1) in vec2 texcoord1In;

layout (location = 0) out vec4 uFragColor;

struct GlobalConstants
{
	float AlphaTestLevel;
	float Unused1;
	float Unused2;
	float LightmapBlendScaleFactor;
};

layout(std430,binding = 0) uniform RenderStateBlock
{
	GlobalConstants globalConstants;
};


layout(binding = 1) uniform sampler2D textures[4];

void main() 
{
	uFragColor = texture(textures[0],texcoord1In);
	uFragColor = uFragColor * color1In;

	if((uFragColor.a - globalConstants.AlphaTestLevel)<0)
	{
		discard; 
	}
}