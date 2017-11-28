bool
GetHostWithPort(char *token, Ip::Address *ipa)
{
    char *t;
    char *host;
    char *tmp;
    unsigned short port;

    host = NULL;
    port = 0;

    if (*token == '[') {
        /* [host]:port */
        host = token + 1;
        t = strchr(host, ']');
        if (!t)
            return false;
        *t = '\0';
        ++t;
        if (*t != ':')
            return false;
        port = xatos(t + 1);
    } else if ((t = strchr(token, ':'))) {
        /* host:port */
        host = token;
        *t = '\0';
        port = xatos(t + 1);

        if (0 == port)
            return false;
    } else if (strtol(token, &tmp, 10) && !*tmp) {
        port = xatos(token);
    } else {
        host = token;
        port = 0;
    }

    if (NULL == host)
        ipa->SetAnyAddr();
    else if ( ipa->GetHostByName(host) ) /* dont use ipcache. Accept either FQDN or IPA. */
        (void) 0;
    else
        return false;

    /* port MUST be set after the IPA lookup/conversion is performed. */
    ipa->SetPort(port);

    return true;
}