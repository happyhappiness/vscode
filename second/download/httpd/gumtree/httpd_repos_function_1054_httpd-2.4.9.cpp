static int apl_toscope(const char *name)
{
    if (0 == strcmp("once", name))
        return AP_LUA_SCOPE_ONCE;
    if (0 == strcmp("request", name))
        return AP_LUA_SCOPE_REQUEST;
    if (0 == strcmp("connection", name))
        return AP_LUA_SCOPE_CONN;
    if (0 == strcmp("conn", name))
        return AP_LUA_SCOPE_CONN;
    if (0 == strcmp("thread", name))
        return AP_LUA_SCOPE_THREAD;
    return AP_LUA_SCOPE_ONCE;
}