#pragma once

#include <DirectXMath.h>

void Billboard_Initialize();
void Billboard_Finalize();

void Billboard_Draw(int texId, const DirectX::XMFLOAT3& position, float scale_x,float scale_y,DirectX::XMFLOAT2 pivot);

