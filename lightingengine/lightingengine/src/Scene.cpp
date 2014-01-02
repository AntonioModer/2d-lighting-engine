#include "Scene.h"
#include "Game.h"

Scene::Scene() {
	m_Polygon *poly = new m_Polygon(5);
	poly->setVertex(0, vector2f(100, 100));
	poly->setVertex(1, vector2f(100, 200));
	poly->setVertex(2, vector2f(200, 200));
	poly->setVertex(3, vector2f(250, 150));
	poly->setVertex(4, vector2f(200, 100));
	polygons.push_back(poly);
	poly = new m_Polygon(3);
	poly->setVertex(0, vector2f(300, 300));
	poly->setVertex(1, vector2f(400, 300));
	poly->setVertex(2, vector2f(400, 400));
	//poly->setVertex(3, vector2f(450, 350));
	polygons.push_back(poly);

	//Create the lighting alpha texture
	//http://www.opengl.org/wiki/Framebuffer_Object_Examples

	fbo = new FrameBufferObject(800, 600, 2);
	
	Light *l = new Light(vector2f(800, 600), 400, .6f);
	lights.push_back(l);
}

Scene::~Scene() {
	delete fbo;
}

void Scene::tick() {
	int mx, my;
	Uint32 mouse = SDL_GetMouseState(&mx, &my);
	//When the mouse is clicked add a light
	if((mouse & SDL_BUTTON_LEFT) && !(lastMouseState & SDL_BUTTON_LEFT)) {
		lights.push_back(new Light(vector2f(mx, my), 400, .8f));
	}
	//Control the top light
	if(lights.size() > 0)
		lights[lights.size()-1]->pos = vector2f(mx, my);
	for(int i=0; i < lights.size(); i++) {
		lights[i]->tick();
	}
}

void Scene::drawLighting() {
	//Set up the main fbo
	fbo->bindFrameBuffer(GL_FRAMEBUFFER_EXT);
	glPushAttrib(GL_VIEWPORT_BIT | GL_COLOR_BUFFER_BIT);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glViewport(0, 0, fbo->width, fbo->height);
	
	//Draw each light to a secondary texture, then draw that one to the primary
	for(int i=0; i < lights.size(); i++) {
		//Draw to secondary texture
		fbo->setRenderToTexture(1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ZERO);

		//Draw the light alpha
		glColorMask(false, false, false, true);
		lights[i]->drawAlpha(this);

		//Draw the light color
		glColorMask(true, true, true, false);
		lights[i]->draw(this);

		glColorMask(true, true, true, true);

		//Draw second texture to the first one
		fbo->setRenderToTexture(0);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);
		fbo->draw(1);
	}
	fbo->unsetRenderToTexture();
	fbo->unbindFrameBuffer(GL_FRAMEBUFFER_EXT);
	glPopAttrib();
}

void Scene::draw() {
	drawLighting();

	//Draw the scene objects
	fbo->bindFrameBuffer(GL_FRAMEBUFFER_EXT);
	fbo->setRenderToTexture(0);
	glPushAttrib(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_DST_COLOR, GL_DST_ALPHA); //Blends the scene objects very nicely with the color of the light

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for(int i=0; i < polygons.size(); i++) {
		float cols[] = { 1.0f, 0.0f, .5f, 1.0f,
						 1.0f, 1.0f, .5f, 1.0f,
						 0.0f, 1.0f, 1.0f, 1.0f,
						 1.0f, 0.0f, .5f, 1.0f,
						 1.0f, 0.0f, .5f, 1.0f };
		polygons[i]->draw(cols);
	}	

	glPopAttrib();
	fbo->unbindFrameBuffer(GL_FRAMEBUFFER_EXT);

	fbo->draw(0);
}