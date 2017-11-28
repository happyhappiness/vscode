static ClientInfo *

clientdbAdd(const IpAddress &addr)
{
    ClientInfo *c;
    char *buf = new char[MAX_IPSTRLEN];
    c = (ClientInfo *)memAllocate(MEM_CLIENT_INFO);
    c->hash.key = addr.NtoA(buf,MAX_IPSTRLEN);
    c->addr = addr;
    hash_join(client_table, &c->hash);
    statCounter.client_http.clients++;

    if ((statCounter.client_http.clients > max_clients) && !cleanup_running && cleanup_scheduled < 2) {
        cleanup_scheduled++;
        eventAdd("client_db garbage collector", clientdbScheduledGC, NULL, 90, 0);
    }

    return c;
}