int lua_db_select(lua_State *L)
{
    /*~~~~~~~~~~~~~~~~~~~~~~~*/
    lua_db_handle   *db = 0;
    apr_status_t     rc = 0;
    const char      *statement;
    request_rec     *r;
    /*~~~~~~~~~~~~~~~~~~~~~~~*/
    r = ap_lua_check_request_rec(L, 2);
    if (r) {
        luaL_checktype(L, 3, LUA_TSTRING);
        statement = lua_tostring(L, 3);
        db = lua_get_db_handle(L);
        if (db && db->alive) {

            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            int cols;
            apr_dbd_results_t   *results = 0;
            lua_db_result_set* resultset = NULL;
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

            rc = apr_dbd_select(db->driver, db->pool, db->handle,
                                &results, statement, 0);
            if (rc == APR_SUCCESS) {
                
                cols = apr_dbd_num_cols(db->driver, results);
                
                if (cols > 0) {
                    lua_newtable(L);
                    resultset = lua_newuserdata(L, sizeof(lua_db_result_set));
                    resultset->cols = cols;
                    resultset->driver = db->driver;
                    resultset->pool = db->pool;
                    resultset->rows = apr_dbd_num_tuples(db->driver, results);
                    resultset->results = results;
                    luaL_newmetatable(L, "lua_apr.dbselect");
                    lua_pushliteral(L, "__call");
                    lua_pushcfunction(L, lua_db_get_row);
                    lua_rawset(L, -3);
                    lua_setmetatable(L, -3);
                    lua_rawseti(L, -2, 0);
                    return 1;
                }
                return 0;
            }
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
        }

        lua_pushboolean(L, 0);
        return 1;
    }

    return 0;
}