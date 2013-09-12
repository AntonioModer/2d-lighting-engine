#include "Polygon.h"
#include "Game.h"

m_Polygon::m_Polygon(int numVerts) {
	verticies = new vector2f[numVerts];
	normals = new vector2f[numVerts];
	edges = new m_Edge*[numVerts];
	numVerticies = numVerts;
	resetVerticies();
}

void m_Polygon::draw() {
	glBegin(GL_POLYGON);
		for(int i=0; i < numVerticies; i++) {
			glVertex3f(verticies[i].x, verticies[i].y, 0.0f);
		}
	glEnd();
}

void m_Polygon::draw(float *colors) {
	glBegin(GL_POLYGON);
		for(int i=0; i < numVerticies; i++) {
			glColor4f(colors[i*4], colors[i*4+1], colors[i*4+2], colors[i*4+3]);
			glVertex3f(verticies[i].x, verticies[i].y, 0.0f);
		}
	glEnd();
}

void m_Polygon::drawNormals() {
	vector2f *normals = getNormals();
	glBegin(GL_LINES);
		for(int i=0; i < numVerticies; i++) {
			vector2f pos = (verticies[(i+1)%numVerticies] - verticies[i]) / 2 + verticies[i];
			glVertex2f(normals[i].x * 20 + pos.x, normals[i].y * 20 + pos.y);
			glVertex2f(pos.x, pos.y);
		}
	glEnd();
}
std::vector<m_Edge*> m_Polygon::getFacingEdges(vector2f point) {
	std::vector<m_Edge*> facing;

	for(int i=0; i < getNumVerticies(); i++) {
		vector2f towards = point - getEdge(i)->getMiddle();
		float dot = getNormal(i) * towards;
		if(dot > 0)
			facing.push_back(getEdge(i));
	}

	return facing;
}

std::vector<m_Edge*> m_Polygon::getNotFacingEdges(vector2f point) {
	std::vector<m_Edge*> notFacing;
	
	for(int i=0; i < getNumVerticies(); i++) {
		vector2f towards = point - getEdge(i)->getMiddle();
		float dot = getNormal(i) * towards;
		if(dot <= 0)
			notFacing.push_back(getEdge(i));
	}

	return notFacing;
}

void m_Polygon::resetVerticies() {
	for(int i=0; i < numVerticies; i++) {
		verticies[i] = vector2f();
	}
	clockwise = false;
}

void m_Polygon::updateAll() {
	updateNormals();
	updateClockwise();
	updateEdges();
}

void m_Polygon::updateNormals() {
	for(int i=0; i < numVerticies; i++) {
		vector2f diff = getVertex(i) - getVertex(i + 1);
		float temp = diff.x;
		diff.x = diff.y;
		diff.y = -temp;
		if(!isClockwise()) diff *= -1;
		normals[i] = diff.normalized();
	}
}


void m_Polygon::updateClockwise() {
	double sum = 0;
	for(int i=0; i < numVerticies - 1; i++) {
		sum += (getVertex(i + 1).x - getVertex(i).x) * (getVertex(i + 1).y + getVertex(i).y);
	}
	clockwise = sum > 0;
}

void m_Polygon::updateEdges() {
	for(int i=0; i < numVerticies; i++) {
		edges[i] = new m_Edge(getVertex(i), getVertex(i+1));
	}
}