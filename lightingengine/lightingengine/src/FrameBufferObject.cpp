#include "FrameBufferObject.h"
#include "Game.h"

FrameBufferObject::FrameBufferObject(int w, int h, int numTextures) {
	width = w;
	height = h;
	assert(numTextures > 0 && numTextures < GL_MAX_COLOR_ATTACHMENTS_EXT);
	textures = std::vector<GLuint>(numTextures);

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

	//Make textures
	for(int i=0; i < numTextures; i++) {
		//Attach a texture to the frame buffer
		glGenTextures(1, &textures[i]);
		bindTexture(i);
		//Create the actual texture with no data
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
		//Attach the texture to the frame buffer
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + i, GL_TEXTURE_2D, textures[i], 0);
		unbindTexture();
	}

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
	glDeleteTextures(textures.size(), &textures[0]);
	glDeleteRenderbuffersEXT(1, &depthBufferId);
	glDeleteFramebuffersEXT(1, &frameBufferId);
}

void FrameBufferObject::draw(int id) {
	bindTexture(id);

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

void FrameBufferObject::bindTexture(int id) {
	assert(id >= 0 && id < textures.size());
	glBindTexture(GL_TEXTURE_2D, textures[id]);
}

void FrameBufferObject::unbindTexture() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FrameBufferObject::setRenderToTexture(int id) {
	assert(id >= 0 && id < textures.size());
	GLenum bufs[] = {GL_COLOR_ATTACHMENT0_EXT + id};
	glDrawBuffers(1, bufs);
}

void FrameBufferObject::unsetRenderToTexture() {
	std::vector<GLenum> bufs(textures.size());
	for(int i=0; i < bufs.size(); i++) {
		bufs[i] = GL_COLOR_ATTACHMENT0_EXT + i;
	}
	glDrawBuffers(bufs.size(), &bufs[0]);
}

bool FrameBufferObject::checkStatus(GLenum status) {
	return status == GL_FRAMEBUFFER_COMPLETE_EXT;
}