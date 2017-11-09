int lua_db_gc(lua_State *L)
{
    /*~~~~~~~~~~~~~~~~*/
    lua_db_handle    *db;
    /*~~~~~~~~~~~~~~~~~~~~*/

    db = lua_touserdata(L, 1);
    if (db && db->alive) {
        if (db->type == LUA_DBTYPE_APR_DBD) {
            apr_dbd_close(db->driver, db->handle);
            if (db->pool) apr_pool_destroy(db->pool);
        }
        else {
            lua_ap_dbd_close = APR_RETRIEVE_OPTIONAL_FN(ap_dbd_close);
            if (lua_ap_dbd_close != NULL)
                if (db->dbdhandle) lua_ap_dbd_close(db->server, db->dbdhandle);
        }
        db->driver = NULL;
        db->handle = NULL;
        db->alive = 0;
        db->pool = NULL;
    }
    lua_settop(L, 0);
    return 0;
}