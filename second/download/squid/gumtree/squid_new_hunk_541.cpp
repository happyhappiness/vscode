
    c->cutoff.n_denied = c->Icp.result_hist[LOG_UDP_DENIED];

    return 1;
}

void
clientdbDump(StoreEntry * sentry)
{
    const char *name;
    ClientInfo *c;
    int icp_total = 0;
    int icp_hits = 0;
    int http_total = 0;
    int http_hits = 0;
    storeAppendPrintf(sentry, "Cache Clients:\n");
    hash_first(client_table);
