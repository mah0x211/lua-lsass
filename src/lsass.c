/*
 *  Copyright 2015 Masatoshi Teruya. All rights reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a 
 *  copy of this software and associated documentation files (the "Software"), 
 *  to deal in the Software without restriction, including without limitation 
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 *  and/or sell copies of the Software, and to permit persons to whom the 
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL 
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 *  DEALINGS IN THE SOFTWARE.
 *
 *  lsass.c
 *  lua-lsass
 *
 *  Created by Masatoshi Teruya on 15/09/16.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <lua.h>
#include <lauxlib.h>
// libsass headers
#include "sass.h"


#define MODULE_MT   "lsass"


// helper macros
#define lstate_setmetatable(L,tname) do{ \
    luaL_getmetatable( L, tname ); \
    lua_setmetatable( L, -2 ); \
}while(0)


#define lstate_fn2tbl(L,k,v) do{ \
    lua_pushstring(L,k); \
    lua_pushcfunction(L,v); \
    lua_rawset(L,-3); \
}while(0)


#define lstate_num2tbl(L,k,v) do{ \
    lua_pushstring(L,k); \
    lua_pushnumber(L,v); \
    lua_rawset(L,-3); \
}while(0)


#define lstate_str2tbl(L,k,v,vl) do{ \
    lua_pushstring(L,k); \
    lua_pushstring(L,v,vl); \
    lua_rawset(L,-3); \
}while(0)


#define lstate_strl2tbl(L,k,v,vl) do{ \
    lua_pushstring(L,k); \
    lua_pushlstring(L,v,vl); \
    lua_rawset(L,-3); \
}while(0)

#define lstate_strll2tbl(L,k,kl,v,vl) do{ \
    lua_pushlstring(L,k,kl); \
    lua_pushlstring(L,v,vl); \
    lua_rawset(L,-3); \
}while(0)


static int version_lua( lua_State *L )
{
    lua_pushstring( L, libsass_version() );
    return 1;
}


LUALIB_API int luaopen_lsass( lua_State *L )
{
    
    // register allocator
    lua_createtable( L, 0, 1 );
    lstate_fn2tbl( L, "version", version_lua );

    return 1;
}


