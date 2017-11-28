void
parse_IpAddress_list_token(IpAddress_list ** head, char *token)
{
    char *t;
    char *host;
    char *tmp;

    IpAddress ipa;
    unsigned short port;
    IpAddress_list *s;

    host = NULL;
    port = 0;

    if (*token == '[') {
        /* [host]:port */
        host = token + 1;
        t = strchr(host, ']');
        if (!t)
            self_destruct();
        *t++ = '\0';
        if (*t != ':')
            self_destruct();
        port = xatos(t + 1);
        if (!Ip::EnableIpv6) {
            debugs(3, DBG_CRITICAL, "FATAL: IPv6 is not enabled.");
            self_destruct();
        }
    } else if ((t = strchr(token, ':'))) {
        /* host:port */
        host = token;
        *t = '\0';
        port = xatos(t + 1);

        if (0 == port)
            self_destruct();
    } else if ((port = strtol(token, &tmp, 10)), !*tmp) {
        /* port */
    } else {
        host = token;
        port = 0;
    }

    if (NULL == host)
        ipa.SetAnyAddr();
    else if ( ipa.GetHostByName(host) )	/* dont use ipcache. Accept either FQDN or IPA. */
        (void) 0;
    else
        self_destruct();

    /* port MUST be set after the IPA lookup/conversion is perofrmed. */
    ipa.SetPort(port);

    while (*head)
        head = &(*head)->next;

    s = static_cast<IpAddress_list *>(xcalloc(1, sizeof(*s)));
    s->s = ipa;

    *head = s;
}