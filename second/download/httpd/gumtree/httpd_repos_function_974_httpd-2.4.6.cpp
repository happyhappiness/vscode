int lua_db_prepare(lua_State* L) 
{
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    lua_db_handle   *db = 0;
    apr_status_t     rc = 0;
    const char      *statement, *at;
    request_rec     *r;
    lua_db_prepared_statement* st;
    int need = 0;
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    
    r = ap_lua_check_request_rec(L, 2);
    if (r) {
        apr_dbd_prepared_t *pstatement = NULL;
        luaL_checktype(L, 3, LUA_TSTRING);
        statement = lua_tostring(L, 3);
        
        /* Count number of variables in statement */
        at = ap_strchr_c(statement,'%');
        while (at != NULL) {
            if (at[1] == '%') {
                at++;
            }
            else {
                need++;
            }
            at = ap_strchr_c(at+1,'%');
        }
        
        
        db = lua_get_db_handle(L);
        rc = apr_dbd_prepare(db->driver, r->pool, db->handle, statement, 
                    NULL, &pstatement);
        if (rc != APR_SUCCESS) {
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            const char  *err = apr_dbd_error(db->driver, db->handle, rc);
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

            lua_pushnil(L);
            if (err) {
                lua_pushstring(L, err);
                return 2;
            }
            return 1;
        }
        
        /* Push the prepared statement table */
        lua_newtable(L);
        st = lua_newuserdata(L, sizeof(lua_db_prepared_statement));
        st->statement = pstatement;
        st->variables = need;
        st->db = db;
        
        lua_pushliteral(L, "select");
        lua_pushcfunction(L, lua_db_prepared_select);
        lua_rawset(L, -4);
        lua_pushliteral(L, "query");
        lua_pushcfunction(L, lua_db_prepared_query);
        lua_rawset(L, -4);
        lua_rawseti(L, -2, 0);
        return 1;
    }
    return 0;
}