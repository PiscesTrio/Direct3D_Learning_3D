#pragma once
#ifndef MAP_H
#define MAP_H
#include <DirectXMath.h>

#include "collision.h"

struct MapObject
{
	int categoryId;
	DirectX::XMFLOAT3 position;
	AABB aabb;
};

void Map_Initialize();
void Map_Finalize();
int Map_ObjCount();
const MapObject* Map_GetObjects();
const MapObject* Map_GetObject(int index);

void Map_Draw();

#endif
