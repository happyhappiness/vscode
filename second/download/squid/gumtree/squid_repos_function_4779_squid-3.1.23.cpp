int
authenticateActiveSchemeCount(void)
{
    int rv = 0;

    for (authConfig::iterator i = Config.authConfiguration.begin(); i != Config.authConfiguration.end(); ++i)
        if ((*i)->configured())
            ++rv;

    debugs(29, 9, "authenticateActiveSchemeCount: " << rv << " active.");

    return rv;
}