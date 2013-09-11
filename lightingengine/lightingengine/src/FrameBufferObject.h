#pragma once
#include <iostream>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class FrameBufferObject {
public:
	FrameBufferObject(int, int);
	~FrameBufferObject();

	void draw();
	
	void bindFrameBuffer(GLenum);
	void unbindFrameBuffer(GLenum);
	void bindRenderBuffer(GLenum);
	void unbindRenderBuffer(GLenum);
	void bindTexture();
	void unbindTexture();

	bool checkStatus(GLenum);

	GLuint textureId;
	GLuint frameBufferId;
	GLuint depthBufferId;

	int width, height;
};