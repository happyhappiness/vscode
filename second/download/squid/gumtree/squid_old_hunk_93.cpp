    debugs(15, 0, "WARNING: Unknown neighbor type: " << s);

    return PEER_SIBLING;
}

#if USE_WCCPv2
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

static void
parse_IpAddress_list(IpAddress_list ** head)
{
    char *token;

    while ((token = strtok(NULL, w_space))) {
        parse_IpAddress_list_token(head, token);
    }
}

static void
dump_IpAddress_list(StoreEntry * e, const char *n, const IpAddress_list * s)
{
    char ntoabuf[MAX_IPSTRLEN];

    while (s) {
        storeAppendPrintf(e, "%s %s\n",
                          n,
                          s->s.NtoA(ntoabuf,MAX_IPSTRLEN));
        s = s->next;
    }
}

static void
free_IpAddress_list(IpAddress_list ** head)
{
    if (*head) delete *head;
    *head = NULL;
}

#if CURRENTLY_UNUSED
/* This code was previously used by http_port. Left as it really should
 * be used by icp_port and htcp_port
 */
static int
check_null_IpAddress_list(const IpAddress_list * s)
{
    return NULL == s;
}

#endif /* CURRENTLY_UNUSED */
#endif /* USE_WCCPv2 */

CBDATA_CLASS_INIT(http_port_list);

static void
parse_http_port_specification(http_port_list * s, char *token)
{
    char *host = NULL;
    unsigned short port = 0;
    char *t = NULL;
    char *junk = NULL;

