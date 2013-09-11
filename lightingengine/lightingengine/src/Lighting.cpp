#include "Lighting.h"
#include "Game.h"

Light::Light(vector2f p, float rad) {
	pos = p;
	radius = rad;
	red = p.x / 800;
	green = p.y / 600;
	blue = (p.x * p.y) / (800 * 600);
}

Light::Light(vector2f p, float rad, float r, float g, float b) {
	pos = p;
	radius = rad;
	red = r;
	green = g;
	blue = b;
}

void Light::tick() {

}

void Light::draw(Scene *scene) {
	float outerDepth = 0.0f;
	float innerDepth = 0.0f;
	//The outer area of the light
	glBegin(GL_TRIANGLE_FAN);
		glColor4f(red, green, blue, 1.0f);
		glVertex3f(pos.x, pos.y, outerDepth);
		glColor4f(red, green, blue, 0.0f);
		for(int i=0; i <= NUM_POINTS; i++) {
			float angle = i * 2 * M_PI / NUM_POINTS;
			glVertex3f(pos.x + (cos(angle) * radius), pos.y + (sin(angle) * radius), outerDepth);
		}
	glEnd();
	//Draw the inner area of the light
	/*
	glBegin(GL_TRIANGLE_FAN);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		//glVertex3f(pos.x, pos.y, innerDepth);
		glColor4f(red, green, blue, 0.0f);
		for(int i=0; i <= NUM_POINTS; i++) {
			float angle = i * 2 * M_PI / NUM_POINTS;
			glVertex3f(pos.x + (cos(angle) * (radius / 8)), pos.y + (sin(angle) * (radius / 8)), innerDepth);
		}
	glEnd();
	*/
	//drawShadows(scene);
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