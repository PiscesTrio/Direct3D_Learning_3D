#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
using namespace	DirectX;
struct UVParameter
{
	XMFLOAT2 scale;
	XMFLOAT2 translation;
};

bool Shader_Billboard_Initialize();
void Shader_Billboard_Finalize();

void Shader_Billboard_SetMatrix(const DirectX::XMMATRIX& matrix);
void Shader_Billboard_SetWorldMatrix(const DirectX::XMMATRIX& matrix);
void Shader_Billboard_SetViewMatrix(const DirectX::XMMATRIX& matrix);
void Shader_Billboard_SetProjectMatrix(const DirectX::XMMATRIX& matrix);

void Shader_Billboard_SetColor(const DirectX::XMFLOAT4& color);

void Shader_Billboard_SetUVParameter(const UVParameter& uvParam);



void Shader_Billboard_Begin();

