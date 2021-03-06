#include "LuaHelper.h"

#include <iostream>

using namespace std;


Lua_Helper::Lua_Helper() {
    state = luaL_newstate();

    // Load all LUA libraries
    luaL_openlibs(state);
}

/* To report errors */
bool Lua_Helper::report_errors(int status) {
    if(status != 0) {
        // Tell user if there is an error message
        cerr << "-- " << lua_tostring(this->state, -1) << endl;
        // Pop value from stack
        lua_pop(this->state, 1);

        return true;
    }
    return false;
}

template<>
bool Lua_Helper::lua_get<bool>() {
    return (bool) lua_toboolean(this->state, -1);
}

template<>
int Lua_Helper::lua_get<int>() {
    if(lua_isnumber(this->state, -1))
        return (int) lua_tonumber(this->state, -1);
    else
        return (int) NULL;
}

template<>
double Lua_Helper::lua_get<double>() {
    if(lua_isnumber(this->state, -1))
        return (double) lua_tonumber(this->state, -1);
    else
        return (double) NULL;
}

template<>
char* Lua_Helper::lua_get<char*>() {
    if(lua_isstring(this->state, -1))
        return (char*) lua_tostring(this->state, -1);
    else
        return NULL;
}

void Lua_Helper::close() {
    lua_close(this->state);
}

