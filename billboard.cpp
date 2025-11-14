#include "billboard.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include "direct3d.h"
#include "mouse.h"
#include "player_cam_tps.h"
#include "shader_billboard.h"
#include "texture.h"
using namespace DirectX;

struct VertexBBD
{
	XMFLOAT3 position; // 頂点座標
	XMFLOAT4 color;
	XMFLOAT2 uv; // uv座標
};

namespace 
{
	constexpr int NUM_VERTEX = 6;
	ID3D11Buffer* g_pVertexBuffer = nullptr; // 頂点バッファ
}

void Billboard_Initialize()
{
	Shader_Billboard_Initialize();

	VertexBBD g_BillboardVertex[]
	{
		{{-0.5f,  0.5f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},  {0.0f, 0.0f}}, // 左上
		{{ 0.5f,  0.5f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},  {1.0f, 0.0f}}, // 右上
		{{-0.5f, -0.5f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},  {0.0f, 1.0f}}, // 左下

		{{-0.5f, -0.5f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},  {0.0f, 1.0f}}, // 左下
		{{ 0.5f,  0.5f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},  {1.0f, 0.0f}}, // 右上
		{{ 0.5f, -0.5f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},  {1.0f, 1.0f}}, // 右下
	};

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;// 書き込み不可に設定
	bd.ByteWidth = sizeof(VertexBBD) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = g_BillboardVertex;

	Direct3D_GetDevice()->CreateBuffer(&bd, &sd, &g_pVertexBuffer);
}

void Billboard_Finalize()
{
	Shader_Billboard_Finalize();
	SAFE_RELEASE(g_pVertexBuffer);
}

void Billboard_Draw(int texId, const DirectX::XMFLOAT3& position, float scale_x, float scale_y, XMFLOAT2 pivot)
{
	Shader_Billboard_SetUVParameter({ { 0.2f,0.5f }, {0.2f*3,0.5f} });

	// シェーダーを描画パイプラインに設定
	Shader_Billboard_Begin();

	Shader_Billboard_SetColor({ 1.0f,1.0f,1.0f,1.0f });

	Texture_Set(texId);

	// 頂点バッファを描画パイプラインに設定
	UINT stride = sizeof(VertexBBD);
	UINT offset = 0;
	Direct3D_GetDeviceContext()->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	Direct3D_GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//頂点シェーダーにワールド座標変換行列を設定
	//回転軸までのオフセット行列
	XMMATRIX mtxOffset = XMMatrixTranslation(-pivot.x, -pivot.y, 1.0f);
	//カメラ行列の回転だけ逆行列を計算
	XMFLOAT4X4 mtxCamera = PlayerCamTps_GetViewMatrix();
	mtxCamera._41 = mtxCamera._42 = mtxCamera._43 = 0.0f; // 平行移動成分を打ち消す
	XMMATRIX invCamera = XMMatrixInverse(nullptr, XMLoadFloat4x4(&mtxCamera));

	XMMATRIX mtxS = XMMatrixScaling(scale_x, scale_y, 1.0f);
	XMMATRIX mtxT = XMMatrixTranslation(position.x + pivot.x, position.y + pivot.y, position.z);
	Shader_Billboard_SetWorldMatrix(mtxOffset * mtxS * invCamera * mtxT);

	// ポリゴン描画命令発行
	Direct3D_GetDeviceContext()->Draw(NUM_VERTEX, 0);
}
