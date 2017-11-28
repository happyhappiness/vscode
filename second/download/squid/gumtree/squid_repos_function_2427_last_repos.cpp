static ClientInfo *
clientdbAdd(const Ip::Address &addr)
{
    ClientInfo *c = new ClientInfo(addr);
    hash_join(client_table, &c->hash);
    ++statCounter.client_http.clients;

    if ((statCounter.client_http.clients > max_clients) && !cleanup_running && cleanup_scheduled < 2) {
        ++cleanup_scheduled;
        eventAdd("client_db garbage collector", clientdbScheduledGC, NULL, 90, 0);
    }

    return c;
}