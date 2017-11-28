static void
commConnectDnsHandle(const ipcache_addrs *ia, const DnsLookupDetails &details, void *data)
{
    ConnectStateData *cs = (ConnectStateData *)data;
    cs->dns = details;

    if (ia == NULL) {
        debugs(5, 3, "commConnectDnsHandle: Unknown host: " << cs->host);
        cs->callCallback(COMM_ERR_DNS, 0);
        return;
    }

    assert(ia->cur < ia->count);

    cs->default_addr = ia->in_addrs[ia->cur];

    if (Config.onoff.balance_on_multiple_ip)
        ipcacheCycleAddr(cs->host, NULL);

    cs->addrcount = ia->count;

    cs->connstart = squid_curtime;

    cs->connect();
}