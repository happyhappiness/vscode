    debugs(15, 0, "WARNING: Unknown neighbor type: " << s);

    return PEER_SIBLING;
}

#if USE_WCCPv2
static void
parse_IpAddress_list(Ip::Address_list ** head)
{
    char *token;
    Ip::Address_list *s;
    Ip::Address ipa;

    while ((token = strtok(NULL, w_space))) {
        if (GetHostWithPort(token, &ipa)) {

            while (*head)
                head = &(*head)->next;

            s = static_cast<Ip::Address_list *>(xcalloc(1, sizeof(*s)));
            s->s = ipa;

            *head = s;
        } else
            self_destruct();
    }
}

static void
dump_IpAddress_list(StoreEntry * e, const char *n, const Ip::Address_list * s)
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
free_IpAddress_list(Ip::Address_list ** head)
{
    if (*head) delete *head;
    *head = NULL;
}

#if CURRENTLY_UNUSED
/* This code was previously used by http_port. Left as it really should
 * be used by icp_port and htcp_port
 */
static int
check_null_IpAddress_list(const Ip::Address_list * s)
{
    return NULL == s;
}

#endif /* CURRENTLY_UNUSED */
#endif /* USE_WCCPv2 */

static void
parsePortSpecification(AnyP::PortCfg * s, char *token)
{
    char *host = NULL;
    unsigned short port = 0;
    char *t = NULL;
    char *junk = NULL;

