#include "map.h"

#include <DirectXMath.h>

#include "cube.h"
#include "model.h"
using namespace DirectX;



namespace 
{
	MapObject g_MapObjects[]
	{
		{1,{ 0.0f,0.5f,0.0f}},
		{1,{ 1.0f,0.5f,0.0f}},
		{1,{-1.0f,0.5f,0.0f}},
		{1,{ 0.0f,0.5f,1.0f}},
		{1,{ 1.0f,0.5f,1.0f}},
		{1,{-1.0f,0.5f,1.0f}},
		{1,{ 0.0f,0.5f,2.0f}},
		{1,{ 1.0f,0.5f,2.0f}},
		{1,{-1.0f,0.5f,2.0f}},

	};
}

void Map_Initialize()
{
	for (MapObject& o : g_MapObjects)
	{
		o.aabb = Cube_GetAABB(o.position);
	}
}

void Map_Finalize()
{
}

int Map_ObjCount()
{
	return std::size(g_MapObjects);
}

const MapObject* Map_GetObjects()
{
	return g_MapObjects;
}

const MapObject* Map_GetObject(int index)
{
	return &g_MapObjects[index];
}

void Map_Draw()
{
	XMMATRIX mtxWorld ;

	for (const auto& obj : g_MapObjects)
	{
		switch (obj.categoryId)
		{
		case 1:
			 mtxWorld = XMMatrixTranslation(
				obj.position.x,
				obj.position.y,
				obj.position.z
			);
			Cube_Draw(mtxWorld);
			break;
		default:
			break;
		}
	}
}
