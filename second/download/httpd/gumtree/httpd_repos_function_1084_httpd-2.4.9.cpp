static apr_status_t server_vm_construct(lua_State **resource, void *params, apr_pool_t *pool)
{
    lua_State* L;
    ap_lua_server_spec* spec = apr_pcalloc(pool, sizeof(ap_lua_server_spec));
    *resource = NULL;
    if (vm_construct(&L, params, pool) == APR_SUCCESS) {
        spec->finfo = apr_pcalloc(pool, sizeof(ap_lua_finfo));
        if (L != NULL) {
            spec->L = L;
            *resource = (void*) spec;
            lua_pushlightuserdata(L, spec);
            lua_setfield(L, LUA_REGISTRYINDEX, "Apache2.Lua.server_spec");
            return APR_SUCCESS;
        }
    }
    return APR_EGENERAL;
}