int lua_db_prepared(lua_State* L) 
{
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    lua_db_handle   *db = 0;
    const char      *tag;
    request_rec     *r;
    lua_db_prepared_statement* st;
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    
    r = ap_lua_check_request_rec(L, 2);
    if (r) {
        apr_dbd_prepared_t *pstatement = NULL;
        db = lua_get_db_handle(L);
        luaL_checktype(L, 3, LUA_TSTRING);
        tag = lua_tostring(L, 3);
        
        /* Look for the statement */
        pstatement = apr_hash_get(db->dbdhandle->prepared, tag, 
                APR_HASH_KEY_STRING);
        
        if (pstatement == NULL) {
            lua_pushnil(L);
            lua_pushfstring(L, 
                    "Could not find any prepared statement called %s!", tag);
            return 2;
        }
        
        
        /* Push the prepared statement table */
        lua_newtable(L);
        st = lua_newuserdata(L, sizeof(lua_db_prepared_statement));
        st->statement = pstatement;
        st->variables = -1; /* we don't know :( */
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