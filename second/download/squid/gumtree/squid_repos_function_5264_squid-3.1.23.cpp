static void
netdbSendPing(const ipcache_addrs *ia, const DnsLookupDetails &, void *data)
{
    IpAddress addr;
    char *hostname = NULL;
    static_cast<generic_cbdata *>(data)->unwrap(&hostname);
    netdbEntry *n;
    netdbEntry *na;
    net_db_name *x;
    net_db_name **X;

    if (ia == NULL) {
        xfree(hostname);
        return;
    }

    addr = ia->in_addrs[ia->cur];

    if ((n = netdbLookupHost(hostname)) == NULL) {
        n = netdbAdd(addr);
        netdbHostInsert(n, hostname);
    } else if ((na = netdbLookupAddr(addr)) != n) {
        /*
         *hostname moved from 'network n' to 'network na'!
         */

        if (na == NULL)
            na = netdbAdd(addr);

        debugs(38, 3, "netdbSendPing: " << hostname << " moved from " << n->network << " to " << na->network);

        x = (net_db_name *) hash_lookup(host_table, hostname);

        if (x == NULL) {
            debugs(38, 1, "netdbSendPing: net_db_name list bug: " << hostname << " not found");
            xfree(hostname);
            return;
        }

        /* remove net_db_name from 'network n' linked list */
        for (X = &n->hosts; *X; X = &(*X)->next) {
            if (*X == x) {
                *X = x->next;
                break;
            }
        }

        n->link_count--;
        /* point to 'network na' from host entry */
        x->net_db_entry = na;
        /* link net_db_name to 'network na' */
        x->next = na->hosts;
        na->hosts = x;
        na->link_count++;
        n = na;
    }

    if (n->next_ping_time <= squid_curtime) {
        debugs(38, 3, "netdbSendPing: pinging " << hostname);
        icmpEngine.DomainPing(addr, hostname);
        n->pings_sent++;
        n->next_ping_time = squid_curtime + Config.Netdb.period;
        n->last_use_time = squid_curtime;
    }

    xfree(hostname);
}