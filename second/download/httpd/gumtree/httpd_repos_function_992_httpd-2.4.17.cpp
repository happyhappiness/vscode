int lua_db_acquire(lua_State *L)
{
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    const char      *type;
    const char      *arguments;
    const char      *error = 0;
    request_rec     *r;
    lua_db_handle   *db = 0;
    apr_status_t     rc = 0;
    ap_dbd_t        *dbdhandle = NULL;
    apr_pool_t      *pool = NULL;
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    r = ap_lua_check_request_rec(L, 1);
    if (r) {
        type = luaL_optstring(L, 2, "mod_dbd"); /* Defaults to mod_dbd */
        
        if (!strcmp(type, "mod_dbd")) {

            lua_settop(L, 0);
            lua_ap_dbd_open = APR_RETRIEVE_OPTIONAL_FN(ap_dbd_open);
            if (lua_ap_dbd_open)
                dbdhandle = (ap_dbd_t *) lua_ap_dbd_open(
                        r->server->process->pool, r->server);

            if (dbdhandle) {
                db = lua_push_db_handle(L, r, LUA_DBTYPE_MOD_DBD, dbdhandle->pool);
                db->driver = dbdhandle->driver;
                db->handle = dbdhandle->handle;
                db->dbdhandle = dbdhandle;
                return 1;
            }
            else {
                lua_pushnil(L);
                if ( lua_ap_dbd_open == NULL )
                    lua_pushliteral(L,
                                    "mod_dbd doesn't seem to have been loaded.");
                else
                    lua_pushliteral(
                        L,
                        "Could not acquire connection from mod_dbd. If your database is running, this may indicate a permission problem.");
                return 2;
            }
        }
        else {
            rc = apr_pool_create(&pool, NULL);
            if (rc != APR_SUCCESS) {
                lua_pushnil(L);
                lua_pushliteral(L, "Could not allocate memory for database!");
                return 2;
            }
            apr_pool_tag(pool, "lua_dbd_pool");
            apr_dbd_init(pool);
            dbdhandle = apr_pcalloc(pool, sizeof(ap_dbd_t));
            rc = apr_dbd_get_driver(pool, type, &dbdhandle->driver);
            if (rc == APR_SUCCESS) {
                luaL_checktype(L, 3, LUA_TSTRING);
                arguments = lua_tostring(L, 3);
                lua_settop(L, 0);
                
                if (strlen(arguments)) {
                    rc = apr_dbd_open_ex(dbdhandle->driver, pool, 
                            arguments, &dbdhandle->handle, &error);
                    if (rc == APR_SUCCESS) {
                        db = lua_push_db_handle(L, r, LUA_DBTYPE_APR_DBD, pool);
                        db->driver = dbdhandle->driver;
                        db->handle = dbdhandle->handle;
                        db->dbdhandle = dbdhandle;
                        return 1;
                    }
                    else {
                        lua_pushnil(L);
                        if (error) {
                            lua_pushstring(L, error);
                            return 2;
                        }

                        return 1;
                    }
                }

                lua_pushnil(L);
                lua_pushliteral(L,
                                "No database connection string was specified.");
                apr_pool_destroy(pool);
                return (2);
            }
            else {
                lua_pushnil(L);
                if (APR_STATUS_IS_ENOTIMPL(rc)) {
                    lua_pushfstring(L, 
                         "driver for %s not available", type);
                }
                else if (APR_STATUS_IS_EDSOOPEN(rc)) {
                    lua_pushfstring(L, 
                                "can't find driver for %s", type);
                }
                else if (APR_STATUS_IS_ESYMNOTFOUND(rc)) {
                    lua_pushfstring(L, 
                                "driver for %s is invalid or corrupted",
                                type);
                }
                else {
                    lua_pushliteral(L, 
                                "mod_lua not compatible with APR in get_driver");
                }
                lua_pushinteger(L, r