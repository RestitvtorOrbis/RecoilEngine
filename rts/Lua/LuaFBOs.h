/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef LUA_FBOS_H
#define LUA_FBOS_H

#include <vector>
#include <string>

#include "Rendering/GL/myGL.h"

struct lua_State;


class LuaFBOs {
public:
	LuaFBOs() { fbos.reserve(8); }
	~LuaFBOs();

	void Clear() { fbos.clear(); }

	struct LuaFBO {
		void Init(lua_State* L);
		void Free(lua_State* L);

		GLuint index; // into LuaFBOs::fbos
		GLuint id;
		GLenum target;
		int luaRef;
		GLsizei xsize;
		GLsizei ysize;
		GLsizei zsize;
	};

	const LuaFBO* GetLuaFBO(lua_State* L, int index);

public:
	static bool PushEntries(lua_State* L);
public:
	static void AttachObjectTexTarget(
		const char* funcName,
		GLenum fboTarget,
		GLenum texTarget,
		GLuint texId,
		GLenum attachID,
		GLenum attachLevel
	);
private:
	std::vector<LuaFBO*> fbos;

private: // helpers
	static bool CreateMetatable(lua_State* L);
	static bool AttachObject(
		const char* funcName,
		lua_State* L, int index,
		LuaFBO* fbo, GLenum attachID,
		GLenum attachTarget = 0,
		GLenum attachLevel  = 0
	);
	static bool ApplyAttachment(lua_State* L, int index,
	                            LuaFBO* fbo, GLenum attachID);
	static bool ApplyDrawBuffers(lua_State* L, int index);

private: // metatable methods
	static int meta_gc(lua_State* L);
	static int meta_index(lua_State* L);
	static int meta_newindex(lua_State* L);

private: // call-outs
	static int CreateFBO(lua_State* L);
	static int DeleteFBO(lua_State* L);
	static int IsValidFBO(lua_State* L);
	static int ActiveFBO(lua_State* L);
	static int RawBindFBO(lua_State* L); // unsafe
	static int BlitFBO(lua_State* L);
	static int ClearAttachmentFBO(lua_State* L);
};


#endif /* LUA_FBOS_H */
