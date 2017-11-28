void
ACLMaxConnection::parse()
{
    char *t = strtokFile();

    if (!t)
        return;

    limit = (atoi (t));

    /* suck out file contents */

    while ((t = strtokFile())) {
        limit = 0;
    }
}