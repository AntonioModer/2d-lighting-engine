#pragma once

#include "Polygon.h"
#include "Lighting.h"

#include "FrameBufferObject.h"

#include <vector>

class Scene {
public:
	Scene();
	~Scene();

	void tick();
	void drawLighting();
	void draw();

	std::vector<m_Polygon*> polygons;
	std::vector<Light*> lights;
	
	FrameBufferObject *fbo;
};

