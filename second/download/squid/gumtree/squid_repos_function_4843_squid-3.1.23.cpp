AuthConfig *
AuthConfig::Find(const char *proxy_auth)
{
    for (authConfig::iterator  i = Config.authConfiguration.begin(); i != Config.authConfiguration.end(); ++i)
        if (strncasecmp(proxy_auth, (*i)->type(), strlen((*i)->type())) == 0)
            return *i;

    return NULL;
}