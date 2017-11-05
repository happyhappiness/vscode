static int apl_toscope(const char *name)
{
    if (0 == strcmp("once", name))
        return APL_SCOPE_ONCE;
    if (0 == strcmp("request", name))
        return APL_SCOPE_REQUEST;
    if (0 == strcmp("connection", name))
        return APL_SCOPE_CONN;
    if (0 == strcmp("conn", name))
        return APL_SCOPE_CONN;
    if (0 == strcmp("server", name))
        return APL_SCOPE_SERVER;
    return APL_SCOPE_ONCE;
}