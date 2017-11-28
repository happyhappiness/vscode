bool
ACLExternal::isProxyAuth() const
{
    return data->def->require_auth;
}