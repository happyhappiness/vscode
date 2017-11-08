static apr_status_t server_cleanup_lua(void *resource)
{
    ap_lua_server_spec* spec = (ap_lua_server_spec*) resource;
    AP_DEBUG_ASSERT(spec != NULL);
    if (spec->L != NULL) {
        lua_close((lua_State *) spec->L);
    }
    return APR_SUCCESS;
}