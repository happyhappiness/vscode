int lua_db_escape(lua_State *L)
{
    /*~~~~~~~~~~~~~~~~~~~~~*/
    lua_db_handle    *db = 0;
    const char       *statement;
    const char       *escaped = 0;
    request_rec      *r;
    /*~~~~~~~~~~~~~~~~~~~~~*/

    r = ap_lua_check_request_rec(L, 2);
    if (r) {
        luaL_checktype(L, 3, LUA_TSTRING);
        statement = lua_tostring(L, 3);
        db = lua_get_db_handle(L);
        if (db && db->alive) {
            apr_dbd_init(r->pool);
            escaped = apr_dbd_escape(db->driver, r->pool, statement,
                                     db->handle);
            if (escaped) {
                lua_pushstring(L, escaped);
                return 1;
            }
        }
        else {
            lua_pushnil(L);
        }
        return (1);
    }

    return 0;
}