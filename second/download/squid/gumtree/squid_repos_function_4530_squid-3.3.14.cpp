void
ACLMaxConnection::parse()
{
    char *t = strtokFile();

    if (!t)
        return;

    limit = (atoi (t));

    /* suck out file contents */
    // ignore comments
    bool ignore = false;
    while ((t = strtokFile())) {
        ignore |= (*t != '#');

        if (ignore)
            continue;

        debugs(89, DBG_CRITICAL, "WARNING: max_conn only accepts a single limit value.");
        limit = 0;
    }
}