static lua_db_handle* lua_push_db_handle(lua_State *L, request_rec* r, int type,
        apr_pool_t* pool) 
{
    lua_db_handle* db;
    lua_newtable(L);
    db = lua_newuserdata(L, sizeof(lua_db_handle));
    db->alive = 1;
    db->pool = pool;
    db->type = type;
    db->dbdhandle = 0;
    db->server = r->server;
    luaL_newmetatable(L, "lua_apr.dbacquire");
    lua_pushliteral(L, "__gc");
    lua_pushcfunction(L, lua_db_gc);
    lua_rawset(L, -3);
    lua_setmetatable(L, -2);
    lua_rawseti(L, -2, 0);
    
    lua_pushliteral(L, "escape");
    lua_pushcfunction(L, lua_db_escape);
    lua_rawset(L, -3);
    
    lua_pushliteral(L, "close");
    lua_pushcfunction(L, lua_db_close);
    lua_rawset(L, -3);
    
    lua_pushliteral(L, "select");
    lua_pushcfunction(L, lua_db_select);
    lua_rawset(L, -3);
    
    lua_pushliteral(L, "query");
    lua_pushcfunction(L, lua_db_query);
    lua_rawset(L, -3);
    
    lua_pushliteral(L, "active");
    lua_pushcfunction(L, lua_db_active);
    lua_rawset(L, -3);
    
    lua_pushliteral(L, "prepare");
    lua_pushcfunction(L, lua_db_prepare);
    lua_rawset(L, -3);
    
    lua_pushliteral(L, "prepared");
    lua_pushcfunction(L, lua_db_prepared);
    lua_rawset(L, -3);
    return db;
}