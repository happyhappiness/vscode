static ClientInfo *

clientdbAdd(const Ip::Address &addr)
{
    ClientInfo *c;
    char *buf = static_cast<char*>(xmalloc(MAX_IPSTRLEN)); // becomes hash.key
    c = (ClientInfo *)memAllocate(MEM_CLIENT_INFO);
    debugs(77, 9, "ClientInfo constructed, this=" << c);
    c->hash.key = addr.toStr(buf,MAX_IPSTRLEN);
    c->addr = addr;
#if USE_DELAY_POOLS
    /* setup default values for client write limiter */
    c->writeLimitingActive=false;
    c->writeSpeedLimit=0;
    c->bucketSize = 0;
    c->firstTimeConnection=true;
    c->quotaQueue = NULL;
    c->rationedQuota = 0;
    c->rationedCount = 0;
    c->selectWaiting = false;
    c->eventWaiting = false;

    /* get current time */
    getCurrentTime();
    c->prevTime=current_dtime;/* put current time to have something sensible here */
#endif
    hash_join(client_table, &c->hash);
    ++statCounter.client_http.clients;

    if ((statCounter.client_http.clients > max_clients) && !cleanup_running && cleanup_scheduled < 2) {
        ++cleanup_scheduled;
        eventAdd("client_db garbage collector", clientdbScheduledGC, NULL, 90, 0);
    }

    return c;
}