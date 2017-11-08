int lua_db_query(lua_State *L)
{
    /*~~~~~~~~~~~~~~~~~~~~~~~*/
    lua_db_handle   *db = 0;
    apr_status_t     rc = 0;
    int              x = 0;
    const char      *statement;
    /*~~~~~~~~~~~~~~~~~~~~~~~*/
    luaL_checktype(L, 3, LUA_TSTRING);
    statement = lua_tostring(L, 3);
    db = lua_get_db_handle(L);
    if (db && db->alive)
        rc = apr_dbd_query(db->driver, db->handle, &x, statement);
    else {
        rc = 0;
        x = -1;
    }

    if (rc == APR_SUCCESS)
        lua_pushnumber(L, x);
    else {

        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        const char  *err = apr_dbd_error(db->driver, db->handle, rc);
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

        lua_pushnil(L);
        if (err) {
            lua_pushstring(L, err);
            return 2;
        }
    }

    return 1;
}