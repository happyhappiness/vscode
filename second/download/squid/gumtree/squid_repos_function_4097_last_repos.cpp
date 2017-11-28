void
ACLMaxConnection::parse()
{
    char *t = ConfigParser::strtokFile();

    if (!t)
        return;

    limit = (atoi (t));

    /* suck out file contents */
    // ignore comments
    bool ignore = false;
    while ((t = ConfigParser::strtokFile())) {
        ignore |= (*t != '#');

        if (ignore)
            continue;

        debugs(89, DBG_CRITICAL, "WARNING: max_conn only accepts a single limit value.");
        limit = 0;
    }
}