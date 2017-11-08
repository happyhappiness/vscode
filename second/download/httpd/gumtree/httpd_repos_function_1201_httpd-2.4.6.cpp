static int lua_ivm_set(lua_State *L) 
{
    const char *key, *raw_key;
    const char *value = NULL;
    size_t str_len;
    lua_ivm_object *object = NULL;
    request_rec *r = ap_lua_check_request_rec(L, 1);
    key = luaL_checkstring(L, 2);
    luaL_checkany(L, 3);
    raw_key = apr_pstrcat(r->pool, "lua_ivm_", key, NULL);
    
    apr_thread_mutex_lock(lua_ivm_mutex);
    apr_pool_userdata_get((void **)&object, raw_key, r->server->process->pool);
    if (!object) {
        object = apr_pcalloc(r->server->process->pool, sizeof(lua_ivm_object));
        ap_varbuf_init(r->server->process->pool, &object->vb, 2);
        object->size = 1;
        object->vb_size = 1;
    }
    object->type = lua_type(L, 3);
    if (object->type == LUA_TNUMBER) object->number = lua_tonumber(L, 3);
    else if (object->type == LUA_TBOOLEAN) object->number = lua_tonumber(L, 3);
    else if (object->type == LUA_TSTRING) {
        value = lua_tolstring(L, 3, &str_len);
        str_len++; /* add trailing \0 */
        if ( str_len > object->vb_size) {
            ap_varbuf_grow(&object->vb, str_len);
            object->vb_size = str_len;
        }
        object->size = str_len-1;
        memset(object->vb.buf, 0, str_len);
        memcpy(object->vb.buf, value, str_len-1);
    }
    apr_pool_userdata_set(object, raw_key, NULL, r->server->process->pool);
    apr_thread_mutex_unlock(lua_ivm_mutex);
    return 0;
}