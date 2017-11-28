static void
clientdbFreeItem(void *data)
{
    ClientInfo *c = (ClientInfo *)data;
    safe_free(c->hash.key);

#if USE_DELAY_POOLS
    if (CommQuotaQueue *q = c->quotaQueue) {
        q->clientInfo = NULL;
        delete q; // invalidates cbdata, cancelling any pending kicks
    }
#endif

    debugs(77, 9, "ClientInfo destructed, this=" << c);
    memFree(c, MEM_CLIENT_INFO);
}