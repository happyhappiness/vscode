int lua_db_active(lua_State *L)
{
    /*~~~~~~~~~~~~~~~~~~~~*/
    lua_db_handle   *db = 0;
    apr_status_t     rc = 0;
    /*~~~~~~~~~~~~~~~~~~~~*/

    db = lua_get_db_handle(L);
    if (db && db->alive) {
        rc = apr_dbd_check_conn(db->driver, db->pool, db->handle);
        if (rc == APR_SUCCESS) {
            lua_pushboolean(L, 1);
            return 1;
        }
    }

    lua_pushboolean(L, 0);
    return 1;
}