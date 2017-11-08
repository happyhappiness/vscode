int lua_db_get_row(lua_State *L) 
{
    int row_no,x,alpha = 0;
    const char      *entry, *rowname;
    apr_dbd_row_t   *row = 0;
    lua_db_result_set *res = lua_get_result_set(L);
    
    row_no = luaL_optinteger(L, 2, 0);
    if (lua_isboolean(L, 3)) {
        alpha = lua_toboolean(L, 3);
    }
    lua_settop(L,0);
    
    /* Fetch all rows at once? */
    
    if (row_no == 0) {
        row_no = 1;
        lua_newtable(L);
        while (apr_dbd_get_row(res->driver, res->pool, res->results,
                            &row, -1) != -1)
         {
            lua_pushinteger(L, row_no);
            lua_newtable(L);
            for (x = 0; x < res->cols; x++) {
                entry = apr_dbd_get_entry(res->driver, row, x);
                if (entry) {
                    if (alpha == 1) {
                        rowname = apr_dbd_get_name(res->driver, 
                                res->results, x);
                        lua_pushstring(L, rowname ? rowname : "(oob)");
                    }
                    else {
                        lua_pushinteger(L, x + 1);
                    }
                    lua_pushstring(L, entry);
                    lua_rawset(L, -3);
                }
            }
            lua_rawset(L, -3);
            row_no++;
        }
        return 1;
    }
    
    /* Just fetch a single row */
    if (apr_dbd_get_row(res->driver, res->pool, res->results,
                            &row, row_no) != -1)
         {
        
        lua_newtable(L);
        for (x = 0; x < res->cols; x++) {
            entry = apr_dbd_get_entry(res->driver, row, x);
            if (entry) {
                if (alpha == 1) {
                    rowname = apr_dbd_get_name(res->driver, 
                            res->results, x);
                    lua_pushstring(L, rowname ? rowname : "(oob)");
                }
                else {
                    lua_pushinteger(L, x + 1);
                }
                lua_pushstring(L, entry);
                lua_rawset(L, -3);
            }
        }
        return 1;
    }
    return 0;
}