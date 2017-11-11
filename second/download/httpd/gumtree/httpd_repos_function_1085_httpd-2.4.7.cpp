static apr_status_t cleanup_lua(void *l)
{
    AP_DEBUG_ASSERT(l != NULL);
    lua_close((lua_State *) l);
    return APR_SUCCESS;
}