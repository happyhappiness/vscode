int
internalHostnameIs(const char *arg)
{
    wordlist *w;

    if (0 == strcmp(arg, internalHostname()))
        return 1;

    for (w = Config.hostnameAliases; w; w = w->next)
        if (0 == strcmp(arg, w->key))
            return 1;

    return 0;
}