#include "Lighting.h"
#include "Game.h"

Light::Light(vector2f p, float rad, float i) {
	init();
	pos = p;
	radius = rad;
	intensity = i;
	red = p.x / 800;
	green = p.y / 600;
	blue = (p.x * p.y) / (800 * 600);
}

Light::Light(vector2f p, float rad, float i, float r, float g, float b) {
	init();
	pos = p;
	radius = rad;
	intensity = i;
	red = r;
	green = g;
	blue = b;
}

void Light::init() {
	pos = vector2f();
	radius = 0;
	intensity = 1.0f;
	red = 0;
	green = 0;
	blue = 0;
	castShadows = true;
}

void Light::tick() {

}

void Light::draw(Scene *scene) {
	float outerDepth = 0.0f;
	float innerDepth = 0.0f;
	//The outer area of the light
	glBegin(GL_TRIANGLE_FAN);
		glColor4f(red, green, blue, intensity);
		glVertex3f(pos.x, pos.y, outerDepth);
		glColor4f(red, green, blue, 0.0f);
		for(int i=0; i <= NUM_POINTS; i++) {
			float angle = i * 2 * M_PI / NUM_POINTS;
			glVertex3f(pos.x + (cos(angle) * radius), pos.y + (sin(angle) * radius), outerDepth);
		}
	glEnd();
}

void Light::drawAlpha(Scene *scene) {
	glBegin(GL_TRIANGLE_FAN);
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glVertex2f(pos.x, pos.y);
		glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
		for(int i=0; i <= NUM_POINTS; i++) {
			float angle = i * 2 * M_PI / NUM_POINTS;
			glVertex3f(pos.x + (cos(angle) * radius), pos.y + (sin(angle) * radius), 0.0f);
		}
	glEnd();
	if(castShadows)
		drawShadows(scene);
}

void Light::drawShadows(Scene *scene) {
	for(int i=0; i < scene->polygons.size(); i++) {
		std::vector<m_Edge*> away = scene->polygons[i]->getNotFacingEdges(pos);

		glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		for(int j=0; j < away.size(); j++) {
			//First point
			vector2f towards = away[j]->p1 - pos;
			towards.normalize();
			towards *= 1000;
			glVertex2f(away[j]->p1.x + towards.x, away[j]->p1.y + towards.y);
			glVertex2f(away[j]->p1.x, away[j]->p1.y);

			//Second point
			towards = away[j]->p2 - pos;
			towards.normalize();
			towards *= 1000;
			glVertex2f(away[j]->p2.x, away[j]->p2.y);
			glVertex2f(away[j]->p2.x + towards.x, away[j]->p2.y + towards.y);
		}
		glEnd();
	}
}