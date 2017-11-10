int lua_db_prepared_select(lua_State *L)
{
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    lua_db_prepared_statement  *st = 0;
    apr_status_t     rc = 0;
    const char       **vars;
    int              x, have;
    /*~~~~~~~~~~~~~~~~~~~~~~~*/
    
    /* Fetch the prepared statement and the vars passed */
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_rawgeti(L, 1, 0);
    luaL_checktype(L, -1, LUA_TUSERDATA);
    st = (lua_db_prepared_statement*) lua_topointer(L, -1);
    
    /* Check if we got enough variables passed on to us.
     * This, of course, only works for prepared statements made through lua. */
    have = lua_gettop(L) - 2;
    if (st->variables != -1 && have < st->variables ) {
        lua_pushboolean(L, 0);
        lua_pushfstring(L, 
                "Error in executing prepared statement: Expected %d arguments, got %d.", 
                st->variables, have);
        return 2;
    }
    vars = apr_pcalloc(st->db->pool, have*sizeof(char *));
    for (x = 0; x < have; x++) {
        vars[x] = lua_tostring(L, x + 2);
    }

    /* Fire off the query */
    if (st->db && st->db->alive) {

        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        int cols;
        apr_dbd_results_t   *results = 0;
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

        rc = apr_dbd_pselect(st->db->driver, st->db->pool, st->db->handle,
                                &results, st->statement, 0, have, vars);
        if (rc == APR_SUCCESS) {

            /*~~~~~~~~~~~~~~~~~~~~~*/
            lua_db_result_set *resultset;
            /*~~~~~~~~~~~~~~~~~~~~~*/

            cols = apr_dbd_num_cols(st->db->driver, results);
            lua_newtable(L);
            resultset = lua_newuserdata(L, sizeof(lua_db_result_set));
            resultset->cols = cols;
            resultset->driver = st->db->driver;
            resultset->pool = st->db->pool;
            resultset->rows = apr_dbd_num_tuples(st->db->driver, results);
            resultset->results = results;
            luaL_newmetatable(L, "lua_apr.dbselect");
            lua_pushliteral(L, "__call");
            lua_pushcfunction(L, lua_db_get_row);
            lua_rawset(L, -3);
            lua_setmetatable(L, -3);
            lua_rawseti(L, -2, 0);
            return 1;
            
        }
        else {

            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            const char  *err = apr_dbd_error(st->db->driver, st->db->handle, rc);
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

            lua_pushnil(L);
            if (err) {
                lua_pushstring(L, err);
                return 2;
            }
            return 1;
        }
    }

    lua_pushboolean(L, 0);
    lua_pushliteral(L, 
            "Database connection seems to be closed, please reacquire it.");
    return (2);
}