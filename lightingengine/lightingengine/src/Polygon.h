#pragma once

#include "Vector2.h"

#include <vector>

class m_Edge {
public:
	m_Edge() { p1 = vector2f(); p2 = vector2f(); }
	m_Edge(vector2f np1, vector2f np2) { p1 = np1; p2 = np2; }

	vector2f getMiddle() { return (p2 - p1) / 2 + p1; }

	vector2f p1, p2;
};

class m_Polygon {
public:
	m_Polygon(int);
	
	void draw();
	void draw(float*);
	void drawNormals();
	
	std::vector<m_Edge*> getFacingEdges(vector2f);
	std::vector<m_Edge*> getNotFacingEdges(vector2f);
	
	//This should be the only way that you modify verticies (bypassing this method will screw things up)
	void setVertex(int i, vector2f v) { verticies[i % getNumVerticies()] = v; updateAll(); }
	//
	vector2f getVertex(int i) { return verticies[i % getNumVerticies()]; }
	vector2f *getVerticies() { return verticies; }

	vector2f* getNormals() { return normals; }
	vector2f getNormal(int i) { return normals[i % getNumVerticies()]; }

	m_Edge** getEdges() { return edges; }
	m_Edge* getEdge(int i) { return edges[i % getNumVerticies()]; }

	bool isClockwise() { return clockwise; }

	int getNumVerticies() { return numVerticies; }

protected:
	//Reset (or initialize) all the verticies to (0, 0)
	void resetVerticies();

	//Update everything
	void updateAll();
	//Update the clockwise variable
	void updateClockwise();
	//Update the normal vectors
	void updateNormals();
	//Update the edges
	void updateEdges();

	int numVerticies;

private:
	vector2f *verticies;
	
	bool clockwise;
	vector2f *normals;
	m_Edge **edges;
};

class m_Pentagon : public m_Polygon {
public:
	m_Pentagon() : m_Polygon(5) { }
};

class m_Quad : public m_Polygon {
public:
	m_Quad() : m_Polygon(4) { }
};

class m_Triangle : public m_Polygon {
public:
	m_Triangle() : m_Polygon(3) { }
};