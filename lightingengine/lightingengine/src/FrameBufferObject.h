#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

class FrameBufferObject {
public:
	FrameBufferObject(int, int, int=1);
	~FrameBufferObject();

	void draw(int=0);
	
	void bindFrameBuffer(GLenum);
	void unbindFrameBuffer(GLenum);
	void bindRenderBuffer(GLenum);
	void unbindRenderBuffer(GLenum);
	void bindTexture(int=0);
	void unbindTexture();
	void setRenderToTexture(int=0);
	void unsetRenderToTexture();

	bool checkStatus(GLenum);

	std::vector<GLuint> textures;
	GLuint frameBufferId;
	GLuint depthBufferId;

	int width, height;
};