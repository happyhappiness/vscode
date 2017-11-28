bool
ACLExternal::isProxyAuth() const
{
#if USE_AUTH
    return data->def->require_auth;
#else
    return false;
#endif
}