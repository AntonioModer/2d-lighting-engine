#include "FrameBufferObject.h"
#include "Game.h"

FrameBufferObject::FrameBufferObject(int w, int h) {
	width = w;
	height = h;

	//First create the frame buffer
	glGenFramebuffersEXT(1, &frameBufferId);
	bindFrameBuffer(GL_FRAMEBUFFER_EXT);
	//Create the depth buffer
	glGenRenderbuffersEXT(1, &depthBufferId);
	bindRenderBuffer(GL_RENDERBUFFER_EXT);
	//Allocate the depth buffer
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);
	//Attach the depth buffer to the frame buffer
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER_EXT, depthBufferId);

	//Attach a texture to the frame buffer
	glGenTextures(1, &textureId);
	bindTexture();
	//Create the actual texture with no data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
	//Attach the texture to the frame buffer
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, textureId, 0);

	//Make sure everything worked correctly
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	logFile << "Frame buffer with size " << width << "x" << height;
	if(!checkStatus(status)) {
		logFile << " NOT created succesfully\n";
	}
	else {
		logFile << " created succesfully\n";
	}

	unbindTexture();
	unbindRenderBuffer(GL_RENDERBUFFER_EXT);
	unbindFrameBuffer(GL_FRAMEBUFFER_EXT);
}

FrameBufferObject::~FrameBufferObject() {
	glDeleteTextures(1, &textureId);
	glDeleteRenderbuffersEXT(1, &depthBufferId);
	glDeleteFramebuffersEXT(1, &frameBufferId);
}

void FrameBufferObject::draw() {
	bindTexture();
	//glGenerateMipmapEXT(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glTexCoord2i(0, 0);
		glVertex2i(0, height);
		
		glTexCoord2i(1, 0);
		glVertex2i(width, height);
		
		glTexCoord2i(1, 1);
		glVertex2i(width, 0);
		
		glTexCoord2i(0, 1);
		glVertex2i(0, 0);
	glEnd();
	unbindTexture();
}

void FrameBufferObject::bindFrameBuffer(GLenum mode) {
	glBindFramebufferEXT(mode, frameBufferId);
}

void FrameBufferObject::unbindFrameBuffer(GLenum mode) {
	glBindFramebufferEXT(mode, 0);
}

void FrameBufferObject::bindRenderBuffer(GLenum mode) {
	glBindRenderbufferEXT(mode, depthBufferId);
}

void FrameBufferObject::unbindRenderBuffer(GLenum mode) {
	glBindRenderbufferEXT(mode, 0);
}

void FrameBufferObject::bindTexture() {
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void FrameBufferObject::unbindTexture() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool FrameBufferObject::checkStatus(GLenum status) {
	return status == GL_FRAMEBUFFER_COMPLETE_EXT;
}