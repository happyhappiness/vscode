static apr_status_t cleanup_lua(void *l)
{
    lua_close((lua_State *) l);
    return APR_SUCCESS;
}