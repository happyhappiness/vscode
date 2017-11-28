Auth::Config *
Auth::Config::Find(const char *proxy_auth)
{
    for (Auth::ConfigVector::iterator  i = Auth::TheConfig.begin(); i != Auth::TheConfig.end(); ++i)
        if (strncasecmp(proxy_auth, (*i)->type(), strlen((*i)->type())) == 0)
            return *i;

    return NULL;
}